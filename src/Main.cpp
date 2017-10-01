#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <set>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "zbar.h"

#include "Piece.hpp"
#include "format.hpp"

int main(int argc, char* argv[]) {
  using std::cerr;
  using std::cout;
  using std::endl;

  std::vector<Polygon> pieces, pframe;

  if (argc <= 1) {
    cerr << "not given argument!!" << endl;
    return -1;
  }

  cv::VideoCapture cap(std::atoi(argv[2]));

  if (!cap.isOpened()) {
    cerr << "Can't open the camera" << endl;
    return -1;
  }

  cerr << cap.get(CV_CAP_PROP_FRAME_WIDTH) << " " << cap.get(CV_CAP_PROP_FRAME_HEIGHT) << endl;

  zbar::ImageScanner scanner;
  scanner.set_config(zbar::ZBAR_NONE, zbar::ZBAR_CFG_ENABLE, 1);

  std::string res;
  std::set<std::string> st;

  while (true) {
    cv::Mat frame, gray;
    cap >> frame;
    // cv::resize(frame, frame, cv::Size(), 0.5, 0.5);
    cv::cvtColor(frame, gray, cv::COLOR_BGR2RGB);
    cv::cvtColor(gray, gray, cv::COLOR_BGR2GRAY);

    const size_t width = gray.cols;
    const size_t height = gray.rows;
    unsigned char* raw = (unsigned char*)gray.data;
    std::vector<std::string> strs;

    zbar::Image image(width, height, "Y800", raw, width * height);
    const size_t symbol_N = scanner.scan(image);
    if (symbol_N != 0) {
      for (auto itr = image.symbol_begin(); itr != image.symbol_end(); ++itr) {
        const auto& symbol = *itr;
        std::vector<cv::Point> vp;
        std::string symbol_str = symbol.get_data();
        const size_t location_size = symbol.get_location_size();
        for (size_t i = 0; i < location_size; ++i) {
          vp.emplace_back(symbol.get_location_x(i), symbol.get_location_y(i));
        }
        cv::RotatedRect r = cv::minAreaRect(vp);
        cv::Point2f points[4];
        r.points(points);
        bool flg = true;
        if (st.find(symbol_str) == st.end()) {
          flg = false;
          strs.emplace_back(symbol_str);
        }
        for (size_t i = 0; i < 4; ++i) {
          if (flg) {
            cv::putText(frame, "OK", r.center, cv::FONT_HERSHEY_SIMPLEX, 5.0, cv::Scalar(0, 0, 255), 2, CV_AA);
            cv::line(frame, points[i], points[(i + 1) % 4], cv::Scalar(0, 0, 255), 3);
          } else {
            cv::line(frame, points[i], points[(i + 1) % 4], cv::Scalar(255, 0, 0), 3);
          }
        }
      }
    }

    cv::imshow("camera", frame);

    const int key = cv::waitKey(1);

    if (key == 's') {
      // res += symbol_str;
      try {
        if (std::stoi(argv[1]) == 0) {
          for (auto&& str : strs) {
            st.emplace(str);
            util::problem_format(str, pieces, pframe);
            cerr << "get: " << str << endl;
          } 
        } else {
          for (auto&& str : strs) {
            st.emplace(str);
            util::hint_format(str, pieces);
            cerr << "get: " << str << endl;
          }
        }
      } catch (std::exception& e) {
        cerr << e.what() << endl;
      } catch (const char* e) {
        cerr << e << endl;
      }
    } else if (key == 'q') {
      break;
    }
  }

  if (std::stoi(argv[1]) == 0) {
    cout << pieces.size() << endl;
    for (auto&& piece : pieces) cout << piece;
    cout << pframe.size() << endl;
    for (auto&& hole : pframe) cout << hole;
  } else {
    cout << pieces.size() << endl;
    for (auto&& piece : pieces) cout << piece;
  }

  return 0;
}

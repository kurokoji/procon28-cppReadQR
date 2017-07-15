#ifndef PROCON28_FORMAT_HPP
#define PROCON28_FORMAT_HPP

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>

#include "boost/algorithm/string.hpp"

namespace ba = boost::algorithm;

namespace util {
  std::string format(std::string& s) {
    // コロンの数(データ数)
    const size_t sep_N = std::count(std::begin(s), std::end(s), ':');
    std::ostringstream ret;
    std::vector<std::string> split_s;

    std::replace(std::begin(s), std::end(s), ':', ' ');
    ba::split(split_s, s, boost::is_any_of(" "));

    // ピース数
    const size_t pieces_N = std::stoi(split_s[0]);
    // フレームのホール数
    const size_t holes_N = sep_N - pieces_N;

    ret << pieces_N << '\n';

    size_t index = 1;
    // ピース
    for (size_t i = 0; i < pieces_N; ++i) {
      // 各ピースの頂点数
      const size_t point_N = std::stoi(split_s[index]);
      //ret += split_s[index++] + "\n";
      ret << split_s[index++] << '\n';
      for (size_t j = 0; j < point_N * 2; j += 2) {
        //ret += split_s[index + j] + " " + split_s[index + j + 1] + "\n";
        ret << split_s[index + j] << " " << split_s[index + j + 1] << '\n';
      }
      index += point_N * 2;
    }

    // ret += std::to_string(holes_N);
    ret << holes_N << '\n';
    // フレームのホール
    for (size_t i = 0; i < holes_N; ++i) {
      // 各ピースの頂点数
      const size_t point_N = std::stoi(split_s[index]);
      // ret += split_s[index++] + "\n";
      ret << split_s[index++] << '\n';
      for (size_t j = 0; j < point_N * 2; j += 2) {
        // ret += split_s[index + j] + " " + split_s[index + j + 1] + "\n";
        ret << split_s[index + j] << " " << split_s[index + j + 1] << '\n';
      }
      index += point_N * 2;
    }

    return ret.str();
  }
}

#endif

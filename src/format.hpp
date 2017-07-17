#ifndef PROCON28_FORMAT_HPP
#define PROCON28_FORMAT_HPP

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace util {
std::vector<std::string> split(const std::string& s, char delim) {
  std::vector<std::string> ret;
  std::stringstream ss(s);
  std::string token;

  while (std::getline(ss, token, delim)) {
    ret.emplace_back(token);
  }

  return ret;
}

// 問題を受け取るとき
std::string problem_format(std::string& s) {
  // コロンの数(データ数)
  const size_t sep_N = std::count(std::begin(s), std::end(s), ':');
  std::ostringstream ret;
  std::vector<std::string> split_s;

  std::replace(std::begin(s), std::end(s), ':', ' ');

  split_s = split(s, ' ');

  // ピース数
  const size_t pieces_N = std::stoi(split_s[0]);
  // フレームのホール数
  const size_t holes_N = sep_N - pieces_N;

  if (holes_N == 0) {
    throw "Exception : wrong format\n";
  }

  ret << pieces_N << '\n';

  size_t index = 1;
  // ピース
  for (size_t i = 0; i < pieces_N; ++i) {
    // 各ピースの頂点数
    const size_t point_N = std::stoi(split_s[index]);
    ret << split_s[index++] << '\n';
    for (size_t j = 0; j < point_N * 2; j += 2) {
      ret << split_s[index + j] << " " << split_s[index + j + 1] << '\n';
    }
    index += point_N * 2;
  }

  ret << holes_N << '\n';
  // フレームのホール
  for (size_t i = 0; i < holes_N; ++i) {
    // 各ピースの頂点数
    const size_t point_N = std::stoi(split_s[index]);
    ret << split_s[index++] << '\n';
    for (size_t j = 0; j < point_N * 2; j += 2) {
      ret << split_s[index + j] << " " << split_s[index + j + 1] << '\n';
    }
    index += point_N * 2;
  }


  return ret.str();
}

// ヒントを受け取るとき
std::string hint_format(std::string& s) {
  std::ostringstream ret;

  std::replace(std::begin(s), std::end(s), ':', ' ');
  std::vector<std::string> split_s = split(s, ' ');

  // ピース数
  const size_t pieces_N = std::stoi(split_s[0]);
  ret << pieces_N << '\n';

  size_t index = 1;
  for (size_t i = 0; i < pieces_N; ++i) {
    // 各ピースの頂点数
    const size_t point_N = std::stoi(split_s[index]);
    ret << split_s[index++] << '\n';
    for (size_t j = 0; j < point_N * 2; j += 2) {
      ret << split_s[index + j] << " " << split_s[index + j + 1] << '\n';
    }
    index += point_N * 2;
  }

  if (index != split_s.size()) {
    throw "Exception : wrong format\n";
  }

  return ret.str();
}
}  // namespace util

#endif

#ifndef LIB_STOCK_INFO_H_
#define LIB_STOCK_INFO_H_
#include <tuple>
#include <string>
#include <chrono>

std::tuple<std::string,
              std::chrono::system_clock::time_point, unsigned>
   stock_info(const std::string &name);
#endif

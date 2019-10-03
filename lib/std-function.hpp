#ifndef LIB_STD_FUNCTION_HPP_
#define LIB_STD_FUNCTION_HPP_

#include <iostream>
#include <deque>
#include <list>
#include <vector>
#include <functional>

static auto consumer (auto &container) {
   return [&] (auto value) {
      container.push_back(value);
   };
}

static void print(const auto &c) {
   for  (auto i : c) {
      std::cout << i << ", ";
   }
   std::cout << '\n';
}

#endif

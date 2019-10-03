#ifndef LIB_CONTAINERS_HPP_
#define LIB_CONTAINERS_HPP_

#include <vector>
#include <algorithm>
#include <cassert>
#include <iterator>
#include <string>
#include <list>
#include <map>
#include <unordered_map>
#include <set>

template <typename T>
void quick_remove_at(std::vector<T> &v,
      typename std::vector<T>::iterator it)
{
   if (it != std::end(v)) {
      *it = std::move(v.back());
      v.pop_back();
   }
}

template <typename C, typename T>
void insert_sorted(C &v, const T &word)
{
   const auto insert_pos
   {std::lower_bound(std::begin(v), std::end(v), word)};
   //if (word.compare(*insert_pos)) {
   std::string item = static_cast<std::string>(word);
   if (item.compare(*insert_pos)) {
      v.insert(insert_pos, word);
   } else {
      return;
   }
}

struct billionaire {
   std::string name;
   double dollars;
   std::string country;
};
#endif

#include <iterator>
#include <map>
#include <algorithm>
#include <string>

std::string filter_ws(const std::string& s)
{
   const char *ws {" \r\n\t"};
   const auto a (s.find_first_not_of(ws));
   const auto b (s.find_last_not_of(ws));
   if (a == std::string::npos) {
      return {};
   }
   return s.substr(a,b);
}

std::multimap<std::size_t, std::string> get_sentence_stats(const std::string& content)
{
   std::multimap<std::size_t, std::string> ret;
   const auto end_it (std::end(content));
   auto it1 (std::begin(content));
   auto it2 (std::find(it1, end_it, '.'));
   while (it1 != end_it && std::distance(it1, it2) > 0) {
      std::string s {filter_ws({it1, it2})};
      if (s.length() > 0) {
          const auto words (count(begin(s), end(s), ' ') + 1);
          ret.emplace(make_pair(words, move(s)));
      }
      it1 = std::next(it2, 1);
      it2 = std::find(it1, end_it, '.');
   }
   return ret; 
}

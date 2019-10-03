#include <map>
#include <sstream>
#include <algorithm>
#include <string>
#include <iostream>
#include <set>
#include <vector>
#include <iomanip>

template <typename IT>
std::string word_freq_counter(IT it, IT end)
{
   using MT1 = std::string;
   using MT2 = std::pair<std::size_t, std::size_t>;
   std::map<MT1, MT2> words;
   int max_word_len {0};
   auto filter_punct ([](const std::string &s) {
         const char *puncts {".,:; "};
         const auto idx_start (s.find_first_not_of(puncts));
         const auto idx_end (s.find_last_not_of(puncts));
         return s.substr(idx_start, idx_end-idx_start + 1);
         });
   //using namespace std::literals;
   for (; it != end; ++it) {
      auto filtered (filter_punct(*it));
      max_word_len = std::max<int>(max_word_len, filtered.length());
      auto [iterator, success] = words.try_emplace(filtered, 
            filtered.length(), 1);
      if (!success) {
         iterator->second.second += 1;
      }
   }
   /* Tried to sort the map in place. but it seems you can't override
    * the compare function as it uses the key. Since we want to sort 
    * the map based on the pair of values we need to convert it to
    * vector and sort the vector. 
    */
   auto comp = [](std::pair<MT1, MT2> const& a,
         std::pair<MT1, MT2> const& b) {
      return a.second.second > b.second.second;
   };
   std::vector<std::pair<MT1,MT2>> my_pairs;
   std::cout << "Using move semantics. Instead of copying\n";
   std::move(words.begin(), words.end(), std::back_inserter(my_pairs));
   // std::vector<std::pair<MT1,MT2>> my_pairs(words.begin(), words.end())
   std::sort(my_pairs.begin(), my_pairs.end(), comp);
   std::cout << "# " << std::setw(max_word_len) << "<WORD>" << " #<COUNT>\n";
   for(const auto &w : my_pairs)
   {
      std::cout << std::setw(max_word_len + 2) << w.first << " #"
         << w.second.second << '\n';
      //std::cout << w.first << ": " << w.second.second << '\n';
   }

   return "DONE";
}

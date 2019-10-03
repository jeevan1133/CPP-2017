#include "lib/freq-counter.hpp"
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

string filter_punctuation(const string &s)
{
   const char *forbidden {".,:; "};
   const auto  idx_start (s.find_first_not_of(forbidden));
   const auto  idx_end   (s.find_last_not_of(forbidden));
   return s.substr(idx_start, idx_end - idx_start + 1);
}

int main() 
{
   std::cout << word_freq_counter(std::istream_iterator<std::string> {std::cin}, {}) << std::endl;
  /* 
   map<string, size_t> words;
   int max_word_len {0};

   string s;
   while (cin >> s) {
      auto filtered (filter_punctuation(s));
      max_word_len = max<int>(max_word_len, filtered.length());
      ++words[filtered];
   }
   vector<pair<string, size_t>> word_counts;
   word_counts.reserve(words.size());
   move(begin(words), end(words), back_inserter(word_counts));
   sort(begin(word_counts), end(word_counts),
         [](const auto &a, const auto &b) {
         return a.second > b.second;
         });
   cout << "# " << setw(max_word_len) << "<WORD>" << " #<COUNT>\n";
   for (const auto & [word, count] : word_counts) {
      cout << setw(max_word_len + 2) << word << " #"
         << count << '\n';
   } 
   */
   std::cout << "To iterate over strings.\n";
   {
       std::string str = "Yo waddup? what, you doing, are ;you h:ome. I'm not ther; I love Pycharm, and Clion.";
        istringstream iss(str);
        std::istream_iterator<std::string> it {iss};
        std::istream_iterator<std::string> end;
        for (;it != end; ++it) {
            std::cout << filter_punctuation(*it) << std::endl;
        }
   }
}


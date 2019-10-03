#include "lib/multimap.hpp"
#include <iostream>

using namespace std;
int main()
{
   cin.unsetf(ios::skipws);
   string content {istream_iterator<char>{cin}, {}};
   for (const auto &[word_count, sentence]
         : get_sentence_stats(content)) {
      cout << word_count << " words: " << sentence << ".\n";
   }
}

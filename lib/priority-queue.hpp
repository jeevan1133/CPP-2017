#include <queue>
#include <tuple>
#include <string>
#include <iostream>

void my_priority_queue(std::initializer_list<std::pair<int, std::string> >& li) 
{
   std::priority_queue<std::pair<int, std::string>> q;
   for (const auto &p : li) {
      q.push(p);
   }
   while (!q.empty()) {
      std::cout << q.top().first << ": " << q.top().second << '\n';
      q.pop();
   }
   std::cout << '\n';
}

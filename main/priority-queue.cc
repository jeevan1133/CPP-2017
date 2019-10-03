#include "lib/priority-queue.hpp"

int main()
{
   std::initializer_list<std::pair<int, std::string>> li {
      {1, "dishes"},
         {0, "watch tv"},
         {2, "do homework"},
         {0, "read comics"},
   };
   my_priority_queue(li);
}

#include "divide-remainder.hpp"

std::pair<int, int> divide_remainder(int const &dividend, 
                                     int const &divisor)
{
   auto n1 = dividend / divisor;
   auto n2 = dividend % divisor;

   return std::make_pair(n1,n2);
}

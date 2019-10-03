#include "stock-info.hpp"
#include <ctime>

std::tuple<std::string,
              std::chrono::system_clock::time_point, unsigned>
   stock_info(const std::string &name)
{
   std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
   
   return std::make_tuple(name, now, 600);
}

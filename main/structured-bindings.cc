#include "lib/divide-remainder.hpp"
#include "lib/stock-info.hpp"
//#include "lib/my-wrapper.hpp"
#include "lib/fold.hpp"
#include <iostream>
#include <iomanip>
#include <vector>
#include <type_traits>
#include <algorithm>
#include <set>
#include <utility>

struct employee {
   unsigned id;
   std::string name;
   std::string role;
   unsigned salary;
};

/*
template <typename T>
struct sum_type {
   T value;
   template <typename ... Ts>
// sum(Ts&& ... values) : value{(values + ...)} {}  // doesn't work
   sum_type(Ts&& ... ts) -> sum_type<std::common_type_t<Ts... >>;
//auto sum(Ts ... ts) {
//value = (ts + ...);
//}
};
*/

template<typename T>
class addable {
   T val;
   public:
   addable(T v) : val {v} {}
   template <typename U>
      T add (U x) const {
         if constexpr (std::is_same_v<T, std::vector<U>>) {
            auto copy (val);
            for (auto &n : copy) {
               n += x;
            }
            return copy;
         }
         else {
            return val + x;
         }
      }
};

template<typename T>
void printIt(T &vec, const std::string &msg=nullptr) {
   if (!msg.empty()) {
      std::cout << msg << std::endl;
   }
   for (auto &n: vec) {
      std::cout << n << ' ';
   }
   std::cout << '\n';

}
int main()
{
   {
      std::cout << "******Running divide, stock and employees******\n";
      auto result = divide_remainder(16,3);
      std::cout << "16/3 is "
         << result.first << " with a remainder of "
         << result.second << '\n';
      auto [fraction, remainder] = divide_remainder(16,3);
      std::cout << "With capture 16 / 3 is "
         << fraction << " with a remainder of "
         << remainder << '\n';

      const auto [name, valid_time, price] = stock_info("INTC");
      std::time_t now_c = \
                          std::chrono::system_clock::to_time_t(valid_time);
      std::cout << name << " at "
         << std::put_time(std::localtime(&now_c), "%F %T")
         << " has " << price << "$.\n";

      std::vector<employee> employees;
      employee e1 = {1, "J", "Mgr", 890000};
      employee e2 = {2, "K", "Assistant Mgr", 650000};
      employees.push_back(e1);
      employees.push_back(e2);
      std::cout << "\t\t\t\tEmployees\n";
      for (const auto &[id, name, role, salary]: employees) {
         std::cout << "\t-Name: " << name
            << "\n\t-id: " << id << '\n';
      }
   }
   /*
      auto v   {1};     // v is int
      auto w   {1, 2};  // error: only single elements in direct
   // auto initialization allowed! (this is new)
   auto x = {1};     // x is std::initializer_list<int>
   auto y = {1, 2};  // y is std::initializer_list<int>
   auto z = {1, 2, 3.0}; // error: Cannot deduce element type

   std::vector<int> V {N, v}  // initialize the vector with two items
   std::vector<int> V (N, v)  // initialize N many items with default value v

   my_wrapper<int, float, char*> wrapper {123, 1.23, "abc"};
   std::cout << "t1: " << wrapper.getT1() << '\n';
   */
   {
      std::cout << "************ Running Addable **************\n";
      auto x =  addable<int>{1}.add(2);
      std::cout << x << '\n';
      std::cout << addable<float>{1.0}.add(2) << '\n';
      std::cout << addable<std::string>{"aa"}.add("bb") << '\n';
      std::vector<int> v {1,2,3};
      for (auto &y: addable<std::vector<int>>{v}.add(10))
      {
         std::cout << y << ' ';
      }
      std::cout << '\n';
   }
   {
      std::cout << "**********Running sum, product and match*********\n";
      int the_sum = sum(1,2,3,4,5);
      // int the_sum {sum(1,2,3,4,5)};
      std::cout << "The sum: " << the_sum << '\n';
      int the_product {product(2,3,4)};
      std::cout << "The product: " << the_product << '\n';
      std::vector<int> v {1,2,3,4,5};
      std::cout << "Calling match on vector with 2 and 5: "
         << matches(v, 2,5) << '\n'
         << "Calling match on vector with 100, 200: "
         << matches(v, 100, 200) << '\n'
         << "Calling match on vector with 100: "
         << matches(v, 100) << '\n'
         << "Calling match on \"abcdefg\" with x, y, z: "
         << matches("abcdefg", 'x','y','z') << '\n'
         << "Calling match on \"abcdefg\" with a, d, f: "
         << matches("abcdefg", 'a','d','f') << '\n';

   }
   std::set<int> my_set {1,2,3,4};
   {
      std::cout << "**********Running insert in set and vector*******\n";
      int x ;
      for (auto n: insert_all(my_set, x, 5,6,7,8)) {
         if (!x) {
            std::cout << " insert all unsuccesssful" << '\n';
            break;
         }
         std::cout << n << ' ';
      }
      std::cout << '\n';
      // auto inserted = insert_all_alt(std::move(my_set),x,9,10);
      for (auto n: insert_all_alt(std::move(my_set),x,9,10)) {
         if (!x) {
            std::cout << " insert all unsuccesssful" << '\n';
            break;
         }
         std::cout << n << ' ';
      }
      std::cout << '\n';
      std::cout << "**********Running matches and within *********\n";
      // If we don't have this my_set becomes null
      insert_all(my_set, x, 1,2,3,4);
      std::cout << "Calling Match again with set: "
         << matches(my_set, 1, 3) << '\n'
         << "Calling match on {1,2,3,4,5} "
         << "to find 3,5: "
         << matches(std::set<int> {1,2,3,4,5}, 3,5) << '\n';

      std::cout << std::boolalpha << within(10, 20, 1, 15, 30)
         << " " << within(10,20,11,12,13) << " "
         << within(5.0, 5.5,  5.1, 5.2, 5.3) << '\n';

      std::string aaa {"aaa"};
      std::string bcd {"bcd"};
      std::string zzz {"zzz"};

      std::cout << "Strings within aaa, bcd, zzz: "
         << std::boolalpha << within(aaa, bcd, zzz) << '\n';
      std::cout << "Strings within aaa, zzz, bcd : "
         << std::boolalpha << within(aaa, zzz, bcd) << '\n';
      std::vector<int> vec {1,2,3};
      insert_all_vec(vec, x, 4,5,6);
      printIt(vec, "Called insert_all_vec");
   }
   {
      std::cout <<"************Running generic insertion************\n";
      insert<int> ins;
      bool success = false;
      std::set<int> my_new_set {1,2,3,4};
      printIt(my_new_set, "Before insertion");
      my_new_set = ins.insert_generic(std::move(my_new_set), success, 6,7,8);
      printIt(my_new_set);
   }
   return 0;
}

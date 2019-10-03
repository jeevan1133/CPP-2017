//#include "lib/std-function.hpp"
#include <iostream>
#include <functional>
#include <iterator>
#include <numeric>

#define FN_NAME std::cout << __FUNCTION__  << '\n'

template <typename T>
void print(const T& val) {
   std::cout << val << ", ";
}

template <typename T, typename ...Ts>
auto concat( T t, Ts ...ts) {
   if constexpr (sizeof ...(ts) > 0) {
      return [=](auto ...parameters) {
         /*This is how you print variable arguments */
         (print(parameters), ...);
         std::cout << '\n';
         return t(concat(ts ...)(parameters ...));
      };
      
   }
   else {
      return t;
   }
}

template <typename ...Ts>
static auto multicall(Ts ...functions) {
   FN_NAME;
   //std::cout << "In multicall\n";
   //(print(functions),...);
   //std::cout << '\n';
   return [=](auto x) {
      (void)std::initializer_list<int>{
         ((void)functions(x),1)...
      };
   };
}

template <typename T, typename Q>
static auto brace_print(Q a, Q b)
{
   FN_NAME; 
   return [=](auto x) {
      std::cout << a << x << b << ", ";
   };
}

template <typename T>
auto map(T fn) {
    FN_NAME;
    return [=](auto reduce_fn) {
        return [=](auto accum, auto input) {
            return reduce_fn(accum, fn(input));
        };
    };
}

template <typename T>
auto filter(T pred) {
    return [=](auto reduce_fn) {
        return [=](auto accum, auto input) {
            if (pred(input))
                return reduce_fn(accum, input);
            else
                return accum;
        };
    };
}

template <typename T, typename ...Ts>
static auto for_each (T f, Ts ...xs) {
   FN_NAME;
   std::cout << "In for_each with\n";
   (print(xs),...);
   std::cout << '\n';
   (void)std::initializer_list<int>{
        ((void)f(xs), 0)...
   };
}

static void print(int x, int y)
{
    std::cout << "("<< x << ","<< y << ")\n";
}

int main() 
{
   std::cout << "The first part doesn't work\n";
   /*
   std::deque<int>     d;
   std::list<int>      l;
   std::vector<int>    v;

   const std::vector<std::function<void(int)>> consumers { 
            consumer(d), consumer(l), consumer(v) };
   for (std::size_t i {0}; i< 10; ++i) {
      for (auto &&consume : consumers) {
         consume(i);
      }
   }

   print(d);
   print(l);
   print(v);
  */
   {
      auto twice ([] (int i) {return i * 2; });
      auto thrice ([] (int i) { return i * 3; });

      auto combined (
            concat(twice, thrice, std::plus<int>{})
      );
      std::cout <<combined(2,3) << '\n';
   }
   {
      std::cout << "There are a lot of tasks, which lead to repetitive "
         << "code. A lot of repetitive code can be eliminated "
         << "easily using lambda expressions and a lambda expression "
         << "helper that wraps such repetitive tasks is created very "
         << "quickly. In this section, we will play with lambda "
         << "expressions in order to forward a single call with all its "
         << "parameters to multiple receivers. This is going to happen "
         << "without any data structures in between, so the compiler "
         << "has a simple job to generate a binary without overhead.\n";

      auto f (brace_print<char>('(',')'));
      auto g (brace_print<char>('[',']'));
      auto h (brace_print<char>('{','}'));
      auto nl ([](auto) {std::cout << '\n';});

      auto call_fgh (multicall (f,g,h,nl));

      for_each(call_fgh,1,2,3,4,5);
   }
   {
       std::cout << "Implementing std::transform_if function. In this "
                 << "section, we are going to implement this function. "
                 << "It would be easy to do this by just implementing "
                 << "a function that iterates over the ranges while"
                 << " copying all the items that are selected by a "
                 << " predicate function and transforming them in"
                 << " between.\n";

       std::istream_iterator<int> it {std::cin};
       std::istream_iterator<int> end_it;

       auto even ( [] (int i) { return i % 2 == 0;});
       auto twice ( [] (int i) { return i* 2; });

       auto copy_and_advance( [] (auto it, auto input) {
            *it = input;
            return ++it;
       });

       std::accumulate(it, end_it, 
               std::ostream_iterator<int> {std::cout , ", "},
               filter(even) (
                   map (twice) (
                       copy_and_advance
                       )
                   )
               );

       std::cout << '\n';
   }
   {
       std::cout << "Generating cartesian product pairs of any input"
           << " at compile time";

       /*
       constexpr auto call_start(
               [=] (auto f, auto x, auto ...rest) constexpr {
               (void)std::initializer_list<int> {
               (((x < rest)
                 ? (void)f (x, rest)
                 : (void)0)
                ,0)...
               };
       });

       constexpr auto cartesian ([=](auto ...xs) constexpr {
           return [=] (auto f) constexpr {
               (void)std::initializer_list<int> {
                   ((void)call_cart(f, xs, xs...), 0)...
                   };
           };
       });

       constexpr auto print_cart (cartesian(1, 2, 3));

       print_cart(print);
       */
   }
}

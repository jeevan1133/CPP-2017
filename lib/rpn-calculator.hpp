#include <stack>
#include <iterator>
#include <map>
#include <sstream>
#include <cassert>
#include <vector>
#include <stdexcept>
#include <cmath>

using namespace std;

double add(double a, double b)
{
   return a + b;
}

double mult(double a, double b)
{
   return a * b;
}
double diff(double a, double b)
{
   return a - b;
}
double divide(double a, double b)
{
   return a / b;
}

double power(double a, double b)
{
   return pow(a, b);
}
template <typename IT>
double evaluate_rpn(IT it, IT end) 
{
   stack<double> val_stack;
   auto pop_stack ([&val_stack]() {
         auto r (val_stack.top());
         val_stack.pop();
         return r;
         });
   /*
   map<string, double (*)(double, double)> ops {
           {"+", [](double a, double b) { return a + b; }},
           {"-", [](double a, double b) { return a - b; }},
           {"*", [](double a, double b) { return a * b; }},
           {"/", [](double a, double b) { return a / b; }},
           {"^", [](double a, double b) { return pow(a, b); }},
           {"%", [](double a, double b) { return fmod(a, b); }},
   };
   */
   map<string, double(*)(double, double)> ops {
         {"+", add},
         {"-", diff},
         {"*", mult},
         {"/", divide},
         {"^", power}
   };

   for (; it != end; ++it) {
      stringstream ss {*it};
      if (double val; ss >> val) {
         val_stack.push(val);
      }
      else {
         const auto r {pop_stack()};
         const auto l {pop_stack()};
         try {
            const auto &op (ops.at(*it));
            const double result {op(l, r)};
            val_stack.push(result);
         }
         catch(const out_of_range &e){
            throw invalid_argument(*it);
         }
      }
   }
   return val_stack.top();
}

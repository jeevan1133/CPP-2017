#include "lib/zip-iterator.hpp"
#include <iostream>
#include <valarray>

int main()
{
   using namespace std;
   vector<double> a { 1.0, 2.0, 3.0 };
   vector<double> b { 4.0, 5.0, 6.0 };
   zipper zipped {a, b};

   const auto add_product ([] (double sum, const auto &p) {
         return sum + p.first * p.second;
   });

   const auto dot_product (accumulate(begin(zipped), 
            end(zipped), 0.0, add_product));

   cout << dot_product << '\n';
   {
      cout << "\nUsing std::valarray\n";
      std::valarray<double> a { 1.0, 2.0, 3.0 };
      std::valarray<double> b {4.0, 5.0 , 6.0 };

      std::cout << (a *b).sum() << '\n';
   }
}

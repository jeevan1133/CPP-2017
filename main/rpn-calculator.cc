#include "lib/rpn-calculator.hpp"
#include <iostream>

using namespace std;

int main() {
   try {
      cout << evaluate_rpn(std::istream_iterator<string> {cin}, {})
                << '\n';
   }
   catch (const invalid_argument &e) {
      cout << "invalid operator: " << e.what() << endl;
   }
}

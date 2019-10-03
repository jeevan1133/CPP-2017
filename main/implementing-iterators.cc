#include <iostream>
#include <sstream>
#include <string>
#include <iterator>
#include <deque>
#include <algorithm>

class num_iterator { 
   int i;
   public:
      explicit num_iterator(int pos = 0) : i(pos) {}

      int operator*() const { return i; }

      num_iterator& operator++() {
         ++i;
         return *this;
      }

      bool operator!=(const num_iterator& other) const {
         return i != other.i;
      }

      bool operator==(const num_iterator& other) const {
         return (!(*this != other));
      }
};

namespace std {
   template<> struct iterator_traits<num_iterator> {
      using iterator_category = std::forward_iterator_tag;
      using value_type        = int;
   };
}

class num_range {
   int a;
   int b;
   public:
      num_range(int from, int to) : a{from}, b{to} {}

      num_iterator begin() const { return num_iterator{a}; }
      num_iterator end() const { return num_iterator{b}; }

};

int main()
{
   std::stringstream ss;
   ss << "This is an example of how for loop is implemented\n"
      << "with custom iterable range and custom iterator\n"
      << "for (auto & a : container) { ... }\n"
      << "is actually sugar coated form of\n"
      << "{\n"
      << "\tauto && __range = array_or_vector_or_map_or_list\n"
      << "\tauto __begin = std::begin(__range);\n"
      << "\tauto __end   = std::end(__range);\n"
      << "\tfor ( ; __begin != __end; ++__begin) {\n"
      << "\t\tint i = *__begin;\n"
      << "\t\tsum += i;\n" 
      << "\t}\n"
      << "}\n"
      << "Therefore, we need to override these operators "
      << "in our custom iterator\n"
      << "\t- operator*()\n"
      << "\t- operator++()\n"
      << "\t- operator!=()\n"
      << "For the custom container(range) class, we need to override\n"
      << "\t-begin()\n"
      << "\t-end()\n";

   std::cout << ss.str();
   for (int i: num_range{100, 110}) {
      std::cout << i << ", ";
   }

   std::cout << "\nMaking your own iterators compatible with STL"
      << "iterator categories\n";
   {
      num_range r {100,100};
      auto [min_it, max_it] (std::minmax_element(std::begin(r), std::end(r)));
      std::cout << *min_it << " - " << *max_it << '\n';
   }

   std::cout << "Using iterator adapters to fill generic data structures"
      << "\nIn a lot of situations, we want to fill any container"
      << "with masses of data, but the data source and the "
      << "container have no common interface. In such a "
      << "situation, we would need to write our own hand-crafted "
      << "algorithms that just deal with the question of how to "
      << "shove data from the source to the sink. Usually, this "
      << "distracts us from our actual work of solving a "
      << "specific problem.\n\n\n";
   {
      std::istream_iterator<int> it_cin {std::cin};
      std::istream_iterator<int> end_cin;
      std::deque<int> v;
      std::copy(it_cin, end_cin, std::back_inserter(v));
      std::istringstream sstr {"123 456 789"};
      auto deque_middle (std::next(std::begin(v), 
               static_cast<int>(v.size())/2)); 
      std::copy(std::istream_iterator<int>{sstr}, {}, 
            std::inserter(v, deque_middle));
      std::cout << "After istream_iterator\n";
      std::initializer_list<int> il2 {-1, -2, -3};
      std::copy(std::begin(il2), std::end(il2), std::front_inserter(v));
      std::copy(std::begin(v), std::end(v), 
            std::ostream_iterator<int> {std::cout, ", "});
      std::cout << '\n';
   }

}

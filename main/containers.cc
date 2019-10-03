#include "lib/containers.hpp"
#include <iostream>

#define cout std::cout 

template<typename T>
void printIt(T &t, const std::string &s = "") {
   cout << s << std::endl;
   for (auto n : t) {
      cout << n << " ";
   }
   cout << '\n';
}

   template <typename M>
void print(const M &m)
{
   cout << "Race placement:\n";
   for(const auto &[placement, driver] : m) {
      cout << placement << ": " << driver << '\n';
   }
}

struct coord {
   int x;
   int y;
};
bool operator==(const coord &l, const coord &r) {
   cout << "IN==\n";
   return (l.x == r.x && l.y == r.y);
}

namespace std
{
   template <>
      struct hash<coord>
      {
         using argument_type = coord;
         using result_type   = size_t;
         result_type operator()(const argument_type &c) const
         {
            cout << "Inside ()\n";
            return static_cast<result_type>(c.x)
               + static_cast<result_type>(c.y);
         } 
      };
}

int main() {
   {
      std::vector<int> v {1,2,3,4,5,2,6,2,4,8};
      const auto new_end (std::remove(std::begin(v), std::end(v), 2));
      v.erase(new_end, end(v));
      v.push_back(2);
      printIt(v, "Removing 2s");
      cout << "Size: " << v.size()
         <<" , Capacity: " << v.capacity() << '\n';
      const auto odd([](int i){return !(i%2);});

      v.erase(std::remove_if(std::begin(v), std::end(v), odd),std::end(v));
      printIt(v, "removing odd numbers");
      cout << "Size: " << v.size()
         <<" , Capacity: " << v.capacity() << '\n';

      v.shrink_to_fit();
      cout << "After shrinking" << '\n';
      cout << "Size: " << v.size()
         <<" , Capacity: " << v.capacity() << '\n';
   }
   cout << "Deleting items from an unsorted std::vector in O(1)\n";
   {
      std::vector<int> v {123, 456, 789, 100, 200};
      quick_remove_at(v, std::find(std::begin(v),std::end(v), 123));
      printIt(v, "quick_remove_at");

   }

   cout << "********************************************************\n";
   cout << "Accessing vector instances the fast or the safe way\n";
   {
      const size_t container_size {1000};
      std::vector<int> v (container_size, 123);

      cout << "Out of range element value: "
         << v[container_size+10] << '\n';
      try {
         cout << "Out of range element can't be accessed: "
            << v.at(container_size + 10) << '\n';
      } catch (const std::out_of_range &e) {
         cout << e.what() << '\n';
      }     
   }

   cout << "********************************************************\n";
   cout << "Keeping std::vector instances sorted\n";
   {
      std::vector<std::string> v {"some", "random","words",
         "without", "order", "aaa",
         "yyy"};
      assert(false == std::is_sorted(std::begin(v), std::end(v)));
      std::sort(std::begin(v), std::end(v));
      assert(true == std::is_sorted(std::begin(v), std::end(v)));
      insert_sorted(v, "foobar");
      insert_sorted(v, "yyy");
      printIt(v, "After insert couple word");
   }
   cout << "********************************************************\n";
   cout << "Inserting items efficiently and conditionally into map\n";
   {
      using namespace std::literals;
      std::list<billionaire> billionaires {
         {"Bill Gates", 86.0, "USA"},
            {"Warren Buffet", 75.6, "USA"},
            {"Jeff Bezos", 72.8, "USA"},
            {"Amancio Ortega", 71.3, "Spain"},
            {"Mark Zuckerberg", 56.0, "USA"},
            {"Carlos Slim", 54.5, "Mexico"},
            // ...
            {"Bernard Arnault", 41.5, "France"},
            // ...
            {"Liliane Bettencourt", 39.5, "France"},
            // ...
            {"Wang Jianlin", 31.3, "China"},
            {"Li Ka-shing", 31.2, "Hong Kong"}
      };             
      std::map<std::string, std::pair<const billionaire, size_t>> m;
      for (const auto &b : billionaires) {
         auto [iterator, success] = m.try_emplace(b.country, b, 1);
         if (!success) {
            iterator->second.second += 1;
         }
      }
      for (const auto &[key, value]: m) {
         const auto &[b, count] = value;
         cout << b.country << " : " << count
            << " billionaires. Riches is "
            << b.name << " with $" << b.dollars
            << " B\n";
      }
   }
   cout << "********************************************************\n";
   cout << "Inserting in amortized O(1) insertion time in map using hint\n";
   {
      std::map<std::string, size_t> m {{"b", 1}, {"c", 2}, {"d",3}};
      /*
       * We will insert multiple items now, and for each item 
       * we will use an insertion hint. Since we have no hint 
       * in the beginning to start with, we will just do the 
       * first insertion pointing to the end iterator of the map.
       *
       */
      auto insert_it (std::end(m));
      for (const auto &s : {"y", "x", "z", "w"}) {
         insert_it = m.insert(insert_it, {s, 1});
      }
      for (const auto & [key, value] : m) {
         cout << "\"" << key << "\": " << value << ", ";
      }
      cout << '\n'; 
   }
   cout << "********************************************************\n";
   cout << "Efficiently modifying keys of std::map items\n";
   {
      std::map<int, std::string> race_placement {
         {1, "Mario"}, {2, "Luigi"}, {3, "Bowser"},
            {4, "Peach"}, {5, "Yoshi"}, {6, "Koopa"},
            {7, "Toad"}, {8, "Donkey Kong Jr."}
      };
      print(race_placement);
      {
         auto a (race_placement.extract(3));
         auto b (race_placement.extract(8));
         std::swap(a.key(), b.key());
         // Needs to have move semantics
         race_placement.insert(move(a));
         race_placement.insert(move(b));
      }
      cout << "After Swapping\n";
      print(race_placement);
   }
   cout << "********************************************************\n";
   cout << "Using std::unordered_map with custom types\n";
   {
      std::unordered_map<coord, int> m {{{0, 0}, 1}, {{0, 1}, 2},
                                               {{2, 1}, 3}};
      for (const auto & [key, value] : m) {
         cout << "{(" << key.x << ", " << key.y
                   << "): " << value << "} ";
      }
      cout << '\n';
   }
   cout << "********************************************************\n";
   cout << "Filtering duplicates from user input and"
        << "printing them in alphabetical order with std::set\n";
   {
      std::set<std::string> s;
      std::istream_iterator<std::string> it {std::cin};
      std::istream_iterator<std::string> end;
      std::copy(it, end, std::inserter(s, s.end()));
      printIt(s, "implementing set");

   }
}

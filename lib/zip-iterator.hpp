#include <vector>
#include <numeric>

class zip_iterator {
   private:
      using it_type = std::vector<double>::iterator;
      it_type it1;
      it_type it2;

   public:
      zip_iterator(it_type it1_, it_type it2_) : 
         it1(it1_), it2(it2_) {}

      zip_iterator& operator++() {
         ++it1;
         ++it2;
         return *this;
      }

      bool operator!=(const zip_iterator& o) const {
         return it1 != o.it1 && it2 != o.it2;
      }

      bool operator==(const zip_iterator& o) const {
         return !(operator!=(o));
      }

      std::pair<double, double> operator*() const {
         return {*it1, *it2};
      }
};

namespace std {
   template <>
      struct iterator_traits<zip_iterator> {
         using iterator_category = std::forward_iterator_tag;
         using value_type = std::pair<double, double>;
         using difference_type = long int;
      }; 
}

class zipper {
   using vec_type = std::vector<double>;
   vec_type &vec1;
   vec_type &vec2;

   public:
      zipper(vec_type &va, vec_type &vb) : vec1(va), vec2(vb) {}

      zip_iterator begin() const {
         return {std::begin(vec1), std::begin(vec2)};
      }

      zip_iterator end() const {
         return {std::end(vec2), std::end(vec2)};
      }
};

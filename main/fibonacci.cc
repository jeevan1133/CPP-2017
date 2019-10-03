#include <iostream>

class fib
{
   private:
      size_t i {0};
      size_t a {0};
      size_t b {1};

   public:
      fib() = default;
      explicit fib(size_t i_) : i{i_} {}
      size_t operator*() const { return b; }
      fib& operator++() {
         const size_t old_b {b};
         b += a;
         a = old_b;
         ++i;
         return *this;
      }

      bool operator!=(const fib& o) const {return i != o.i; }
      bool operator==(const fib& o) const {return (!(operator!=(o)));}
};

class fib_range
{
   size_t end_n;
   public:
   fib_range(size_t end_n_) : end_n{end_n_} {}

   fib begin() const { return fib(); }
   fib end() const { return fib{end_n}; }
};

int main()
{
   for (size_t i : fib_range(10)) {
      std::cout << i << ", ";
   }
   std::cout << '\n';
}

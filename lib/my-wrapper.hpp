#ifndef LIB_MY_WRAPPER_H_
#define LIB_MY_WRAPPER_H_

#include <iostream>

template <typename T1, typename T2, typename T3>
class my_wrapper {
   private:
      T1 t1;
      T2 t2;
      T3 t3;

   public:
      my_wrapper(T1 t1_, T2 t2_, T3 t3_) : t1{t1_}, t2{t2_}, t3{t3_} {

      }
      
      ~my_wrapper() {
         std::cout << "My wrapper destructed" << '\n';
      }

      T1 getT1() {
         return t1;
      }
};
#endif

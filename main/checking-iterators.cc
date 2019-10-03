#include <iostream>
#include <vector>

int main()
{
   std::vector<int> v {1,2,3};
   /* We apply shrink_to_fit() on the vector in order to ensure that its
    * capacity is really 3, as its implementation might allocate more
    * memory than necessary as a little reserve to make future item
    * insertions faster:
    */
   v.shrink_to_fit();
   const auto it (std::begin(v));

   std::cout << *it << '\n';
   /* appending a new number to the vector. As the vector is not large 
    * enough to take another number, it will automatically increase 
    * its size. It does this by allocating a new and larger chunk of
    * memory, moving all the existing items to that new chunk and 
    * then deleting the old memory chunk
    */
   v.push_back(123);

   std::cout << *it << '\n';

}

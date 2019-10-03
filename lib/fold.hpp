#include <algorithm>
#include <utility>
#include <set>

/* This template returns the sum of given arbitrary args
 * int x = sum(1,2,3,4,5);
 * and x is 15
 * int x = sum();
 *  and x is 0
 */
template <typename ... Ts>
auto sum(Ts ... ts)
{
   return (ts + ... + 0);
}

/* This template returns the product of given arbitrary args
 * int x = sum(1,2,3);
 * and x is 6
 * int x = sum();
 * and x is 1
 */

template <typename ... Ts>
auto product(Ts ... ts)
{
   return (ts * ... * 1);
}

/* This template matches ranges against individual items
 * whether some range contains at least one of the values 
 * we provide as variadic parameters
 * matches("abcdefg", 'a','b') //returns 2
 * matches("abcdefg", 'a','b','x','y') // returns 2
 */
template <typename R, typename ... Ts>
auto matches(const R& range, Ts ... ts)
{
   return (std::count(std::begin(range), std::end(range), ts) + ... );
}

/* This template inserts items into the set
 * T is the set
 * U is outgoing parameter
 * Ts is arbitrary number of arguments that are inserted into the set
 * std::set<int> my_set {1,2,3,4}
 * insert_all(my_set,4,5,6,8)
 * returns {1,2,3,4,5,6,8}
 */
template <typename T, typename U, typename ... Ts>
T insert_all(T &&set, U &u, Ts ... ts) 
{
   u = (set.insert(ts).second && ...);
   //(set.insert(ts), ...);
   return set;
}


template <typename T, typename U, typename ... Ts>
T insert_all_vec(T &&vec, U &u, Ts ... ts) 
{
   (vec.push_back(ts), ...);
   return vec;
}


/* Same as above however this doesn't copy the parameter 
 * but moves the old value to the passed parameter
 */
template <typename T, typename U, typename ... Ts>
T insert_all_alt(T &&set, U &u, Ts ... ts)
{
   u = (set.insert(ts).second && ...);
   return std::move(set);
}

/* This template checks if all the parameters are within a given range
 * within(10,20,1,15,25) // false
 */
template <typename T, typename ... Ts>
bool within(T min, T max, Ts ... ts)
{
   return ((min <= ts && ts <= max) && ...);
}

template<typename T>
struct insert {
    template <class Q, typename U, typename ... Ts>
    Q insert_generic (Q &&set, U &u, Ts ... ts) {
        if constexpr (std::is_same_v<Q, std::vector<T>>) {
           (set.push_back(ts), ...);
        }
        else if constexpr (std::is_same_v<Q, std::set<T>>) {
            (set.insert(ts), ... );
        }
        else {
           u = false;
        }
        return std::forward<Q>(set);
    }
};

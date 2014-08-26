// Multiples of 3 and 5
// If we list all the natural numbers below 10 that are multiples of 3 or 5, we get 3, 5, 6 and 9. The sum of these multiples is 23.
// Find the sum of all the multiples of 3 or 5 below 1000.

// Let's use STL! Just for fun, as there are simpler solutions.

#include <iostream>
#include <algorithm>
#include <vector>

int main()
{
    std::vector<int> v(999);
    std::iota(v.begin(), v.end(), 1);

    int result = std::accumulate(v.begin(), v.end(), 0, [](int sum, int elem)
        {   return (!(elem % 3) || !(elem % 5)) ? sum + elem : sum;   });
 
    std::cout << "Sum: " << result << '\n';
}
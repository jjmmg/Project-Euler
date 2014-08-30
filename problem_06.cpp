// Sum square difference
// The sum of the squares of the first ten natural numbers is,
// 1^2 + 2^2 + ... + 10^2 = 385
// The square of the sum of the first ten natural numbers is,
// (1 + 2 + ... + 10)^2 = 552 = 3025
// Hence the difference between the sum of the squares of the first ten natural numbers and the square of the sum is 3025 - 385 = 2640.
// Find the difference between the sum of the squares of the first one hundred natural numbers and the square of the sum.

#include <iostream>
#include <numeric>
#include <vector>

int main()
{
    std::vector<int> v(100);
    std::iota(v.begin(), v.end(), 1);

    long result{0};
    for (auto it=v.begin(); it!=v.end(); ++it)
    {
        int nbr{*it};
        result = std::accumulate(it+1,
                                 v.end(),
                                 result,
                                 [&nbr](const int& sum, const int& elem)
                                 { return sum + 2 * nbr * elem; });
    }
 
    std::cout << "Difference: " << result << '\n';
}
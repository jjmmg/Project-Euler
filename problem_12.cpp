// The sequence of triangle numbers is generated by adding the natural numbers. So the 7th triangle number would be 1 + 2 + 3 + 4 + 5 + 6 + 7 = 28. The first ten terms would be:
//   1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...
// Let us list the factors of the first seven triangle numbers:
//   
//    1: 1
//    3: 1,3
//    6: 1,2,3,6
//   10: 1,2,5,10
//   15: 1,3,5,15
//   21: 1,3,7,21
//   28: 1,2,4,7,14,28
// We can see that 28 is the first triangle number to have over five divisors.
// What is the value of the first triangle number to have over five hundred divisors?

#include <iostream>
#include <chrono>

template <typename T, typename U>
inline int factor_rep(T& nbr, U factor)
{
    int times{0};
    for (; !(nbr%factor); ++times) nbr /= factor;
    return times;
}

template <typename T>
inline int count_factors(T nbr)
{
    int divisors {factor_rep(nbr,2) + 1};
    divisors *= factor_rep(nbr,3) + 1; // * because of combinations with previous factor

    // 6k +- 1
    for (int i{5}; i*i<=nbr; i+=6)
    {
        divisors *= factor_rep(nbr,i) + 1;
        divisors *= factor_rep(nbr,i+2) + 1;
    }

    // one last prime factor
    if (nbr != 1)
        divisors *= 2;

    return divisors;
}

int main()
{
    auto start = std::chrono::steady_clock::now();

    int nbr{0}, div{0};
    while (div <= 500)
    {
        ++nbr;
        // triangle_number[nbr] = nbr*(nbr+1)/2
        int first{nbr}, second{nbr+1};
        nbr & 0x1 ? second/=2 : first/=2;
        div = count_factors(first) * count_factors(second);
    }
 
    std::cout << "Triangle number: " << nbr*(nbr+1)/2 << "\n";

    std::cout << std::chrono::duration<double, std::milli> (std::chrono::steady_clock::now() - start).count() << " ms\n";
}

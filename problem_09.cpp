// Special Pythagorean triplet
// A Pythagorean triplet is a set of three natural numbers, a < b < c, for which,
//     a^2 + b^2 = c^2
// For example, 3^2 + 4^2 = 9 + 16 = 25 = 5^2.
// There exists exactly one Pythagorean triplet for which a + b + c = 1000.
// Find the product abc.

// Use long long to allow using really big numbers for the sum

#include <iostream>

int main()
{
    constexpr long long N = 1000LL;
    constexpr long long A_LIM = N/3LL; // a < b < c,  so "a" will alays be less than a third of N
    constexpr long long B_LIM = N/2LL; // a < b < c,  so "b" will alays be less than half N
   
    long long a, b, c;

    for (a=1; a<A_LIM; ++a)
    {
        for (b=a+1; b<B_LIM; ++b)
        {
            c = N - a - b;
            if ((a*a + b*b == c*c) && (a + b + c == N))
            {
                std::cout << "Product: " << a * b * c << "\n";
                return 0;
            }
        }
    }
}
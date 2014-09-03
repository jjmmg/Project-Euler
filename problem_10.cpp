// Summation of primes
// The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.
// Find the sum of all the primes below two million.

#include <iostream>

template <typename T>
inline bool is_prime(const T& nbr)
{
    if (nbr==2 || nbr==3 || nbr==5 || nbr==7)
        return true;
    if (!(nbr & 0x1) || nbr<2)
        return false;
    for (T i{3}; i*i<=nbr; i+=2)
        if (nbr % i == 0)
            return false;
    return true;
}

int main()
{
    constexpr int MAX{2000000};
    int count{1};
    long sum{0};

    while (++count<MAX)
        if (is_prime(count))
            sum += count;

    std::cout << "Sum: " << sum << "\n";
    return 0;
}
// What is the largest prime factor of the number 600851475143 ?

#include <iostream>

int main()
{
    const long long N {600851475143LL};
    long long nbr {N};
    long long largest_prime {2};
    for (long long i=3; i*i<=N; i+=2)
    {
        if (nbr % i == 0)
        {
            largest_prime = i;
            nbr /= i;
        }
    }

    std::cout << "Largest prime: " << largest_prime << "\n";
    return 0;
}
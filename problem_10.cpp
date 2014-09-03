// 10001st prime
// By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that the 6th prime is 13.
// What is the 10 001st prime number?

#include <iostream>

template <typename T>
inline bool is_prime(const T& nbr)
{

    for (T i{3}; i*i<=nbr; i+=2)
        if (nbr % i == 0)
            return false;
    return true;
}

int main()
{
    const int pos{10001};
    int count{1}, nbr{1};

    while (count<pos)
    {
        nbr += 2;
        if (is_prime(nbr))
            ++count;
    }

    std::cout << count << " prime number: " << nbr << "\n";
    return 0;
}

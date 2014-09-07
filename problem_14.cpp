// The following iterative sequence is defined for the set of positive integers:
//   n ? n/2 (n is even)
//   n ? 3n + 1 (n is odd)
// Using the rule above and starting with 13, we generate the following sequence:
//   13 ? 40 ? 20 ? 10 ? 5 ? 16 ? 8 ? 4 ? 2 ? 1
// It can be seen that this sequence (starting at 13 and finishing at 1) contains 10 terms. Although it has not been proved yet (Collatz Problem), it is thought that all starting numbers finish at 1.
// Which starting number, under one million, produces the longest chain?
// NOTE: Once the chain starts the terms are allowed to go above one million.

#include <iostream>
#include <chrono>

template<typename T>
inline T collatz_biggest_chain(T max)
{
    T longest_chain{T(1)};
    T result{T(1)};

    for (T nbr{T(2)}; nbr<max; ++nbr)
    {
        T chain_len{T(1)};
        for (T aux{nbr}; aux!=T(1); aux=(aux&0x1)?(T(3)*aux+T(1)):(aux>>1))
             ++chain_len;
        if (chain_len>longest_chain)
        {
             longest_chain = chain_len;
             result = nbr;
        }
    }
    return result;
}    

int main()
{
    auto start = std::chrono::steady_clock::now();

    const unsigned limit{1000000U};
    std::cout << "Number: " << collatz_biggest_chain(limit) << "\n";

    std::cout << std::chrono::duration<double, std::milli> (std::chrono::steady_clock::now() - start).count() << " ms\n";
}

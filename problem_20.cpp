// n! means n × (n - 1) × ... × 3 × 2 × 1
// For example, 10! = 10 × 9 × ... × 3 × 2 × 1 = 3628800,
// and the sum of the digits in the number 10! is 3 + 6 + 2 + 8 + 8 + 0 + 0 = 27.
// Find the sum of the digits in the number 100!

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <numeric>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <chrono>

std::string add(std::vector<std::string> nbr_str)
{
    constexpr int chunk{15}; // digits to add up at a time. It should take into account the size of the strings vector and long (or long long) maximum
    long div = std::pow(10, chunk); // 10^chunk
    long overflow{0L};
    std::string result{""};
    unsigned long max_size{0L};
    std::for_each(nbr_str.begin(), nbr_str.end(), [&max_size](std::string s) { max_size = std::max(s.size(), max_size); });
    for (int i{0}; i*chunk<max_size; ++i)
    {
        // Convert from string to long of "chunk" digits and add up.
        long sum{std::accumulate(nbr_str.begin(),
                                 nbr_str.end(),
                                 overflow,
                                 [i, chunk](long res, std::string s)
                                 {
                                     if (static_cast<int>(s.size())<=i*chunk) // no more digits for this number
                                         return res;
                                     int start = std::max(0, static_cast<int>(s.size())-(i+1)*chunk);
                                     int chars = std::min(chunk, static_cast<int>(s.size())-i*chunk);
                                     return res + std::stol(s.substr(start, chars));
                                 })};
        overflow = sum / div;  // carry beyond chunk size
        std::stringstream ss;
        int filling{(i+1)*chunk<max_size ? chunk : 0}; // do not remove left zeroes
        ss << std::setw(filling) << std::setfill('0') << (sum - overflow*div);
        result = ss.str() + result;
    }
    return result;
}

std::string multiply(std::string n1, std::string n2)
{
    // TODO check for 0 at the right end, remove them, multiply the left digits, and add the zeros to the right of the final result
    const int chunk{16}; // digits to multiply at a time by one digit of the other number
    long div=std::pow(10, chunk); // 10^chunk
    long overflow{0L};
    std::vector<std::string> nbr_str;
    std::string nbr1{n1.size()>n2.size() ? n2 : n1};
    std::string nbr2{n1.size()>n2.size() ? n1 : n2};
    
    // Convert from string to long of "chunk" digits and multiply.
    for (auto it=nbr1.crbegin(); it!=nbr1.crend(); ++it)
    {
        std::string result{""};
        long digit{*it-'0'};
        for (int i{0}; i*chunk<=nbr2.size(); ++i)
        {
            int start{0}, chars{chunk};
            if (nbr2.size() > (i+1)*chunk)
                start = nbr2.size()-(i+1)*chunk;
            else
                chars = nbr2.size()-i*chunk;
            long res{(chars!=0 ? (digit*std::stol(nbr2.substr(start,chars))) : 0) + overflow};
            overflow = res / div; // carry beyond chunk size
            std::stringstream ss;
            int filling{(i+1)*chunk<nbr2.size() ? chunk : 0}; // do not remove left zeroes
            ss << std::setw(filling) << std::setfill('0') << (res - overflow * div);
            result = ss.str() + result;
        }
        for (int i{0}; i<it-nbr1.rbegin(); ++i)
            result = result + "0";
        nbr_str.push_back(result);
    }
    return add(nbr_str);
}

std::string factorial(int nbr)
{
    std::string res{std::to_string(nbr)};
    for (int i{nbr-1}; i>1; --i)
        res = multiply(res, std::to_string(i));
    return res;
}

int main()
{
    auto start = std::chrono::steady_clock::now();

    const int nbr{100};
    std::string res{factorial(nbr)};
    int sum{std::accumulate(res.begin(), res.end(), 0, [](int r, char c) { return r + c - '0';})};
    std::cout << "Sum: " << sum << "\n";

    std::cout << std::chrono::duration<double, std::milli> (std::chrono::steady_clock::now() - start).count() << " ms\n";
}
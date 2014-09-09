// 2^15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.
// What is the sum of the digits of the number 21000?/Title of this code

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
    constexpr int chunk{16}; // digits to add up at a time. It should take into account the size of the strings vector and long (or long long) maximum
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
                                     int start{0}, end{chunk};
                                     if (s.size() > (i+1)*chunk)
                                         start = s.size()-(i+1)*chunk;
                                     else
                                         end = s.size()-i*chunk;
                                     return res + std::stol(s.substr(start, end));
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
    const int chunk{14}; // digits to multiply at a time by one digit of the other number
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

std::string power_2(int exp)
{
    std::string res{"2"};
    for (int i{1}; i<exp; ++i)
        res = multiply(res, "2");
    return res;
}

int main()
{
    auto start = std::chrono::steady_clock::now();

    const int exp{10000};
    std::string res{power_2(exp)};
    std::cout << "2^" << exp << ": "<< res << "\n";
    int sum{std::accumulate(res.begin(), res.end(), 0, [](int r, char c) { return r + c - '0';})};
    std::cout << "Sum: " << sum << "\n";

    std::cout << std::chrono::duration<double, std::milli> (std::chrono::steady_clock::now() - start).count() << " ms\n";
}
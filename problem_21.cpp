// Let d(n) be defined as the sum of proper divisors of n (numbers less than n which divide evenly into n).
// If d(a) = b and d(b) = a, where a ? b, then a and b are an amicable pair and each of a and b are called amicable numbers.
// For example, the proper divisors of 220 are 1, 2, 4, 5, 10, 11, 20, 22, 44, 55 and 110; therefore d(220) = 284. The proper divisors of 284 are 1, 2, 4, 71 and 142; so d(284) = 220.
// Evaluate the sum of all the amicable numbers under 10000.

#include <iostream>
#include <vector>
#include <numeric>
#include <chrono>

template <typename T>
inline int factor_rep(T& nbr, T factor)
{
    int times{0};
    for (; !(nbr%factor); ++times) nbr /= factor;
    return times;
}

template <typename T>
inline std::vector<T> get_factors(T nbr)
{
    T itself{nbr};
    std::vector<T> result{T{1}};
    auto check_factor = [&result](T& n, const T& f) {
        int reps{factor_rep(n, f)};
        for (int rep{0}; rep<reps; ++rep)
            result.push_back(f);
    };

    if (nbr>2) check_factor(nbr, T{2});
    if (nbr>3) check_factor(nbr, T{3});

    // 6k +- 1
    for (T i{5}; i*i<=nbr; i+=6)
    {
        check_factor(nbr, i);
        check_factor(nbr, i+2);
    }

    // one last prime factor
    if (nbr!=1 && nbr!=itself)
        result.push_back(nbr);

    return result;
}

template <typename T>
inline std::vector<T> get_divisors(T nbr)
{
    std::vector<T> res(get_factors(nbr));
    std::vector<T> aux;
    int len;
    do
    {
        len = res.size();
        aux.clear();
        for (auto it=res.begin()+1; it!=res.end(); ++it)
        {
            for (auto it_int=it; it_int!=res.end(); ++it_int)
            {
                T mul{*it * *it_int};
                if (mul<nbr && nbr%mul==0)
                    aux.push_back(mul);
            }
        }
        std::copy(aux.begin(), aux.end(), std::back_inserter(res));
        std::sort(res.begin(), res.end());
        res.erase(std::unique(res.begin(), res.end()), res.end());
    } while (len!=res.size());

    return res;
}

template <typename T>
inline bool is_amicable(const T& a, T& b)
{
    std::vector<T> a_div{get_divisors(a)};
    b = std::accumulate(a_div.begin(), a_div.end(), T{0});
    std::vector<T> b_div{get_divisors(b)};
    long b_div_sum{std::accumulate(b_div.begin(), b_div.end(), T{0})};
    return (b>a && a==b_div_sum);
}

int main()
{
    auto start = std::chrono::steady_clock::now();

    typedef long type;
    std::vector<type> r;
    type b;
    for (type a{1}; a<10000; ++a)
        if (is_amicable(a, b))
        {
            r.push_back(a);
            r.push_back(b);
        }

    std::cout << "Sum: " << std::accumulate(r.begin(), r.end(), type{0}) << "\n";
    
    std::cout << std::chrono::duration<double, std::milli> (std::chrono::steady_clock::now() - start).count() << " ms\n";
}
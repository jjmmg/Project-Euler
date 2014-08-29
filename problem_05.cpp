// Smallest multiple
// 2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.
// What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?

#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>
#include <functional>
#include <iterator>

int main() {
    std::vector<int> v(20);
    std::iota(v.begin(), v.end(), 1);
    std::vector<int> res{};

    while (!v.empty())
    {
    	auto elem = v.back();
    	auto multiple = [elem](int x) { return elem % x == 0;};
        v.pop_back();
        res.push_back(elem);
        v.erase(std::remove(v.begin(), v.end(), 1), v.end());

        std::vector<int> rem;
        std::copy_if(v.rbegin(), v.rend(), std::back_inserter(rem), multiple);
        if (rem.empty())
            continue;

        std::for_each(v.begin(), v.end(),
                      [&rem](int &n)
                      {
                          for (const auto &elem : rem)
                              if (n % elem == 0)
                              {
                                  n /= elem;
                                  break;
                              }
                      });

        std::sort(v.begin(), v.end());
        v.erase(std::unique(v.begin(), v.end()), v.end());
    }

    std::cout << "Smallest multiple: " << std::accumulate(res.begin(), res.end(), 1, [](int x, int y) { return x*y; }) << '\n';

    std::cout << "********************************************************************************" << '\n';
    return 0;
}
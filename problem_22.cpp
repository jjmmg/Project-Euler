#include <iostream>
#include <fstream>
#include <string>
#include <numeric>
#include <algorithm>
#include <vector>
#include <iterator>
#include <chrono>

using std::string;
using std::vector;
using std::accumulate;
using std::sort;

inline vector<string> read_file(const string& path)
{
    std::ifstream file(path);
    if (!file)
    {
        std::cerr << "Unable to open file" << "\n";
        std::exit(-1);
    }

    vector<string> words;
    string token;
    while (std::getline(file, token, ',')) // token = "XXXX"
    {
        token.erase(0,1); // remove fist "
        token.erase(token.length()-1, 1); // remove last "
        words.push_back(token);
    }

    return words;
}

inline int sum_chars(const string& w)
{
    const static int offset {'A'-1};
    return accumulate(w.begin(), w.end(), 0, [](int r, char c) { return r+c-offset; });
}

inline int total_score(const vector<string>& ws)
{
    int counter {1};
    return accumulate(ws.begin(),
                      ws.end(),
                      0,
                      [&counter](int r, string w) { return r+(sum_chars(w)*counter++); });
}

int main()
{
    auto start = std::chrono::steady_clock::now();

    vector<string> words {read_file("names.txt")};
    sort(words.begin(), words.end());
    std::cout << "Total score: " << total_score(words) << "\n";

    std::cout << std::chrono::duration<double, std::milli> (std::chrono::steady_clock::now() - start).count() << "ms" << "\n";
}

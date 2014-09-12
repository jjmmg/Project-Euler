// You are given the following information, but you may prefer to do some research for yourself.
//
//   1 Jan 1900 was a Monday.
//
//   Thirty days has September,
//   April, June and November.
//   All the rest have thirty-one,
//   Saving February alone,
//   Which has twenty-eight, rain or shine.
//   And on leap years, twenty-nine.
//
//   A leap year occurs on any year evenly divisible by 4, but not on a century unless it is divisible by 400.
//
// How many Sundays fell on the first of the month during the twentieth century (1 Jan 1901 to 31 Dec 2000)?

#include <iostream>
#include <cmath>
#include <chrono>

int day_of_week(int year, int month, int day)
{
    // Gaussian algorithm http://calendars.wikia.com/wiki/Calculating_the_day_of_the_week
    int Y{(month < 3) ? year-1 : year};
    int d{day};
    int m{(month - 3) % 12 + 1};
    int y{Y % 100};
    int c{(Y - y) / 100};
    return (d + static_cast<int>(std::floor(2.6*m-0.2)) + y + y/4 + c/4 -2*c) % 7;
}

long days_week_matching_days_month(int day_week, int day_month, int start_year, int end_year)
{
    long total{0L};
    for (int year{start_year}; year<end_year; ++year)
        for (int month{1}; month<=12; ++month)
            if (day_of_week(year, month, day_month) == day_week)
                ++total;
    return total;
}
 
int main()
{
    auto start = std::chrono::steady_clock::now();
    
    std::cout << "Result: " << days_week_matching_days_month(0, 1, 1901, 2000) << "\n";

    std::cout << std::chrono::duration<double, std::milli> (std::chrono::steady_clock::now() - start).count() << "ms\n";
}
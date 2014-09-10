// If the numbers 1 to 5 are written out in words: one, two, three, four, five, then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in total.
// If all the numbers from 1 to 1000 (one thousand) inclusive were written out in words, how many letters would be used?
// NOTE: Do not count spaces or hyphens. For example, 342 (three hundred and forty-two) contains 23 letters and 115 (one hundred and fifteen) contains 20 letters. The use of "and" when writing out numbers is in compliance with British usage.

#include <iostream>
#include <vector>

int main()
{
//                            { "", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen" };
    std::vector<int> len_spec {  0,     3,     3,       5,      4,      4,     3,       5,       5,      4,     3,        6,        6,          8,          8,         7,         7,           9,          8,          8 };
//                            { "", "ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety" };
    std::vector<int> len_tens {  0,     3,        6,        6,       5,       5,       5,        7,         6,        6 };

    unsigned int res{0U};
    const unsigned int N{1000U};
    
    for (unsigned int i{1}; i<=N; ++i)
    {
        decltype(i) nbr{i};

        // Thousands
        res += len_spec[nbr/1000];
        if (i>=1000)
            res += 8; // "thousand"
        nbr = nbr % 1000;

        // Hundreds
        res += len_spec[nbr/100];
        if (i%1000!=0 && i>=100)
        {
            res += 7; // "hundred"
            if (i%100!=0)
                res += 3; // "and"
        }
        nbr = nbr % 100;

        // Tens and units
        if (nbr<len_spec.size())
            res += len_spec[nbr];
        else
            res = res + len_tens[nbr/10] + len_spec[nbr%10];
    }
    
    std::cout << "Result(" << N << "): " << res << "\n";

}
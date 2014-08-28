// Largest palindrome product
// A palindromic number reads the same both ways. The largest palindrome made from the product of two 2-digit numbers is 9009 = 91 × 99.
// Find the largest palindrome made from the product of two 3-digit numbers.

#include <iostream>

int main() {
	int largest_palindrome{0};
	auto is_palindrome = [](const int& nbr)
		{
			int aux{nbr}, reverse{0};
			while (aux != 0)
			{
				reverse = reverse * 10 + aux % 10;
				aux /= 10;
			}
			return reverse == nbr;
		};
	
	for (int nbr1{999}; nbr1>1; --nbr1)
	{
		for (int nbr2{nbr1}; nbr2>1; --nbr2)
		{
			if (is_palindrome(nbr1*nbr2))
			{
				int aux{nbr1*nbr2};
				if (aux > largest_palindrome)
					largest_palindrome = aux;
				break;
			}
		}
	}

	std::cout << "Largest palindrome: " << largest_palindrome << '\n';
	return 0;
}
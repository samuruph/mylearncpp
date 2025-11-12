#include <iostream>

template <typename T, typename U>
auto sub(T x, U y)
{
    return x - y;
}

/*
//If C++20 capable, you can use an abbreviated function template instead
auto sub(auto x, auto y)
{
	return x - y;
}
*/

int main()
{
	std::cout << sub(3, 2) << '\n';
	std::cout << sub(3.5, 2) << '\n';
	std::cout << sub(4, 1.5) << '\n';

	return 0;
}
#include <iostream>
#include <cstdarg>

using namespace std;

int solving_polynomial(int x, int pow_p, ...)
{
	int res = 0, koef = 0, dot = x;

	va_list factor;
	va_start(factor, pow_p);

	res = va_arg(factor, int);
	printf("Polynomial: ");
	cout << res;

	for (int i = 1; i <= pow_p; i++)
	{
		koef = va_arg(factor, int);
		cout << " + " << koef << "*x^" << i;

		res += koef * dot;
		dot *= x;
	}

	va_end(factor);
	cout << endl << "x = " << x << endl;
	return res;
}

int main()
{
	cout << solving_polynomial(10, 3, 5, 4, 6, 3);
	return 0;
}
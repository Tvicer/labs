#include <iostream>
#include <cstdlib>
#include <cstdarg>

using namespace std;

string work(const string& str1, const string& str2, int base)
{
	string res;

	int delta = int(str1.length() - str2.length());
	int i, num1 = 0, num2 = 0, num_res = 0, ost = 0;

	res = "0" + str1;

	for (i = str2.length() - 1; i >= 0; i--)
	{
		if (isdigit(str1[i + delta]))
			num1 = str1[i + delta] - '0';
		else if (isalpha(toupper(str1[i + delta])))
			num1 = toupper(str1[i + delta]) - 'A' + 10;

		if (isdigit(str2[i]))
			num2 = str2[i] - '0';
		else if (isalpha(toupper(str2[i])))
			num2 = toupper(str2[i]) - 'A' + 10;

		if ((num1 >= base) || (num2 >= base))
		{
			return res = "";
		}

		num_res = num1 + num2 + ost;
		ost = 0;

		if (num_res >= base)
		{
			num_res -= base;
			ost = 1;
		}

		if (num_res < 10)
			res[i + delta + 1] = num_res + '0';
		else
			res[i + delta + 1] = num_res - 10 + 'A';
	}

	while (ost)
	{
		if (isdigit(res[i + delta + 1]))
			num_res = res[i + delta + 1] - '0';
		else if (isalpha(toupper(res[i + delta + 1])))
			num_res = toupper(res[i + delta + 1]) - 'A' + 10;


		if (num_res >= base)
		{
			return res = "";
		}

		num_res += ost;
		ost = 0;

		if (num_res >= base)
		{
			num_res -= base;
			ost = 1;
		}

		if (num_res < 10)
			res[i + delta + 1] = num_res + '0';
		else
			res[i + delta + 1] = num_res - 10 + 'A';

		i--;
	}

	return res;
}

string summ(const string& str1, const string& str2, int base)
{
	string res;

	if (str1.length() >= str2.length())
		res = work(str1, str2, base);
	else
		res = work(str2, str1, base);

	while (res[0] == '0')
		res.erase(0, 1);

	return res;
}




string LongDivision(int base, int count, ...)
{
	va_list factor;
	string res;
	va_start(factor, count);

	if ((base < 2) || (base > 36) || (count < 0))
	{
		return "";
	}

	res = va_arg(factor, const char*);

	for (int i = 0; i < count - 1; i++)
	{
		res = summ(res, va_arg(factor, char*), base);
		if (res == "")
		{
			return "";
		}
	}

	va_end(factor);

	return res;
}



int main()
{
	cout << "Lab 1 Number 5 of Nosov Alexander M8O-211B-20" << endl;
	
	cout << "99999999 + 1 = " << LongDivision(10, 2, "99999999", "1") << endl;
	cout << "49A140F3 + 30B583 = " << LongDivision(16, 2, "49A140F3", "30B583") << endl;
	cout << "000000012 + 0000015 = " << LongDivision(10, 2, "000000012", "0000015") << endl;

	return 0;
}


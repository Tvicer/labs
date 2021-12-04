#include <iostream>
#include <vector>
#include <fstream>
#include <cstdarg> 
#include <string>

using namespace std;

vector<string> somefunc(int(find(const string&, const string&)), const string &sought, int num_of_par, ...)
{
	vector<string> result;
	string name, buf_str;
	ifstream file;
	va_list factor;

	va_start(factor, num_of_par);

	for (int i = 0; i < num_of_par; i++)
	{
		name = va_arg(factor, string);

		file.open(name);
		if (file.is_open())
		{
			while (getline(file, buf_str))
			{
				if (find(buf_str, sought))
				{
					result.push_back(name);
				}
			}
		}
		file.close();
	}
	va_end(factor);

	return result;
}

int search(const string &str, const string &sought)
{
	bool flag = false;
	int j = 0, k = 0;
	for (int i = 0; i <= str.length() - sought.length(); i++)
	{
		if (str[i] == sought[0])
		{
			flag = true;
			j = i + 1;
			k = 1;
			while ((k < sought.length()) && (flag))
			{
				if (str[j] != sought[k])
					flag = false;
				j++;
				k++;
			}
			if (flag)
			{
				return 1;
			}
		}
	}

	return 0;
}

int main()
{
	cout << "Lab 1 Number 1 of Nosov Alexander M8O-211B-20" << endl;

	string file1 = "test1.txt";
	string file2 = "test2.txt";

	string str = "lolkek";

	vector <string> names_res;

	names_res = somefunc(search, str, 2, file1, file2);
	cout << "Files with string:" << endl;
	for (vector<string>::iterator i = names_res.begin(); i != names_res.end(); i++)
	{
		cout << *i << endl;
	}
}

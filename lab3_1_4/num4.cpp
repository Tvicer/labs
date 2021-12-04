#include <iostream>
#include <fstream>

using namespace std;

int find_min_base(const string& num)
{
    int min_base = 0, temp = 0;
    for (int i = 0; i < num.length(); i++)
    {
        if (isdigit(num[i]))
            temp = num[i] - '0' + 1;
        else if (isalpha(num[i]))
            temp = toupper(num[i]) - 'A' + 10 + 1;
        else
            return -1;

        if (min_base < temp)
        {
            min_base = temp;
        }
    }

    return min_base;
}

int to_10cc(const string& num, int base)
{
    int res = 0;

    if (num[0] == '-')
        for (int i = 1; i < num.length(); i++)
        {
            res = res * base;
            if (isdigit(num[i]))
                res -= num[i] - '0';
            else
                res -= toupper(num[i]) - 'A' + 10;
        }
    else
        for (int i = 0; i < num.length(); i++)
        {
            res = res * base;
            if (isdigit(num[i]))
                res += num[i] - '0';
            else
                res += toupper(num[i]) - 'A' + 10;
        }

    return res;
}

int parsing_file(ifstream& in_f)
{
    string num_in_str;
    int base;

    ofstream out_f("output.txt");

    while (!in_f.eof())
    {
        in_f >> num_in_str;

        base = find_min_base(num_in_str);
        if (base == -1)
            return -1;
        out_f << num_in_str << "(" << base << ")" << " = " << to_10cc(num_in_str, base) << "(10)" << endl;
    }

    out_f.close();

    return 0;
}

int main(int argc, char* argv[])
{
    cout << "Lab 1 Number 4 of Nosov Alexander M8O-211B-20" << endl;

    if (argc == 1)
    {
        cout << "Enter your file!" << endl;
        return -1;
    }

    ifstream in_f(argv[1]);

    if (!in_f)
    {
        cout << "File opening error!" << endl;
        return -2;
    }

    if (parsing_file(in_f) == 0)
    {
        in_f.close();
        cout << "Completed successfully!";
        return 0;
    }
    else
    {
        in_f.close();
        cout << "Error! Incorrect symbol!";
        return -3;
    }

	return 0;
}
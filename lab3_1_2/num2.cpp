#include <iostream>
#include <cstdarg>


using namespace std;


struct Polygon
{
    int x, y;

    Polygon(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    Polygon()
    { 
        x = 0;
        y = 0; 
    }
};


int check_spin(const Polygon &p1, const Polygon &p2, const Polygon &p3)
{
    Polygon ab(p2.x - p1.x, p2.y - p1.y);
    Polygon bc(p3.x - p2.x, p3.y - p2.y);

    int spin = ab.x * bc.y - ab.y * bc.x;

    if (spin == 0)
    {
        return 0;
    }
    else
    {
        if (spin > 0)
            return 1;
        else
            return -1;
    }
}


int check_polygon(int count, ...)
{
    va_list factor;

    Polygon firstp, secondp, temp1, temp2, temp3;

    int flag = 0;

    va_start(factor, count);
    firstp = va_arg(factor, Polygon);
    secondp = va_arg(factor, Polygon);
    temp1 = firstp;
    temp2 = secondp;
    temp3 = va_arg(factor, Polygon);

    if (count < 3)
    {
        return -1;
    }

    flag = check_spin(temp1, temp2, temp3);

    for (int i = 3; i <= count; i++)
    {
        temp1 = temp2;
        temp2 = temp3;
        temp3 = va_arg(factor, Polygon);

        if ((flag != check_spin(temp1, temp2, temp3)) && check_spin(temp1, temp2, temp3) != 0)
        {
            return -1;
        }
    }

    if ((flag != check_spin(temp2, temp3, firstp)) && check_spin(temp2, temp3, firstp) != 0)
        return -1;
    else
    {
        if ((flag != check_spin(temp3, firstp, secondp)) && check_spin(temp3, firstp, secondp) != 0)
            return -1;
        else
            return 1;
    }

    va_end(factor);
}


int main()
{
    cout << "Lab 1 Number 2 of Nosov Alexander M8O-211B-20" << endl;

    Polygon point1(1, 1);
    Polygon point2(0, 3);
    Polygon point3(4, 8);
    Polygon point4(10, 0);
    Polygon point5(4, 0);

    int res = check_polygon(4, point1, point2, point3, point4, point5);

    if (res == 1)
        cout << "Polygon is convex!";
    else
        cout << "Polygon isn't convex!";

    return 0;
}
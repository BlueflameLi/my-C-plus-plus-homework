#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;

const double PI = 3.1415926;
class Circle
{
public:
    void setradius(double r);
    double area();
    double circumference();
    Circle(double);

private:
    double radius;
};
Circle::Circle(double r)
{
    setradius(r);
}
void Circle::setradius(double r)
{
    radius = r;
}
double Circle::area()
{
    return PI * radius * radius;
}
double Circle::circumference()
{
    return 2 * PI * radius;
}
int main()
{
    double r;
    cin >> r;
    Circle c(r);
    cout << fixed << setprecision(2) << 20 * c.area() + 35 * c.circumference() << endl;
    return 0;
}


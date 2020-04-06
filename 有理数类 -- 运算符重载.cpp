#include <iostream>
#include <cmath>
using namespace std;
class Rational
{
private:
	int numerator;	  //分子
	int denominator;  //分母
	void reduction(); //约分

public:
	Rational(int num, int denom); //构造

	Rational operator+(const Rational &rhs) const; //加法重载
	Rational operator-(const Rational &rhs) const; //减法重载
	Rational operator*(const Rational &rhs) const; //乘法重载
	Rational operator/(const Rational &rhs) const; //除法重载

	friend ostream &operator<<(ostream &os, const Rational &rhs); //输出重载
};

Rational::Rational(int num, int denom)
{
	numerator = num;
	denominator = denom;

	reduction();
}
void Rational::reduction()
{
	if (denominator < 0) //保证分母大于0
	{
		denominator = -denominator;
		numerator = -numerator;
	}

	int a = abs(numerator);
	int b = denominator;

	while (b) //欧几里得gcd
	{
		int r = a % b;
		a = b;
		b = r;
	}

	numerator /= a;
	denominator /= a;
}
Rational Rational::operator+(const Rational &rhs) const
{
	int a = denominator;
	int b = numerator;
	int c = rhs.denominator;
	int d = rhs.numerator;

	return Rational(b * c + a * d, a * c);
}
Rational Rational::operator-(const Rational &rhs) const
{
	int a = denominator;
	int b = numerator;
	int c = rhs.denominator;
	int d = rhs.numerator;

	return Rational(b * c - a * d, a * c);
}
Rational Rational::operator*(const Rational &rhs) const
{
	int a = denominator;
	int b = numerator;
	int c = rhs.denominator;
	int d = rhs.numerator;

	return Rational(b * d, a * c);
}
Rational Rational::operator/(const Rational &rhs) const
{
	int a = denominator;
	int b = numerator;
	int c = rhs.denominator;
	int d = rhs.numerator;

	return Rational(b * c, a * d);
}
ostream &operator<<(ostream &os, const Rational &rhs)
{
	if (rhs.denominator == 1)
		os << rhs.numerator;
	else
		os << rhs.numerator << '/' << rhs.denominator;
	return os;
}
int main()
{
	int a, b, c, d;
	cin >> a >> b >> c >> d;
	Rational A(a, b), B(c, d);
	cout << A << endl;
	cout << B << endl;
	cout << A + B << '\t' << A - B << '\t' << A * B << '\t' << A / B << endl;
	return 0;
}
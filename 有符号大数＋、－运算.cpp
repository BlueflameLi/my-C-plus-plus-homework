#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
class signed_Bignumber;
class Unsigned_Bignumber
{
private:
	string number;
	friend class signed_Bignumber;

public:
	Unsigned_Bignumber operator+(const Unsigned_Bignumber &rhs) const; //加法重载
	Unsigned_Bignumber operator-(const Unsigned_Bignumber &rhs) const; //减法重载

	friend istream &operator>>(istream &is, Unsigned_Bignumber &rhs); //输入重载
	friend istream &operator>>(istream &is, signed_Bignumber &rhs);
	friend ostream &operator<<(ostream &os, const Unsigned_Bignumber &rhs); //输出重载
	friend ostream &operator<<(ostream &os, const signed_Bignumber &rhs);
};

Unsigned_Bignumber Unsigned_Bignumber::operator+(const Unsigned_Bignumber &rhs) const
{
	int l1 = number.length();
	int l2 = rhs.number.length();
	Unsigned_Bignumber C;
	int t = 0; //进位
	for (int i = 0, j = 0; i < l1 || j < l2 || t; i++, j++)
	{
		if (i < l1)
			t += number[i] - '0';
		if (j < l2)
			t += rhs.number[i] - '0';
		C.number += t % 10 + '0';
		t /= 10;
	}
	return C;
}
Unsigned_Bignumber Unsigned_Bignumber::operator-(const Unsigned_Bignumber &rhs) const
{
	Unsigned_Bignumber C;
	if (number == rhs.number)
		C.number = "0";
	else
	{
		int t = 0;
		int tmp = 0; //退位
		int l1 = number.length();
		int l2 = rhs.number.length();
		for (int i = 0; i < l2; i++)
		{
			t = (number[i] - '0') - (rhs.number[i] - '0') - tmp;
			if (t < 0)
			{
				tmp = 1;
				t += 10;
			}
			else
				tmp = 0;
			C.number += t + '0';
		}
		for (int i = l2; i < l1; i++)
		{
			t = number[i] - '0' - tmp;
			if (t < 0)
			{
				tmp = 1;
				t += 10;
			}
			else
				tmp = 0;
			if (i < l1 - 1 || t)
				C.number += t + '0';
		}
	}
	return C;
}

istream &operator>>(istream &is, Unsigned_Bignumber &rhs)
{
	is >> rhs.number;
	int i = 0;
	int l = rhs.number.length();
	for (i = 0; i < l; i++)
		if (rhs.number[i] > '0' && rhs.number[i] <= '9')
			break;
	if (i == l)
		rhs.number = "0";
	else
	{
		rhs.number.erase(0, i);
		reverse(rhs.number.begin(), rhs.number.end());
	}
	return is;
}
ostream &operator<<(ostream &os, const Unsigned_Bignumber &rhs)
{
	string str;
	str.assign(rhs.number.rbegin(), rhs.number.rend());
	os << str;
	return os;
}
class signed_Bignumber
{
private:
	Unsigned_Bignumber absolute_value;
	bool sgn;

public:
	signed_Bignumber operator+(const signed_Bignumber &rhs) const; //加法重载
	signed_Bignumber operator-(const signed_Bignumber &rhs) const; //减法重载

	friend istream &operator>>(istream &is, signed_Bignumber &rhs);		  //输入重载
	friend ostream &operator<<(ostream &os, const signed_Bignumber &rhs); //输出重载
};
signed_Bignumber signed_Bignumber::operator+(const signed_Bignumber &rhs) const
{
	signed_Bignumber C;
	if (sgn && rhs.sgn) //(-a)+(-b)=-(a+b)
	{
		C.absolute_value = absolute_value + rhs.absolute_value;
		C.sgn = true;
	}
	else if (sgn && !rhs.sgn)																																													//(-a)+b=b-a
		if (absolute_value.number.length() > rhs.absolute_value.number.length() || (absolute_value.number.length() == rhs.absolute_value.number.length() && absolute_value.number > rhs.absolute_value.number)) //若a>b，b-a=-(a-b)
		{
			C.absolute_value = absolute_value - rhs.absolute_value;
			C.sgn = true;
		}
		else
		{
			C.absolute_value = rhs.absolute_value - absolute_value;
			C.sgn = false;
		}
	else if (!sgn && rhs.sgn)																																													//a+(-b)=a-b
		if (absolute_value.number.length() < rhs.absolute_value.number.length() || (absolute_value.number.length() == rhs.absolute_value.number.length() && absolute_value.number < rhs.absolute_value.number)) //若b>a,a-b=-(b-a)
		{
			C.absolute_value = rhs.absolute_value - absolute_value;
			C.sgn = true;
		}
		else
		{
			C.absolute_value = absolute_value - rhs.absolute_value;
			C.sgn = false;
		}
	else
	{
		C.absolute_value = absolute_value + rhs.absolute_value;
		C.sgn = false;
	}
	return C;
}
signed_Bignumber signed_Bignumber::operator-(const signed_Bignumber &rhs) const
{
	signed_Bignumber C;
	if (sgn && rhs.sgn)																																															//(-a)-(-b)=b-a
		if (absolute_value.number.length() > rhs.absolute_value.number.length() || (absolute_value.number.length() == rhs.absolute_value.number.length() && absolute_value.number > rhs.absolute_value.number)) //若a>b，b-a=-(a-b)
		{
			C.absolute_value = absolute_value - rhs.absolute_value;
			C.sgn = true;
		}
		else
		{
			C.absolute_value = rhs.absolute_value - absolute_value;
			C.sgn = false;
		}
	else if (sgn && !rhs.sgn) //(-a)-b=-(a+b)
	{
		C.absolute_value = absolute_value + rhs.absolute_value;
		C.sgn = true;
	}
	else if (!sgn && rhs.sgn) //a-(-b)=a+b
	{
		C.absolute_value = absolute_value + rhs.absolute_value;
		C.sgn = false;
	}
	else if (absolute_value.number.length() < rhs.absolute_value.number.length() || (absolute_value.number.length() == rhs.absolute_value.number.length() && absolute_value.number < rhs.absolute_value.number)) //若b>a,a-b=-(b-a)
	{
		C.absolute_value = rhs.absolute_value - absolute_value;
		C.sgn = true;
	}
	else
	{
		C.absolute_value = absolute_value - rhs.absolute_value;
		C.sgn = false;
	}
	return C;
}

istream &operator>>(istream &is, signed_Bignumber &rhs)
{
	is >> rhs.absolute_value.number;
	rhs.sgn = false;
	int i = 0;
	int l = rhs.absolute_value.number.length();
	for (i = 0; i < l; i++)
		if (rhs.absolute_value.number[i] > '0' && rhs.absolute_value.number[i] <= '9')
			break;
		else if (rhs.absolute_value.number[i] == '-')
			rhs.sgn = true;
	if (i == l)
		rhs.absolute_value.number = "0";
	else
	{
		rhs.absolute_value.number.erase(0, i);
		reverse(rhs.absolute_value.number.begin(), rhs.absolute_value.number.end());
	}
	return is;
}
ostream &operator<<(ostream &os, const signed_Bignumber &rhs)
{
	string str;
	str.assign(rhs.absolute_value.number.rbegin(), rhs.absolute_value.number.rend());
	if (rhs.sgn)
		os << '-';
	os << str;
	return os;
}
int main()
{
	signed_Bignumber A, B;
	cin >> A;
	cin >> B;
	cout << A + B << endl;
	cout << A - B << endl;

	//test
	// int a, b;
	// cin >> a >> b;
	// cout << a + b << endl;
	// cout << a - b << endl;
	return 0;
}
#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;
class Unsigned_Bignumber
{
private:
	string number;

public:
	Unsigned_Bignumber operator+(const Unsigned_Bignumber &rhs) const; //加法重载
	Unsigned_Bignumber operator-(const Unsigned_Bignumber &rhs) const; //减法重载

	friend istream &operator>>(istream &is, Unsigned_Bignumber &rhs);		//输入重载
	friend ostream &operator<<(ostream &os, const Unsigned_Bignumber &rhs); //输出重载
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
int main()
{
	Unsigned_Bignumber A, B;
	cin >> A;
	cin >> B;
	cout << A + B << endl;
	cout << A - B << endl;
	return 0;
}
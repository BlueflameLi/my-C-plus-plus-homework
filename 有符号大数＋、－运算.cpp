#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
class signed_Bignumber
{
private:
	string number;
	bool sgn;

public:
	signed_Bignumber operator+(const signed_Bignumber &rhs) const; //加法重载
	signed_Bignumber operator-(const signed_Bignumber &rhs) const; //减法重载

	friend istream &operator>>(istream &is, signed_Bignumber &rhs);		  //输入重载
	friend ostream &operator<<(ostream &os, const signed_Bignumber &rhs); //输出重载
};
string add(const string &s1, const string &s2) //无符号高精度加法
{
	int l1 = s1.length();
	int l2 = s2.length();
	string str;
	int t = 0; //进位
	for (int i = 0, j = 0; i < l1 || j < l2 || t; i++, j++)
	{
		if (i < l1)
			t += s1[i] - '0';
		if (j < l2)
			t += s2[i] - '0';
		str += t % 10 + '0';
		t /= 10;
	}
	return str;
}
string sub(const string &s1, const string &s2) //无符号高精度减法
{
	string str;
	if (s1 == s2)
		str = "0";
	else
	{
		int t = 0;
		int tmp = 0; //退位
		int l1 = s1.length();
		int l2 = s2.length();
		for (int i = 0; i < l2; i++)
		{
			t = (s1[i] - '0') - (s2[i] - '0') - tmp;
			if (t < 0)
			{
				tmp = 1;
				t += 10;
			}
			else
				tmp = 0;
			str += t + '0';
		}
		for (int i = l2; i < l1; i++)
		{
			t = s1[i] - '0' - tmp;
			if (t < 0)
			{
				tmp = 1;
				t += 10;
			}
			else
				tmp = 0;
			if (i < l1 - 1 || t)
				str += t + '0';
		}
	}
	return str;
}
signed_Bignumber signed_Bignumber::operator+(const signed_Bignumber &rhs) const
{
	signed_Bignumber C;
	if (sgn && rhs.sgn) //(-a)+(-b)=-(a+b)
	{
		C.number = add(number, rhs.number);
		C.sgn = true;
	}
	else if (sgn && !rhs.sgn)																						  //(-a)+b=b-a
		if (number.length() > rhs.number.length() || (number.length() == rhs.number.length() && number > rhs.number)) //若a>b，b-a=-(a-b)
		{
			C.number = sub(number, rhs.number);
			C.sgn = true;
		}
		else
		{
			C.number = sub(rhs.number, number);
			C.sgn = false;
		}
	else if (!sgn && rhs.sgn)																						  //a+(-b)=a-b
		if (number.length() < rhs.number.length() || (number.length() == rhs.number.length() && number < rhs.number)) //若b>a,a-b=-(b-a)
		{
			C.number = sub(rhs.number, number);
			C.sgn = true;
		}
		else
		{
			C.number = sub(number, rhs.number);
			C.sgn = false;
		}
	else
	{
		C.number = add(number, rhs.number);
		C.sgn = false;
	}
	return C;
}
signed_Bignumber signed_Bignumber::operator-(const signed_Bignumber &rhs) const
{
	signed_Bignumber C;
	if (sgn && rhs.sgn)																								  //(-a)-(-b)=b-a
		if (number.length() > rhs.number.length() || (number.length() == rhs.number.length() && number > rhs.number)) //若a>b，b-a=-(a-b)
		{
			C.number = sub(number, rhs.number);
			C.sgn = true;
		}
		else
		{
			C.number = sub(rhs.number, number);
			C.sgn = false;
		}
	else if (sgn && !rhs.sgn) //(-a)-b=-(a+b)
	{
		C.number = add(number, rhs.number);
		C.sgn = true;
	}
	else if (!sgn && rhs.sgn) //a-(-b)=a+b
	{
		C.number = add(number, rhs.number);
		C.sgn = false;
	}
	else if (number.length() < rhs.number.length() || (number.length() == rhs.number.length() && number < rhs.number)) //若b>a,a-b=-(b-a)
	{
		C.number = sub(rhs.number, number);
		C.sgn = true;
	}
	else
	{
		C.number = sub(number, rhs.number);
		C.sgn = false;
	}
	return C;
}

istream &operator>>(istream &is, signed_Bignumber &rhs)
{
	is >> rhs.number;
	rhs.sgn = false;
	int i = 0;
	int l = rhs.number.length();
	for (i = 0; i < l; i++)
		if (rhs.number[i] > '0' && rhs.number[i] <= '9')
			break;
		else if (rhs.number[i] == '-')
			rhs.sgn = true;
	if (i == l)
		rhs.number = "0";
	else
	{
		rhs.number.erase(0, i);
		reverse(rhs.number.begin(), rhs.number.end());
	}
	return is;
}
ostream &operator<<(ostream &os, const signed_Bignumber &rhs)
{
	string str;
	str.assign(rhs.number.rbegin(), rhs.number.rend());
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
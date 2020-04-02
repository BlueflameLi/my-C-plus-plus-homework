#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Set
{
private:
	vector<int> v;

public:
	Set();
	~Set();
	void print();
	void insert(int);
	vector<int>::iterator find(int x);
	vector<int>::iterator erase(vector<int>::iterator);
	Set operator*(Set &B);
	Set operator+(Set &B);
	Set operator-(Set &B);
};

Set::Set()
{
}

Set::~Set()
{
}
void Set::insert(int x)
{
	vector<int>::iterator itr;
	for (itr = v.begin(); itr != v.end(); itr++)
	{
		if (*itr == x)
			return;
		if (*itr > x)
			break;
	}
	v.insert(itr, x);
}
void Set::print()
{
	cout << '{';
	vector<int>::iterator itr;
	for (itr = v.begin(); itr != v.end(); itr++)
	{
		if (itr != v.end() - 1)
			cout << *itr << ',';
		else
			cout << *itr;
	}
	cout << '}' << endl;
}
vector<int>::iterator Set::erase(vector<int>::iterator itr)
{
	return v.erase(itr);
}
vector<int>::iterator Set::find(int x)
{
	return std::find(v.begin(), v.end(), x);
}
Set Set::operator*(Set &B)
{
	Set C;
	vector<int>::iterator itr;
	for (itr = v.begin(); itr != v.end(); itr++)
	{
		if (B.find(*itr) != B.v.end())
			C.insert(*itr);
	}
	return C;
}
Set Set::operator+(Set &B)
{
	Set C;
	vector<int>::iterator itr;
	for (itr = v.begin(); itr != v.end(); itr++)
		C.insert(*itr);
	for (itr = B.v.begin(); itr != B.v.end(); itr++)
		C.insert(*itr);
	return C;
}
Set Set::operator-(Set &B)
{
	Set C;
	vector<int>::iterator itr;
	for (itr = v.begin(); itr != v.end(); itr++)
	{
		if (B.find(*itr) == B.v.end())
			C.insert(*itr);
	}
	return C;
}
int main()
{
	Set A, B;
	int m, n;
	cin >> m >> n;
	for (int i = 0; i < m; i++)
	{
		int x;
		cin >> x;
		A.insert(x);
	}
	for (int i = 0; i < n; i++)
	{
		int x;
		cin >> x;
		B.insert(x);
	}
	A.print();
	B.print();
	Set C = A + B;
	C.print();
	C = A * B;
	C.print();
	C = A - B;
	C.print();
	return 0;
}
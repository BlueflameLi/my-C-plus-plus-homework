#include <iostream>
#include <vector>
using namespace std;
class Stack
{
private:
	vector<int> v;

public:
	Stack();
	~Stack();
	void push(int);
	int top();
	void pop();
	bool empty();
	int size();
};

Stack::Stack()
{
}

Stack::~Stack()
{
}
void Stack::push(int x)
{
	v.push_back(x);
}
int Stack::top()
{
	return v.back();
}
void Stack::pop()
{
	v.pop_back();
}
bool Stack::empty()
{
	return v.empty();
}
int Stack::size()
{
	return v.size();
}
int main()
{
	int v, x;
	Stack s1, s2;
	while (cin >> v >> x)
		if (v == 1)
			s1.push(x);
		else
			s2.push(x);
	while (!s1.empty())
	{
		cout << s1.top();
		s1.pop();
		if (s1.empty())
			cout << endl;
		else
			cout << ' ';
	}
	while (!s2.empty())
	{
		cout << s2.top();
		s2.pop();
		if (s2.empty())
			cout << endl;
		else
			cout << ' ';
	}
	return 0;
}

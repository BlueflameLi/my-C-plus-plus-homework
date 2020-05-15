#include <iostream>
#include <queue>
#include <string>
using namespace std;

template <class T>
class Cqueue
{
private:
	deque<T> q;

public:
	Cqueue() {}
	~Cqueue() {}
	Cqueue(const Cqueue &rhs) : q(rhs.q) {}

	inline void push(const T &x)
	{
		q.push_back(x);
	}
	inline void pop()
	{
		cout << q.front();
		q.pop_front();
	}
	inline void assign(const Cqueue &rhs)
	{
		q = rhs.q;
	}
	void Dump();
};

template <class T>
void Cqueue<T>::Dump()
{
	while (q.size() > 1)
	{
		pop();
		cout << ' ';
	}
	if (!q.empty())
	{
		pop();
		cout << endl;
	}
}
template <class T>
void Parse()
{
	int n;
	cin >> n;

	Cqueue<T> q1, q2, q3;

	cout << "Start:" << endl;
	string cmd;
	int id;
	for (int i = 0; i < n; i++)
	{
		cin >> cmd;
		cin >> id;
		if (cmd == "push")
		{
			T x;
			cin >> x;
			if (id == 1)
				q1.push(x);
			else if (id == 2)
				q2.push(x);
			else
				q3.push(x);
		}
		else if (cmd == "pop")
		{
			if (id == 1)
				q1.pop();
			else if (id == 2)
				q2.pop();
			else
				q3.pop();
			cout << ' ';
		}
		else
		{
			int j;
			cin >> j;
			if (id == 1)
			{
				if (j == 2)
					q2.assign(q1);
				else if (j == 3)
					q3.assign(q1);
			}
			else if (id == 2)
			{
				if (j == 1)
					q1.assign(q2);
				else if (j == 3)
					q3.assign(q2);
			}
			else
			{
				if (j == 1)
					q1.assign(q3);
				else if (j == 2)
					q2.assign(q3);
			}
		}
	}
	cout << endl;

	Cqueue<T> q4(q1);
	cout << "Final:" << endl;
	q1.Dump();
	q2.Dump();
	q3.Dump();
	q4.Dump();
}

int main()
{
	string type;
	cin >> type;
	if (type == "int")
		Parse<int>();
	else
		Parse<string>();
	return 0;
}
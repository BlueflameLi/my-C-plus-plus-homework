#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>

using namespace std;

class Set
{
private:
	struct node
	{
		int data;
		node *next;
		node()
		{
			data = 0;
			next = nullptr;
		}
	} * root; //头节点

public:
	//构造和析构
	Set();
	~Set();

	Set(const Set &copy);			 //拷贝构造
	Set &operator=(const Set &copy); //拷贝赋值

	Set(Set &&copy) noexcept;			 //移动构造
	Set &operator=(Set &&copy) noexcept; //移动赋值

	void clear();			//清空
	void insert(int x);		//插入
	void erase(int x);		//删除
	bool find(int x) const; //查找
	void show() const;		//显示

	Set operator+(const Set &B) const; //并
	Set operator*(const Set &B) const; //交
	Set operator-(const Set &B) const; //差
};

Set::Set()
{
	root = new node;
}

Set::~Set()
{
	clear();
	delete root;
}
Set::Set(const Set &copy)
{
	root = new node;
	node *p = copy.root->next;
	node *q = root;
	while (p)
	{
		q->next = new node;
		q->next->data = p->data;
		p = p->next;
		q = q->next;
	}
}
Set &Set::operator=(const Set &copy)
{
	if (this != &copy)
	{
		clear();
		node *p = copy.root->next;
		node *q = root;
		while (p)
		{
			q->next = new node;
			q->next->data = p->data;
			p = p->next;
			q = q->next;
		}
	}
	return *this;
}
Set::Set(Set &&copy) noexcept
{
	root = copy.root;
	copy.root = nullptr;
}
Set &Set::operator=(Set &&copy) noexcept
{
	node *tmp = copy.root;
	copy.root = root;
	root = tmp;
	return *this;
}
void Set::clear()
{
	node *p = root->next;
	while (p)
	{
		node *q = p->next;
		delete p;
		p = q;
	}
	root->next = nullptr;
}
void Set::insert(int x)
{
	node *p = root;
	while (p->next && p->next->data < x)
		p = p->next;
	if (!p->next)
	{
		p->next = new node;
		p->next->data = x;
		return;
	}
	if (p->next->data == x)
		return;
	node *q = new node;
	q->data = x;
	q->next = p->next;
	p->next = q;
	return;
}
void Set::erase(int x)
{
	node *p = root;
	while (p->next && p->next->data < x)
		p = p->next;
	if (!p->next || p->next->data > x)
		return;
	node *q = p->next;
	p->next = q->next;
	delete q;
}
bool Set::find(int x) const
{
	node *p = root->next;
	while (p)
	{
		if (p->data == x)
			return true;
		p = p->next;
	}
	return false;
}

void Set::show() const
{
	cout << '{';
	node *p = root->next;
	while (p)
	{
		if (!p->next)
			cout << p->data;
		else
			cout << p->data << ',';
		p = p->next;
	}
	cout << '}' << endl;
}
Set Set::operator*(const Set &B) const
{
	Set C;
	node *p = root->next;
	node *q = B.root->next;
	node *ans = C.root;
	while (p && q)
	{
		if (p->data > q->data)
			q = q->next;
		else if (p->data < q->data)
			p = p->next;
		else
		{
			ans->next = new node;
			ans->next->data = p->data;
			ans = ans->next;
			p = p->next;
			q = q->next;
		}
	}
	return C;
}

Set Set::operator+(const Set &B) const
{
	Set C;
	node *p = root->next;
	node *q = B.root->next;
	node *ans = C.root;
	while (p || q)
	{
		if (!p)
		{
			while (q)
			{
				ans->next = new node;
				ans->next->data = q->data;
				ans = ans->next;
				q = q->next;
			}
			break;
		}
		if (!q)
		{
			while (p)
			{
				ans->next = new node;
				ans->next->data = p->data;
				ans = ans->next;
				p = p->next;
			}
			break;
		}
		if (p->data > q->data)
		{
			ans->next = new node;
			ans->next->data = q->data;
			ans = ans->next;
			q = q->next;
		}
		else if (p->data < q->data)
		{
			ans->next = new node;
			ans->next->data = p->data;
			ans = ans->next;
			p = p->next;
		}
		else
		{
			ans->next = new node;
			ans->next->data = p->data;
			ans = ans->next;
			p = p->next;
			q = q->next;
		}
	}
	return C;
}
Set Set::operator-(const Set &B) const
{
	Set C;
	node *p = root->next;
	node *q = B.root->next;
	node *ans = C.root;
	while (p)
	{
		if (!q)
		{
			while (p)
			{
				ans->next = new node;
				ans->next->data = p->data;
				ans = ans->next;
				p = p->next;
			}
			break;
		}
		if (p->data > q->data)
			q = q->next;
		else if (p->data < q->data)
		{
			ans->next = new node;
			ans->next->data = p->data;
			ans = ans->next;
			p = p->next;
		}
		else
		{
			p = p->next;
			q = q->next;
		}
	}
	return C;
}
int main()
{
	int n, m;
	Set A, B;
	cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		int x;
		cin >> x;
		A.insert(x);
	}
	for (int i = 0; i < m; i++)
	{
		int x;
		cin >> x;
		B.insert(x);
	}
	A.show();
	B.show();
	Set C = A + B;
	C.show();
	C = A * B;
	C.show();
	C = A - B;
	C.show();
	return 0;
}
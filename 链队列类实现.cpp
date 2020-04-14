#include <iostream>
#include <string>
using namespace std;
class CQueue
{
	struct Node
	{
		int data;
		Node *next;
	}; //链表结点结构
private:
	Node *m_pFront, *m_pRear; //链表首结点和尾结点指针
public:
	CQueue();				   //队列构造
	CQueue(const CQueue &rhs); //队列拷贝构造
	~CQueue();				   //队列析构，
	bool push(int x);		   //X入队列
	void pop();				   //出队列
	int front();			   //取队首元素
	bool empty() const;		   //判队空
	int GetLength() const;	   //取队列长度
};

CQueue::CQueue()
{
	this->m_pFront = this->m_pRear = new Node; //链表加头结点简化出队列、入队列操作
	this->m_pFront->next = this->m_pRear->next = NULL;
}
CQueue::CQueue(const CQueue &rhs) //复制队列
{
	this->m_pFront = this->m_pRear = new Node;
	this->m_pFront->next = NULL;
	Node *p = rhs.m_pFront->next;
	while (p)
	{ //将原队列元素依次入队列
		this->push(p->data);
		p = p->next;
	}
}

CQueue::~CQueue()
{
	while (m_pFront != NULL)
	{ //释放链表中所有结点
		m_pRear = m_pFront;
		m_pFront = m_pFront->next;
		delete m_pRear;
	}
}

bool CQueue::push(int x) //X入队列
{
	Node *p = new Node; //申请结点

	p->data = x;
	p->next = NULL;
	//挂在队尾
	this->m_pRear->next = p;
	this->m_pRear = p;
	return true;
}

//队列非空
void CQueue::pop() //出队列
{
	Node *p = m_pFront;
	this->m_pFront = this->m_pFront->next; //后一结点变为头结点
	delete p;
}

//队列非空
int CQueue::front()
{
	return this->m_pFront->next->data; //队首元素存放在头结点的下一结点
}
bool CQueue::empty() const
{
	return (this->m_pFront == this->m_pRear); //是否只有头结点
}

int CQueue::GetLength() const
{
	int count = 0;
	Node *p = this->m_pFront->next; //头结点不算
	while (p != NULL)
	{
		count++;
		p = p->next;
	}
	return count;
}

int main()
{
	CQueue Queue[2];

	int x;

	cin >> x;
	while (x != 0)
	{
		if (x > 0)
			Queue[0].push(x); //入队列
		else
			Queue[1].push(x);
		cin >> x;
	}

	while (!Queue[0].empty())
	{						  //所有元素出队列
		x = Queue[0].front(); //出队列
		Queue[0].pop();
		cout << x << ' ';
	}
	cout << endl;

	while (!Queue[1].empty())
	{						  //所有元素出队列
		x = Queue[1].front(); //出队列
		Queue[1].pop();
		cout << x << ' ';
	}
	cout << endl;

	return 0;
}

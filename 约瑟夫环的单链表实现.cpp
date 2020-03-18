#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <iomanip>

using namespace std;

struct node
{
    int v;
    node *next;
    node(int a)
    {
        v = a;
        next = NULL;
    }
} * head;
int n, m;
void create(node *p)
{
    for (int i = 2; i <= n; i++)
    {
        node *q = new node(i);
        q->next = p->next;
        p->next = q;
        p = q;
    }
}

int main()
{
    head = new node(1);
    head->next = head;
    cin >> n >> m;
    create(head);
    int cnt = 0;
    node *pre = NULL;
    bool flag = 0;
    while (head->next != head)
    {
        cnt++;
        if (cnt == m)
        {
            if (!flag)
            {
                cout << head->v;
                flag = 1;
            }
            else
                cout << setw(4) << head->v;
            node *p = head;
            pre->next = head->next;
            head = head->next;
            delete p;
            cnt = 0;
        }
        else
        {
            pre = head;
            head = head->next;
        }
    }
    cout << setw(4) << head->v << endl;
    delete head;
    return 0;
}


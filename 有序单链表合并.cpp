#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

struct node
{
    int v;
    node *next;
    node()
    {
        v = 0;
        next = NULL;
    }
};
void insert(node *p, int x)
{
    while (p->next && p->next->v < x)
        p = p->next;
    node *q = new node;
    q->v = x;
    q->next = p->next;
    p->next = q;
}
void print(node *head)
{
    head = head->next;
    if (head)
    {
        cout << head->v;
        head = head->next;
    }
    while (head)
    {
        cout << "->" << head->v;
        head = head->next;
    }
    cout << endl;
}
void merge(node *head1, node *head2)
{
    head2 = head2->next;
    while (head2)
    {
        insert(head1, head2->v);
        head2 = head2->next;
    }
}
void del(node *head)
{
    if (head)
    {
        del(head->next);
        delete head;
    }
}
int main()
{
    node *head1 = new node;
    node *head2 = new node;
    int x;
    while (cin >> x && x)
    {
        if (x % 2)
            insert(head1, x);
        else
            insert(head2, x);
    }
    print(head1);
    print(head2);
    merge(head1, head2);
    print(head1);
    del(head1);
    del(head2);
    return 0;
}


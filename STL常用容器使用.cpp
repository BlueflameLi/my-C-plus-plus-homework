#include <iostream>
#include <cstring>
#include <iomanip>
#include <stack>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

vector<int> v;
queue<int> q;
stack<int> s1, s2;

bool is_prime(int n)
{
    if (n < 2)
        return false;
    for (int i = 2; i <= sqrt(n); i++)
        if (n % i == 0)
            return false;
    return true;
}
int main()
{
    int n;
    while (cin >> n && n)
    {
        if (n < 0)
            v.push_back(n);
        else
        {
            if (is_prime(n))
                q.push(n);
            if (n & 1)
                s2.push(n);
            else
                s1.push(n);
        }
    }
    vector<int>::iterator itr;
    for (itr = v.begin(); itr != v.end(); itr++)
        cout << *itr << '\t';
    cout << endl;
    while (!q.empty())
    {
        cout << q.front() << '\t';
        q.pop();
    }
    cout << endl;
    while (!s1.empty())
    {
        cout << s1.top() << '\t';
        s1.pop();
    }
    cout << endl;
    while (!s2.empty())
    {
        if (s2.size() == 1)
            cout << s2.top() << endl;
        else
            cout << s2.top() << '\t';
        s2.pop();
    }
    return 0;
}


#include <iostream>
#include <vector>
#include <string>
using namespace std;

template <class T>
class queue
{
private:
      vector<T> v;

public:
      queue() {}
      ~queue() {}
      queue(const queue &rhs) : v(rhs.v) {}

      inline void push(const T &x)
      {
            v.push_back(x);
      }
      inline void pop()
      {
            cout << v.front();
            v.erase(v.begin());
      }
      inline void assign(const queue &q)
      {
            v = q.v;
      }
      void Dump();
};

template <class T>
void queue<T>::Dump()
{
      while (v.size() > 1)
      {
            pop();
            cout << ' ';
      }
      if (!v.empty())
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

      queue<T> q1, q2, q3;

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

      queue<T> q4(q1);
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
#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int n;
int r, c; //r表示行，c表示列
int tr, tc;
int main()
{
    cin >> n;
    vector<int> v(n * n, 0);
    c = n >> 1;
    for (int i = 1; i <= n * n; i++)
    {
        // cout << r << ' ' << c << ' ' << i << endl;
        v[r * n + c] = i;
        tr = r - 1;
        tc = c + 1;
        if (tr < 0)
            tr = n - 1;
        if (tc >= n)
            tc = 0;
        if (v[tr * n + tc])
        {
            tr = r + 1;
            tc = c;
            if (tr >= n)
                tr = 0;
        }
        r = tr;
        c = tc;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout.width(5);
            cout << v[i * n + j];
        }
        cout << endl;
    }
    return 0;
}


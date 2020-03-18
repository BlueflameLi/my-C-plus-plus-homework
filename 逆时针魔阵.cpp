#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int n;
int r, c; //r表示行，c表示列
int d;    //d表示方向,0向下，1向右，2向上，3向左
int main()
{
    cin >> n;
    vector<int> v(n * n, 0);
    for (int i = 1; i <= n * n; i++)
    {
        // cout << r << ' ' << c << ' ' << i << endl;
        v[r * n + c] = i;
        switch (d)
        {
        case 0:
            if (r < n - 1 && !v[(r + 1) * n + c])
                r++;
            else
            {
                d = 1;
                c++;
            }
            break;
        case 1:
            if (c < n - 1 && !v[r * n + c + 1])
                c++;
            else
            {
                d = 2;
                r--;
            }
            break;
        case 2:
            if (r > 0 && !v[(r - 1) * n + c])
                r--;
            else
            {
                d = 3;
                c--;
            }
            break;
        default:
            if (c > 0 && !v[r * n + c - 1])
                c--;
            else
            {
                d = 0;
                r++;
            }
            break;
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout.width(4);
            cout << v[i * n + j];
        }
        cout << endl;
    }
    return 0;
}


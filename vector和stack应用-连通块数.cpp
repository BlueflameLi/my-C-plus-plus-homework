#include <iostream>
#include <vector>
#include <stack>
#include <iterator>
#include <algorithm>
using namespace std;

int n, m;
int dx[4] = {0, 1, -1, 0};
int dy[4] = {1, 0, 0, -1};
vector<vector<int>> v;
stack<pair<int, int>> s;
inline bool check(int x, int y)
{
    if (x >= 0 && y >= 0 && x < n && y < m)
        return true;
    return false;
}
void dfs(int x, int y)
{
    int k = v[x][y];
    s.push(make_pair(x, y));
    while (!s.empty())
    {
        int px = s.top().first;
        int py = s.top().second;
        bool flag = 1;
        for (int i = 0; i < 4; i++)
        {
            int nx = px + dx[i];
            int ny = py + dy[i];
            if (check(nx, ny) && v[nx][ny] == k)
            {
                v[nx][ny] = -1;
                s.push(make_pair(nx, ny));
                flag = 0;
                break;
            }
        }
        if (flag)
            s.pop();
    }
}
int main()
{
    cin >> n >> m;
    v.resize(n, vector<int>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> v[i][j];

    int cnt = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (~v[i][j])
            {
                cnt++;
                dfs(i, j);
            }
    cout << cnt << endl;
    return 0;
}

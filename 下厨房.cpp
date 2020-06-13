#include <iostream>
#include <map>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
    map<string, int> mp;
    string str;
    while (cin >> str)
        mp[str]++;
    cout << mp.size() << endl;
    return 0;
}

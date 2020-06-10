#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;
class Check
{
public:
    bool operator()(int x) const
    {
        int sum = 0;
        for (int i = 1; i < x; i++)
            if (x % i == 0)
                sum += i;
        if (sum == x)
            return true;
        return false;
    }
};

int main()
{
    vector<int> v;

    copy(istream_iterator<int>(cin), istream_iterator<int>(), back_inserter(v));

    auto cnt = count_if(v.begin(), v.end(), Check());
    cout << cnt << endl;
    if (cnt)
    {
        auto ans = find_if(v.begin(), v.end(), Check());
        cout << (ans - v.begin()) + 1 << '\t' << *ans << endl;
    }
    else
        cout << "none" << endl;

    return 0;
}

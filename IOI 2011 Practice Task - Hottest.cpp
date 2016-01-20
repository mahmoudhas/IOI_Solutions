#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
    int n, k;
    ll sum = 0, mx = 0;
    deque<int> cur;
    cin >> n >> k;
    while (n--)
    {
        int x;
        cin >> x;
        sum += x;
        cur.push_back(x);
        while (cur.size() > k)
        {
            sum -= cur.front();
            cur.pop_front();
        }
        mx = max(mx, sum);
    }
    cout << mx << endl;
}

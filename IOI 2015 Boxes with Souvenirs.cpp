#include <bits/stdc++.h>

using namespace std;

int n, l, k;
vector<int> cw, ccw;
long long memo1[10000010];
long long doCW(int i)
{
    if (i < 0 || cw.size() == 0)
        return 0;
    if (i >= cw.size())
        return doCW(cw.size() - 1);
    if (memo1[i] != -1)
        return memo1[i];
    return memo1[i] = 1LL * cw[i] * 2 + doCW(i - k);
}
long long memo2[10000010];
long long doCCW(int i)
{
    if (i < 0 || ccw.size() == 0)
        return 0;
    if (i >= ccw.size())
        return doCCW(ccw.size() - 1);
    if (memo2[i] != -1)
        return memo2[i];
    return memo2[i] = 1LL * ccw[i] * 2 + doCCW(i - k);
}

int main()
{
    memset(memo1, -1, sizeof memo1);
    memset(memo2, -1, sizeof memo2);

    scanf("%d%d%d", &n, &k, &l);
    for (int i = 0; i < n; i++)
    {
        int x;
        scanf("%d", &x);
        if (x == 0 || x == l)
            continue;
        if (x >= l / 2 + (l % 2))
            ccw.push_back(l - x);
        else cw.push_back(x);
    }
    cerr << cw.size() << " " << ccw.size() << endl;
    sort(cw.begin(), cw.end());
    sort(ccw.begin(), ccw.end());

    long long ans = doCW((int)cw.size() - 1) + doCCW((int)ccw.size() - 1);
    for (int j = 0; j <= k; j++)
    {
        int d = k - j;
        int a = (int)cw.size() - 1 - j;
        int b = (int)ccw.size() - 1 - d;
        ans = min(ans, doCW(a) + doCCW(b) + l);
    }
    printf("%lld\n", ans);
}

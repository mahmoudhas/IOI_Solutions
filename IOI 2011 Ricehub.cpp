#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 200010;

int n;
vector<ll> ar;

ll ft[MAXN + 1];
ll rsq(int i)
{
    i++;
    ll ret = 0;
    for (; i; i -= i & -i)
        ret += ft[i];
    return ret;
}
ll rsq(int i, int j)
{
    return rsq(j) - rsq(i - 1);
}
void add(int i, ll x)
{
    i++;
    for (; i < MAXN + 1; i += i & -i)
        ft[i] += x;
}
ll comp(int l, int r, int x)
{
    ll a = 0, b = 0;

    if (r != x)
    {
        a += rsq(x + 1, r);
        a -= 1LL * ar[x] * (r - x);
    }

    if (l != x)
    {
        b += rsq(l, x - 1);
        b = 1LL * ar[x] * (x - l) - b;
    }
    return a + b;
}

int besthub(int R, int L, int X[], long long B)
{
    n = R;
    ar = vector<ll>(R);
    for (int i = 0; i < R; i++)
        ar[i] = X[i], add(i, ar[i]);
    int ans = 0;
    int l = 0;
    int cnt = 0;
    ll sum = 0;
    for (int i = 0; i < n; i++)
    {
        cnt++;
        sum += ar[i];

        while (l <= i)
        {
            ll b6e5 = sum / (cnt);
            int lo = l; int hi = i;
            while (lo < hi)
            {
                int mid = (lo + hi) / 2;
                if (ar[mid] >= b6e5)
                    hi = mid;
                else lo = mid + 1;
            }
            lo = (l + i) / 2;
            int a = lo; int b = lo + 1; int c = a - 1;
            ll cur = LLONG_MAX;
            if (a >= 0 && a < n)
                cur = min(cur, comp(l, i, a));
            if (b >= 0 && b < n)
                cur = min(cur, comp(l, i, b));
            ll prevv = cur;
            for (c = max(l, lo - 59); c <= min(i, lo + 59); c++)
            {
                cur = min(cur, comp(l, i, c));
                if (prevv != cur)
                {
                    prevv = cur;
                }
            }
            if (cur <= B)
            {
                break;
            }
            else
            {
                cnt--;
                sum -= ar[l];
                l++;
            }
        }
        ans = max(ans, cnt);
    }
    return ans;
}

int main()
{
    int r, l;
    ll b;
    cin >> r >> l >> b;
    int *ar = new int[r];
    for (int i = 0; i < r; i++)
        cin >> ar[i];
    cout << besthub(r, l, ar, b) << endl;
}

#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

#define left (index << 1)
#define right ((index << 1) + 1)
#define mid ((l + r) / 2)

const int MAXA = (int)1e9 + 1;
const int mod = (int)1e9 + 7;

int n;
vector<int> x, y;
vector<int> p, p2;
void buildP(int index, int l, int r)
{
    if (l == r)
    {
        p[index] = p2[index] = x[l];
        return;
    }
    buildP(left, l, mid);
    buildP(right, mid + 1, r);
    p[index] = (1LL * p[left] * p[right]) % mod;
    p2[index] = min((ll)MAXA, 1LL * p2[left] * p2[right]);
}
void updateP(int index, int l, int r, int ind)
{
    if (!(ind >= l && ind <= r))
        return;
    if (l == r)
    {
        p[index] = p2[index] = x[ind];
        return;
    }
    updateP(left, l, mid, ind);
    updateP(right, mid + 1, r, ind);
    p[index] = (1LL * p[left] * p[right]) % mod;
    p2[index] = min((ll)MAXA, 1LL * p2[left] * p2[right]);
}
int queryP(int index, int l, int r, int ql, int qr, bool foo)
{
    if (l > qr || r < ql)
        return 1;
    if (l >= ql && r <= qr)
        return foo ? p2[index] : p[index];
    if (foo)
        return min((ll)MAXA, (1LL * queryP(left, l, mid, ql, qr, true) * queryP(right, mid + 1, r, ql, qr, true)));
    return (1LL * queryP(left, l, mid, ql, qr, false) * queryP(right, mid + 1, r, ql, qr, false)) % mod;
}

vector<int> st;
void build(int index, int l, int r)
{
    if (l == r)
    {
        st[index] = l;
        return;
    }
    build(left, l, mid);
    build(right, mid + 1, r);
    int lll = st[left],
        rrr = st[right];
    if (queryP(1, 0, n - 1, lll + 1, rrr, true) >= ceil(y[lll] / (double)y[rrr]))
        st[index] = rrr;
    else st[index] = lll;
}
void update(int index, int l, int r, int ind)
{
    if (!(ind >= l && ind <= r))
        return;
    if (l == r)
        return;
    update(left, l, mid, ind);
    update(right, mid + 1, r, ind);
    int lll = st[left],
        rrr = st[right];
    if (queryP(1, 0, n - 1, lll + 1, rrr, true) >= (int)ceil(y[lll] / (double)y[rrr]))
        st[index] = rrr;
    else st[index] = lll;
}

int solve()
{
    int ind = st[1];
    //cout << ind << endl;
    return (1LL * queryP(1, 0, n - 1, 0, ind, false) * y[ind]) % mod;
}

int init(int N, int X[], int Y[])
{
    x = y = vector<int>(N);
    for (int i = 0; i < N; i++)
        x[i] = X[i], y[i] = Y[i];
    p = p2 = st = vector<int>(N * 4);
    n = N;
    buildP(1, 0, n - 1);
    build(1, 0, n - 1);
    return solve();
}

int updateX(int pos, int val)
{
    x[pos] = val;
    updateP(1, 0, n - 1, pos);
    update(1, 0, n - 1, pos);
    //buildP(1, 0, n - 1);
    //build(1, 0, n - 1);
    return solve();
}

int updateY(int pos, int val)
{
    y[pos] = val;
    update(1, 0, n - 1, pos);
    //buildP(1, 0, n - 1);
    //build(1, 0, n - 1);
    return solve();
}

#ifdef ONLINE_JUDGE
int *arrA, *arrB;
int main()
{
    int n;
    scanf("%d", &n);
    arrA = new int[n];
    arrB = new int[n];
    for (int i = 0; i < n; i++)
        scanf("%d", &arrA[i]);
    for (int i = 0; i < n; i++)
        scanf("%d", &arrB[i]);
    printf("%d\n", init(n, arrA, arrB));
    int q;
    scanf("%d", &q);
    while (q--)
    {
        int t, pos, val;
        scanf("%d%d%d", &t, &pos, &val);
        int ans;
        if (t == 1)
            ans = updateX(pos, val);
        else
            ans = updateY(pos, val);
        printf("%d\n", ans);
    }
}
#endif

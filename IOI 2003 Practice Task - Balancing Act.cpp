#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200010;

typedef pair<int, int> ii;
#define fr first
#define sc second
#define mp make_pair

int n;
vector<int> tree[MAXN];
int sons[MAXN];
vector<int> sub[MAXN];

int dfs(int pos, int par)
{
    if (sons[pos] != -1)
        return sons[pos];
    sons[pos] = 0;
    for (int i = 0; i < tree[pos].size(); i++) if (tree[pos][i] != par)
    {
        int x = dfs(tree[pos][i], pos);
        sons[pos] += x;
        sub[pos].push_back(x);
    }
    sub[pos].push_back(n - sons[pos] - 1);
    sort(sub[pos].begin(), sub[pos].end());
    return sons[pos] + 1;
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        u--, v--;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    memset(sons, -1, sizeof sons);
    dfs(0, -1);
    int ans1, ans2 = INT_MAX;
    for (int i = 0; i < n; i++)
    {
        if (sub[i].back() < ans2)
        {
            ans1 = i;
            ans2 = sub[i].back();
        }
    }
    printf("%d %d\n", ans1 + 1, ans2);
}

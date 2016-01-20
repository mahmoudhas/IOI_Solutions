#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2000010;
const int MAXK = 2000010;
const int inf = (1 << 29);

int n, k;
vector<int> adj[MAXN];
vector<int> len[MAXN];

int subtree_size[MAXN];
bool deleted[MAXN];

int id = 0, id_a[MAXN];
int idh = 0, id_ah[MAXN];
int a[MAXN], helper_a[MAXN];

int root;
int best, bestmax;

int ans;

void compute_size(int u, int par)
{
    subtree_size[u] = 1;
    for (int i = 0; i < adj[u].size(); i++) if (adj[u][i] != par && !deleted[adj[u][i]])
    {
        compute_size(adj[u][i], u);
        subtree_size[u] += subtree_size[adj[u][i]];
    }
}

void best_node(int u, int par)
{
    int mx = subtree_size[root] - subtree_size[u];
    for (int i = 0; i < adj[u].size(); i++) if (adj[u][i] != par && !deleted[adj[u][i]])
    {
        mx = max(mx, subtree_size[adj[u][i]]);
        best_node(adj[u][i], u);
    }
    if (mx < bestmax)
    {
        bestmax = mx;
        best = u;
    }
}

void dfs(int u, int par, int curlen, int curn, bool helper)
{
    if (curlen > k) return;
    if (id_ah[curlen] != idh)
    {
        id_ah[curlen] = idh;
        helper_a[curlen] = inf;
    }
    if (id_a[curlen] != id)
    {
        id_a[curlen] = id;
        a[curlen] = inf;
    }
    if (helper)
    {
        helper_a[curlen] = min(helper_a[curlen], curn);
        if (id_a[k - curlen] == id)
            a[k] = min(a[k], helper_a[curlen] + a[k - curlen]);
    }
    else
    {
        a[curlen] = min(a[curlen], helper_a[curlen]);
    }
    for (int i = 0; i < adj[u].size(); i++) if (adj[u][i] != par && !deleted[adj[u][i]])
    {
        dfs(adj[u][i], u, curlen + len[u][i], curn + 1, helper);
    }
}

void process(int u)
{
    root = u;
    compute_size(u, -1);
    if (subtree_size[u] == 1)
        return;
    best = -1;
    bestmax = inf;
    best_node(u, -1);

    a[0] = 0;
    a[k] = inf;
    id_a[0] = id;
    id_a[k] = inf;

    for (int i = 0; i < adj[best].size(); i++) if (!deleted[adj[best][i]])
    {
        helper_a[0] = 0;
        id_ah[0] = idh;

        dfs(adj[best][i], best, len[best][i], 1, true);
        dfs(adj[best][i], best, len[best][i], 1, false);
        idh++;
    }
    id++;
    ans = min(ans, a[k]);
    deleted[best] = true;
    u = best;
    for (int i = 0; i < adj[u].size(); i++) if (!deleted[adj[u][i]])
    {
        process(adj[u][i]);
    }
}

inline void add(int u, int v, int l);

int main()
{
    ans = inf;
    memset(id_a, -1, sizeof id_a);
    memset(id_ah, -1, sizeof id_ah);
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n - 1; i++)
    {
        int u, v, l;
        scanf("%d%d%d", &u, &v, &l);
        add(u, v, l);
    }
    process(0);
    printf("%d\n", ans >= inf ? -1 : ans);
}

inline void add(int u, int v, int l)
{
    adj[u].push_back(v);
    len[u].push_back(l);
    adj[v].push_back(u);
    len[v].push_back(l);
}

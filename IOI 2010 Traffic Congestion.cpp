#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000010;

int n;
int val[MAXN];
vector<int> adj[MAXN];

int vv = INT_MAX, ans;

int sz[MAXN];
void comp(int u, int par = -1) {
    sz[u] = val[u];
    for (auto &v : adj[u]) if (v != par) {
        comp(v, u);
        sz[u] += sz[v];
    }
}
void dfs(int u, int x = 0, int par = -1) {
    int mx = x;
    for (auto &v : adj[u]) if (v != par) {
        dfs(v, x + sz[u] - sz[v], u);
        mx = max(mx, sz[v]);
    }
    if (mx < vv) {
        vv = mx;
        ans = u;
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", val + i);
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    comp(0);
    dfs(0);
    printf("%d\n", ans);
}

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 150010;
const int MXLOG = 30;

int n, m, s;
vector<int> adj[2 * MAXN];
int to[2 * MAXN];
bool vis[2 * MAXN];
vector<int> adj2[2 * MAXN];
int dist[2 * MAXN][2];

int w[2][2], wh[2];
bool check(int t, int d) {
    if (d < 0) return false;
    if (d == 0) return true;
    if (wh[t] == -1) return false;
    if (wh[t] == t) {
        return d % w[t][t] == 0;
    }
    if (wh[!t] == t) {
        d %= w[t][!t] + w[!t][t];
        return check(!t, d - w[t][!t]);
    }
    return check(!t, d - w[t][!t]);
}

void dfs(int u, int t, int d = 0) {
    memset(vis, 0, sizeof vis);
    queue<int> q;
    dist[u][t] = 0;
    q.push(u);
    while (!q.empty()) {
        u = q.front();
        q.pop();
        if (vis[u]) continue;
        vis[u] = true;
        for (auto &v : adj2[u]) {
            if (dist[v][t] == -1) {
                dist[v][t] = dist[u][t] + 1;
                q.push(v);
            }
        }
    }
}

void comp(int t) {
    memset(vis, 0, sizeof vis);
    int st = (t == 0 ? s : s + n);
    int u = to[st];
    int d = 1;
    while (!vis[u]) {
        vis[u] = true;
        if (u == s) {
            wh[t] = 0;
            w[t][0] = d;
            break;
        }
        if (u == s + n) {
            wh[t] = 1;
            w[t][1] = d;
            break;
        }
        d++;
        u = to[u];
    }
}


int main() {
    scanf("%d%d%d", &n, &m, &s);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        if (adj[u].size() < 2) {
            adj[u].push_back(v);
        }
        if (adj[v].size() < 2) {
            adj[v].push_back(u);
        }
    }
    for (int i = n; i < 2*n; i++) {
        adj[i] = adj[i - n];
        if (adj[i].size() == 2) {
            swap(adj[i][0], adj[i][1]);
        }
    }
    for (int u = 0; u < 2 * n; u++) {
        int v = adj[u][0];
        if (adj[v][0] == u % n) {
            v += n;
        }
        to[u] = v;
        adj2[v].push_back(u);
    }
    memset(w, -1, sizeof w);
    memset(dist, -1, sizeof dist);
    wh[0] = wh[1] = -1;
    dfs(s, 0);
    dfs(s + n, 1);
    comp(0);
    comp(1);
    int q;
    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        int g;
        scanf("%d", &g);
        int ans = 0;
        for (int z = 0; z < n; z++) {
            int cur = 0;
            if (dist[z][0] != -1) {
                int rem = g - dist[z][0];
                cur |= check(0, rem);
            }
            if (dist[z][1] != -1) {
                int rem = g - dist[z][1];
                cur |= check(1, rem);
            }
            ans += cur;
        }
        if (i) printf(" ");
        printf("%d", ans);
    }
    printf("\n");
}

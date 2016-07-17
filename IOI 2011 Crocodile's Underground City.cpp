#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef pair<ll, int> lli;
typedef priority_queue< lli, vector<lli>, greater<lli> > PQ;

const int MAXN = 100010;

int n, m, k;
vector<int> adj[MAXN];
vector<int> len[MAXN];
int vis[MAXN];
ll ans;

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0; i < m; i++) {
        int u, v, l;
        scanf("%d%d%d", &u, &v, &l);
        adj[u].push_back(v);
        adj[v].push_back(u);
        len[u].push_back(l);
        len[v].push_back(l);
    }
    PQ pq;
    for (int i = 0; i < k; i++) {
        int x;
        scanf("%d", &x);
        pq.push({ 0, x });
        vis[x] = 1;
    }
    while (!pq.empty()) {
        int u = pq.top().second;
        ll l = pq.top().first;
        pq.pop();
        if (!vis[u]) {
            vis[u] = 1;
            continue;
        }
        if (vis[u] == 2) {
            continue;
        }
        if (u == 0) {
            ans = l;
            break;
        }
        vis[u] = 2;
        for (int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i];
            ll nl = l + len[u][i];
            if (vis[v] == 2) continue;
            pq.push({ nl, v });
        }
     }
     printf("%lld\n", ans);
}

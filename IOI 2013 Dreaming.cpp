#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100010;

typedef long long ll;
const ll infll = 1LL << 62;

int n, m, L;
vector<int> adj[MAXN], len[MAXN];
vector<int> component;
bitset<MAXN> vis;

ll dp[MAXN];
void dfs1(int u, int par = -1) {
	vis[u] = true;
	dp[u] = 0;
	for (int i = 0; i < adj[u].size(); i++) if (adj[u][i] != par) {
		int v = adj[u][i];
		dfs1(v, u);
		dp[u] = max(dp[u], len[u][i] + dp[v]);
	}
}

int center;
ll dist;
void dfs2(int u, ll mx = 0, int par = -1) {
	ll mx1 = 0, mx2 = 0;
	int ind = 0;
	for (int i = 0; i < adj[u].size(); i++) if (adj[u][i] != par) {
		int v = adj[u][i];
		ll x = dp[v] + len[u][i];
		if (x > mx1) {
			mx2 = mx1;
			mx1 = x;
			ind = i;
		}
		else if (x > mx2) {
			mx2 = x;
		}
	}
	ll mxx = max(mx1, mx);
	if (mxx < dist) {
		dist = mxx;
		center = u;
	}
	for (int i = 0; i < adj[u].size(); i++) if (adj[u][i] != par) {
		int v = adj[u][i];
		if (i == ind) swap(mx1, mx2);
		dfs2(v, max(mx1, mx) + len[u][i], u);
		if (i == ind) swap(mx1, mx2);
	}
}

ll diam;
int diamv;
void dfs3(int u, ll l = 0, int par = -1) {
	if (l > diam) {
		diam = l;
		diamv = u;
	}
	for (int i = 0; i < adj[u].size(); i++) if (adj[u][i] != par) {
		dfs3(adj[u][i], l + len[u][i], u);
	}
}

int main() {
	cin >> n >> m >> L;
	for (int i = 0; i < m; i++) {
		int u, v, l;
		cin >> u >> v >> l;
		adj[u].push_back(v);
		adj[v].push_back(u);
		len[u].push_back(l);
		len[v].push_back(l);
	}
	ll mx = 0;
	int vert = 0;
	for (int i = 0; i < n; i++) if (!vis[i]) {
		dist = infll;
		center = i;
		dfs1(i);
		dfs2(i);

		component.push_back(center);
		if (dist > mx) {
			mx = dist;
			vert = component.back();
		}
	}
	for (auto &u : component) if (u != vert) {
		adj[u].push_back(vert);
		adj[vert].push_back(u);
		len[u].push_back(L);
		len[vert].push_back(L);
	}
	dfs3(0);
	dfs3(diamv);
	cout << diam << endl;
}

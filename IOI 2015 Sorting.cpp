#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000010;

typedef pair<int, int> ii;
typedef long long ll;

int n, m;
vector<int> ar;

int ar1[MAXN], ar2[MAXN];

vector<ii> ans;

bool check(int t) {
	vector<int> cur = ar;
	for (int i = 0; i < t; i++) {
		swap(cur[ar1[i]], cur[ar2[i]]);
	}
	vector<ii> swaps;
	for (int i = 0; i < n; i++) {
		while (cur[i] != i) {
			swaps.emplace_back(cur[i], cur[cur[i]]);
			swap(cur[i], cur[cur[i]]);
		}
	}
	while (swaps.size() < t) swaps.emplace_back(0, 0);
	if (swaps.size() > t) return false;
	cur = ar;
	vector<int> ind(n);
	for (int i = 0; i < n; i++) {
		ind[cur[i]] = i;
	}
	vector<ii> ret;
	for (int i = 0; i < t; i++) {
		int x = ar1[i];
		int y = ar2[i];
		swap(ind[cur[x]], ind[cur[y]]);
		swap(cur[x], cur[y]);

		x = swaps[i].first;
		y = swaps[i].second;
		ret.emplace_back(ind[x], ind[y]);
		swap(cur[ind[x]], cur[ind[y]]);
		swap(ind[x], ind[y]);
	}
	ans = ret;
	return true;
}

int main() {
	cin >> n;
	ar = vector<int>(n);
	for (int i = 0; i < n; i++) {
		cin >> ar[i];
	}
	cin >> m;
	int sw = 0;
	for (int i = 0; i < m; i++) {
		cin >> ar1[i] >> ar2[i];
	}
	int lo = 0, hi = m;
	while (lo < hi) {
		int mid = lo + (hi - lo) / 2;
		if (check(mid)) {
			hi = mid;
		}
		else lo = mid + 1;
	}
	check(lo);
	cout << ans.size() << endl;
	for (int i = 0; i < ans.size(); i++) {
		cout << ans[i].first << " " << ans[i].second << endl;
	}
}

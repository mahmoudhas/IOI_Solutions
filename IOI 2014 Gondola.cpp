#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000010;
const int mod = 1000000009;
typedef pair<int, int> ii;

int modpow(int x, int y) {
	if (y == 0) return 1;
	if (y == 1) return x;
	int ret = modpow(x, y / 2);
	ret = 1LL * ret * ret % mod;
	if (y % 2) ret = 1LL * ret * x % mod;
	return ret;
}

int n;
int ar[MAXN];

set<int> there;
bool valid() {
	ar[n] = ar[0];
	for (int i = 0; i < n; i++) {
		if (there.count(ar[i])) return false;
		there.insert(ar[i]);
		if (ar[i] < n && (ar[i + 1] != ar[i] + 1 && ar[i + 1] <= n)) {
			return false;
		}
		if (ar[i] == n && (ar[i + 1] != 1 && ar[i + 1] <= n)) {
			return false;
		}
	}
	return true;
}

void replacement() {
	vector<ii> repl;
	bool fail = false;
	do {
		if (fail) {
			repl.emplace_back(ar[0], 1);
			ar[0] = 1;
		}
		for (int z = 0; z < 2 * n; z++) {
			int i = z % n;
			int j = (z + 1) % n;
			if (ar[i] > n) continue;
			if (ar[j] != ar[i] % n + 1) {
				repl.emplace_back(ar[j], ar[i] % n + 1);
				ar[j] = ar[i] % n + 1;
			}
		}
		fail = ar[0] > n;
	} while (fail);
	sort(repl.begin(), repl.end());
	int last = n + 1;
	vector<int> ans;
	for (int i = 0; i < repl.size(); i++) {
		while (repl[i].second < repl[i].first) {
			ans.push_back(repl[i].second);
			repl[i].second = last++;
		}
	}
	printf("%d", (int)ans.size());
	for (int i = 0; i < ans.size(); i++) {
		printf(" %d", ans[i]);
	}
	puts("");
}

int countReplacement() {
	if (!valid()) return 0;
	vector<int> big;
	for (int i = 0; i < n; i++) {
		if (ar[i] > n) {
			big.push_back(ar[i]);
		}
	}
	sort(big.begin(), big.end());
	int ans = big.size() == n ? n : 1;
	int gond = big.size();
	int cur = n + 1;
	for (int i = 0; i < big.size(); i++) {
		int d = big[i] - cur;
		ans = 1LL * ans * modpow(gond, d) % mod;
		cur = big[i] + 1;
		gond--;
	}
	return ans;
}

int main() {
	int subtask;
	scanf("%d", &subtask);
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", ar + i);
	}
	if (subtask >= 1 && subtask <= 3) {
		printf("%d\n", (int)valid());
	}
	if (subtask >= 4 && subtask <= 6) {
		replacement();
	}
	if (subtask >= 7 && subtask <= 10) {
		printf("%d\n", countReplacement());
	}
}

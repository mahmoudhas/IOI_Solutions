#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2000010;
const int inf = (1 << 30);

int n, q;
int dst[4 * MAXN], ust[4 * MAXN];
int ar[MAXN];
int t, ql, qr, h;

#define left (index << 1)
#define right (left + 1)
#define mid ((l + r) / 2)
void fix(int index) {
	int ind = left;
	for (; ind < left + 2; ind++) {

		dst[ind] = min(dst[ind], dst[index]);
		dst[ind] = max(dst[ind], ust[index]);
		ust[ind] = min(ust[ind], dst[index]);
		ust[ind] = max(ust[ind], ust[index]);

	}
}
void update(int index, int l, int r) {
	if (l > qr || r < ql) return;
	if (l >= ql && r <= qr) {
		if (t == 0) {
			dst[index] = min(dst[index], h);
			ust[index] = min(ust[index], h);
		}
		else {
			dst[index] = max(dst[index], h);
			ust[index] = max(ust[index], h);
		}
		return;
	}
	fix(index);
	dst[index] = inf;
	ust[index] = 0;
	update(left, l, mid);
	update(right, mid + 1, r);
}
void dfs(int index, int l, int r) {
	if (l == r) {
		ar[l] = ust[index];
		assert(ust[index] == dst[index]);
	}
	else {
		fix(index);
		dfs(left, l, mid);
		dfs(right, mid + 1, r);
	}
}
#undef left
#undef right
#undef mid

int main() {
	scanf("%d%d", &n, &q);
	while (q--) {
		scanf("%d%d%d%d", &t, &ql, &qr, &h);
		t = (t - 1) ^ 1;
		update(1, 0, n - 1);
	}
    dfs(1, 0, n - 1);
    for (int i = 0; i < n; i++) {
        printf("%d\n", ar[i]);
    }
}

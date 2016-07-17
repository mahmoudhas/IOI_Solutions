#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
#define fr first
#define sc second

const int MAXN = 50010;
const int MAXT = 1000010;

int n1, n2, t;
int ar1[MAXN], ar2[MAXN];

bool del[MAXT];
struct toy {
    int w1, w2;
    int id;
};
bool cmp1(toy a, toy b) {
    return a.w1 < b.w1 || (a.w1 == b.w1 && a.w2 < b.w2);
}
bool cmp2(toy a, toy b) {
    return a.w2 < b.w2 || (a.w2 == b.w2 && a.w1 < b.w1);
}
toy toys1[MAXT], toys2[MAXT];

bool check(int x) {
    int rem = t;
    priority_queue<ii> pq;
    int ind = 0;
    for (int i = 0; i < n1; i++) {
        while (ind != t && (del[toys1[ind].id] || toys1[ind].w1 < ar1[i])) {
            if (!del[toys1[ind].id])
                pq.push({ toys1[ind].w2, toys1[ind].id });
            ind++;
        }
        int tt = x;
        while (!pq.empty() && tt--) {
            int cur = pq.top().second;
            pq.pop();
            rem--;
            del[cur] = true;
        }
    }
    pq = priority_queue<ii>();
    ind = 0;
    for (int i = 0; i < n2; i++) {
        while (ind != t && (del[toys2[ind].id] || toys2[ind].w2 < ar2[i])) {
            if (!del[toys2[ind].id])
                pq.push({ toys2[ind].w1, toys2[ind].id });
            ind++;
        }
        int tt = x;
        while (!pq.empty() && tt--) {
            int cur = pq.top().second;
            pq.pop();
            del[cur] = true;
            rem--;
        }
    }
    return rem == 0;
}

int main() {
    scanf("%d%d%d", &n1, &n2, &t);
    for (int i = 0; i < n1; i++) {
        scanf("%d", ar1 + i);
    }
    for (int i = 0; i < n2; i++) {
        scanf("%d", ar2 + i);
    }
    for (int i = 0; i < t; i++) {
        int w1, w2;
        scanf("%d%d", &w1, &w2);
        toys1[i] = toys2[i] = { w1, w2, i };
    }
    sort(toys1, toys1 + t, cmp1);
    sort(toys2, toys2 + t, cmp2);
    if (n1) {
        sort(ar1, ar1 + n1);
    }
    if (n2) {
        sort(ar2, ar2 + n2);
    }
    int lo = 0, hi = t;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (check(mid)) {
            hi = mid;
        }
        else {
            lo = mid + 1;
        }
        memset(del, 0, sizeof del);
    }
    printf("%d\n", (check(lo) ? lo : -1));
}

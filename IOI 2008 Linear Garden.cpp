#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000010;

int n, mod;
string s;

int memo[MAXN][2][2][2];
int bt(int i, bool pref, bool pr1, bool pr2) {
    if (i >= n) return 1;
    int &ret = memo[i][pref][pr1][pr2];
    if (ret != -1) return ret;
    ret = 0;
    bool stop = false;
    if (i >= 2 && pr1 == pr2 && i + 1 < n) {
        if (!pref || (pref && !pr1 < s[i]) || (pref && !pr1 == s[i] && pr2 <= s[i + 1])) {
            ret += bt(i + 2, pref && s[i] == !pr1 && s[i + 1] == pr2, pr1, pr2);
        }
        if (!pref || (pref && !pr1 < s[i]) || (pref && !pr1 == s[i] && !pr2 <= s[i + 1])) {
            ret += bt(i + 2, pref && s[i] == !pr1 && s[i + 1] == !pr2, !pr1, !pr2);
        }
    }
    else {
        if (pr1 || pr2 || i < 2) {
            ret += bt(i + 1, pref && s[i] == 0, pr2, false);
        }
        if ((!pref || s[i] == 1) && (!pr1 || !pr2 || i < 2)) {
            ret += bt(i + 1, pref && s[i] == 1, pr2, true);
        }
    }
    ret %= mod;
    return ret;
}

int main() {
    ios::sync_with_stdio(false);

    cin >> n >> mod >> s;
    for (int i = 0; i < n; i++) {
        s[i] = s[i] == 'L' ? 0 : 1;
    }
    memset(memo, -1, sizeof memo);
    int ans = bt(0, true, 0, 0);
    cout << ans << "\n";
}

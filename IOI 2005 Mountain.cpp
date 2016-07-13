#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

struct node
{
    int l, r;
    int v;
    ll sum;
    ll mx;
    int prior;
    node *lef;
    node *rig;
    node(int a, int b, int c)
    {
        l = a;
        r = b;
        v = c;
        prior = rand();
        lef = rig = NULL;
    }
};

typedef node* pnode;

pnode root;

inline void upd(pnode t)
{
    if (!t) return;
    t->sum = 0;
    t->mx = 0;
    if (t->lef)
    {
        t->sum += t->lef->sum;
        t->mx = max(t->sum, t->lef->mx);
    }
    t->sum += 1LL * t->v * (t->r - t->l + 1);
    t->mx = max(t->mx, t->sum);
    if (t->rig)
    {
        t->mx = max(t->mx, t->sum + t->rig->mx);
        t->sum += t->rig->sum;
    }
}

void split(pnode t, pnode &l, pnode &r, int key)
{
    if (!t) l = r = NULL;
    else if (t->l > key)
    {
        split(t->lef, l, t->lef, key);
        r = t;
    }
    else
    {
        split(t->rig, t->rig, r, key);
        l = t;
    }
    upd(l);
    upd(r);
}
void merge(pnode &t, pnode l, pnode r)
{
    if (!l || !r)
    {
        t = l ? l : r;
    }
    else if (l->prior > r->prior)
    {
        merge(l->rig, l->rig, r);
        t = l;
    }
    else
    {
        merge(r->lef, l, r->lef);
        t = r;
    }
    upd(t);
}
void insert(pnode &t, pnode val)
{
    if (!t)
    {
        t = val;
        upd(t);
    }
    else
    {
        if (val->prior > t->prior)
        {
            split(t, val->lef, val->rig, val->l);
            t = val;
        }
        else
        {
            insert((val->l > t->l ? t->rig : t->lef), val);
        }
    }
    upd(t);
}
void erase(pnode &t, ii &val)
{
    if (!t) return;
    if (t->l == val.first && t->r == val.second)
    {
        pnode temp = t;
        merge(t, t->lef, t->rig);
        delete temp;
    }
    else erase((val.first > t->l ? t->rig : t->lef), val);
    upd(t);
}

struct st
{
    int l, r, val;
};

vector<st> toadd;
vector<ii> torem;

void dfs(pnode &t, ii &val)
{
    if (!t) return;
    if (t->r < val.first)
    {
        dfs(t->rig, val);
        return;
    }
    if (t->l > val.second)
    {
        dfs(t->lef, val);
        return;
    }
    torem.push_back({ t->l, t->r });
    if (t->l <= val.first - 1)
    {
        toadd.push_back({ t->l, val.first - 1, t->v });
    }
    if (val.second + 1 <= t->r)
    {
        toadd.push_back({ val.second + 1, t->r, t->v });
    }
    dfs(t->lef, val);
    dfs(t->rig, val);
}

int ans;
void query(pnode &t, int &f, ll sum, ll mx)
{
    if (!t) return;
    mx = max(mx, sum);
    ll tsum = sum + (t->lef ? t->lef->sum : 0);
    ll tmx = max(mx, sum + (t->lef ? t->lef->mx : 0));
    if (tmx > f)
    {
        query(t->lef, f, sum, mx);
        return;
    }
    if (t->v <= 0)
    {
        ans = max(ans, t->r);
    }
    else
    {
        ll tf = f - tsum;
        tf /= t->v;
        ans = max(1LL * ans, min(1LL * t->r, t->l - 1 + tf));
    }
    query(t->rig, f, tsum + 1LL * t->v * (t->r - t->l + 1), tmx);
}

int main()
{
    int n;
    cin >> n;
    pnode nd = new node(1, n, 0);
    insert(root, nd);
    char cmd;
    while (cin >> cmd)
    {
        if (cmd == 'I')
        {
            int l, r, d;
            cin >> l >> r >> d;
            ii tmp = { l, r };
            dfs(root, tmp);
            for (auto &v : torem)
            {
                erase(root, v);
            }
            for (auto &v : toadd)
            {
                nd = new node(v.l, v.r, v.val);
                insert(root, nd);
            }
            torem = vector<ii>();
            toadd = vector<st>();
            nd = new node(l, r, d);
            insert(root, nd);
        }
        else if (cmd == 'Q')
        {
            int f;
            cin >> f;
            ans = 0;
            query(root, f, 0, 0);
            cout << ans << endl;
        }
        else break;
    }
}

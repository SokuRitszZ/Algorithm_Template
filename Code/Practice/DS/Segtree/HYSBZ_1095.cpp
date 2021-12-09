#include <iostream>

#define CT const 
#define IL inline
#define endl '\n'
#define all(x) x.begin(), x.end()
#define MULTICASE() int _, kase; for (cin >> _, kase = 0; kase ++ , _ --;)

using namespace std;

typedef long long i6;

const int N = 1e5 + 10, M = N << 1;

int n;
int h[N], e[M], ne[M], idx;

struct Node
{
	int lp, rp, l1, l2, r1, r2, dis;	
}tr[N << 4];

void add(int a, int b)
{
	e[ ++ idx] = b, ne[idx] = h[a], h[a] = idx;
}

int s[N << 2], pos[N], c[N], tot;

void pushup(int x)
{
	int l = x << 1, r = x << 1 | 1;

	if (tr[l].rp > tr[r].lp)
		tr[x].lp = tr[l].lp, tr[x].rp = tr[r].rp + tr[l].rp - tr[r].lp;
	else 
		tr[x].lp = tr[l].lp + tr[r].lp - tr[l].rp, tr[x].rp = tr[r].rp;

	tr[x].l1 = max(tr[l].l1, max(tr[r].l1 + tr[l].lp - tr[l].rp, tr[r].l2 + tr[l].lp + tr[l].rp));
	tr[x].l2 = max(tr[l].l2, tr[r].l2 - tr[l].lp + tr[l].rp);
	tr[x].r1 = max(tr[r].r1, max(tr[l].r1 - tr[r].lp + tr[r].rp, tr[l].r2 + tr[r].lp + tr[r].rp));
	tr[x].r2 = max(tr[r].r2, tr[l].r2 + tr[r].lp - tr[r].rp);
	tr[x].dis = max(max(tr[l].r1 + tr[r].l2, tr[l].r2 + tr[r].l1), max(tr[l].dis, tr[r].dis));
}

void push(int u, int x)
{
	tr[u].lp = tr[u].rp = 0;
	tr[u].l1 = tr[u].l2 = tr[u].r1 = tr[u].r2 = tr[u].dis = -1e9;
	if (s[x] == -1) tr[u].rp = 1;
	else if (s[x] == -2) tr[u].lp = 1;
	else if (!c[s[x]]) tr[u].l1 = tr[u].r1 = tr[u].r2 = tr[u].l2 = 0;
}

void build(int l, int r, int u = 1)
{
	if (l == r) return push(u, r), void();

	int mid = l + r >> 1;
	build(l, mid, u << 1), build(mid + 1, r, u << 1 | 1);
	pushup(u);
}

void modify(int l, int r, int x, int u = 1)
{
	if (l == r) return push(u, r), void();
	int mid = l + r >> 1;
	if (x <= mid) modify(l, mid, x, u << 1);
	else modify(mid + 1, r, x, u << 1 | 1);
	pushup(u);
}

void dfs(int u, int f)
{
	s[ ++ tot] = -1;
	s[ ++ tot] = u, pos[u] = tot;
	for (int i = h[u]; i; i = ne[i])
	{
		int v = e[i];
		if (v == f) continue;
		dfs(v, u);
	}
	s[ ++ tot] = -2;
}

signed main(){
	cin >> n;
	for (int i = 1; i < n; ++ i)
	{
		int a, b; cin >> a >> b;
		add(a, b), add(b, a);
	}

	dfs(1, 0);

	build(1, tot);

	int m, cnt = n; cin >> m;

	while (m -- )
	{
		char op[2]; cin >> op;

		if (*op == 'C')
		{
			int x; cin >> x;
			cnt += c[x] ? 1 : -1;
			c[x] ^= 1, modify(1, tot, pos[x]);
		}
		else
		{
			if (cnt == 0) cout << -1 << endl;
			else if (cnt == 1) cout << 0 << endl;
			else cout << tr[1].dis << endl;
		}
	}
	return 0;
}
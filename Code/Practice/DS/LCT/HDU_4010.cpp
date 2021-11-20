#include <iostream>
#include <algorithm>

#define CT const 
#define IL inline
#define endl '\n'
#define all(x) x.begin(), x.end()
#define MULTICASE() int _, kase; for (cin >> _, kase = 0; kase ++ , _ --;)

using namespace std;

typedef long long i6;

CT int N = 3e5 + 10, INF = 2e9 + 10;

struct Node
{
	int s[2], f, v;
	int maxv, rev, tag;

	void init(int _v)
	{
		maxv = v = _v, s[0] = s[1] = f = rev = 0;
	}
}tr[N];

int n;

void pushadd(int x, int w)
{
	if (!x) return ;
	tr[x].v += w, tr[x].maxv += w, tr[x].tag += w;
}

void pushrev(int x)
{
	tr[x].rev ^= 1, swap(tr[x].s[0], tr[x].s[1]);
}

int stk[N], top;

void pushdown(int x){
	if (tr[x].rev)
	{
		pushrev(tr[x].s[0]), pushrev(tr[x].s[1]);
		tr[x].rev = 0;
	}
	if (tr[x].tag)
	{
		pushadd(tr[x].s[0], tr[x].tag), pushadd(tr[x].s[1], tr[x].tag);
		tr[x].tag = 0;
	}
}

void pushup(int x)
{
	tr[x].maxv = max(tr[x].v, max(tr[tr[x].s[0]].maxv, tr[tr[x].s[1]].maxv));
}
	
bool isroot(int x)
{
	return tr[tr[x].f].s[0] != x && tr[tr[x].f].s[1] != x;
}

void rotate(int x)
{
	int y = tr[x].f, z = tr[y].f;
	int p = tr[y].s[1] == x, c = tr[x].s[p ^ 1];
	if (!isroot(y)) tr[z].s[tr[z].s[1] == y] = x; tr[x].f = z;
	tr[x].s[p ^ 1] = y, tr[y].f = x;
	tr[y].s[p] = c, tr[c].f = y;
	pushup(y), pushup(x);
}

void splay(int x)
{
	int r = x;
	stk[ ++ top] = r;
	while (!isroot(r)) stk[ ++ top] = r = tr[r].f;
	while (top) pushdown(stk[top -- ]);

	while (!isroot(x))
	{
		int y = tr[x].f, z = tr[y].f;
		if (!isroot(y))
			(tr[y].s[1] == x) ^ (tr[z].s[1] == y) ? rotate(x) : rotate(y);
		rotate(x);
	}
}

void access(int x)
{
	int r = x;
	for (int y = 0; x; y = x, x = tr[x].f)
		splay(x), tr[x].s[1] = y, pushup(x);

	splay(r);	
}

void mkroot(int x)
{
	access(x);
	pushrev(x);
}

int find(int x)
{
	access(x);
	while (tr[x].s[0]) pushdown(x), x = tr[x].s[0];

	splay(x);
	return x;
}

void link(int x, int y)
{
	mkroot(x);
	if (find(y) != x) tr[x].f = y;
	else cout << -1 << endl;
}

void cut(int x, int y)
{
	mkroot(x);
	if (find(y) == x && tr[x].s[1] == y && tr[y].s[0] == 0)
		tr[x].s[1] = tr[y].f = 0, pushup(x);
	else cout << -1 << endl;
}

void solve(int x, int y)
{
	mkroot(x);
	if (x == y || find(y) != x)
	{
		cout << -1 << endl;
		return ;
	}
	splay(y);
	int p = tr[y].s[0];
	while (tr[p].s[1]) pushdown(p), p = tr[p].s[1];
	cut(p, y);
}
	
void split(int x, int y)
{
	mkroot(x), access(y);
}

int a[N], b[N];

signed main(){
	tr[0].v = tr[0].maxv = -INF;
	while (cin >> n)
	{
		for (int i = 1; i < n; ++ i) cin >> a[i] >> b[i];

		for (int i = 1; i <= n; ++ i)
		{
			int v; cin >> v;
			tr[i].init(v);
		}

		for (int i = 1; i < n; ++ i) link(a[i], b[i]);

		int m; cin >> m;
		int w, x, y, op;
		while (m -- )
		{
			cin >> op;
			if (op == 1)
			{
				cin >> x >> y;
				link(x, y);
			}
			else if (op == 2)
			{
				cin >> x >> y;
				solve(x, y);
			}
			else if (op == 3)
			{
				cin >> w >> x >> y;
				if (find(x) != find(y)) cout << -1 << endl;
				else split(x, y), pushadd(y, w);
			}
			else 
			{
				cin >> x >> y;
				if (find(x) != find(y)) cout << -1 << endl;
				else split(x, y), cout << tr[y].maxv << endl;
			}
		}
		cout << endl;
	}		
	return 0;
}
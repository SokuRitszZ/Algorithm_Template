#include <iostream>

#define CT const 
#define IL inline
#define endl '\n'
#define all(x) x.begin(), x.end()
#define MULTICASE() int _, kase; for (cin >> _, kase = 0; kase ++ , _ --;)

using namespace std;

typedef long long i6;

const int N = 3e4 + 10, INF = 2e9;

struct Node{
	int s[2], f, v;
	int maxv, sumv, rev;

	void init(int _v)
	{
		v = maxv = sumv = _v, s[0] = s[1] = f = rev = 0;
	}
}tr[N];

void pushrev(int x)
{
	tr[x].rev ^= 1;
	swap(tr[x].s[0], tr[x].s[1]);
}

void pushup(int x)
{
	tr[x].maxv = max(tr[x].v, max(tr[tr[x].s[0]].maxv, tr[tr[x].s[1]].maxv));
	tr[x].sumv = tr[tr[x].s[0]].sumv + tr[x].v + tr[tr[x].s[1]].sumv;
}

void pushdown(int x)
{
	if (tr[x].rev)
	{
		pushrev(tr[x].s[0]), pushrev(tr[x].s[1]);
		tr[x].rev = 0;
	}
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

int stk[N], top;

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
	int z = x;
	for (int y = 0; x; y = x, x = tr[x].f)
		splay(x), tr[x].s[1] = y, pushup(x);
	splay(z);
}

void mkroot(int x)
{
	access(x), pushrev(x);
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
}

void split(int x, int y)
{
	mkroot(x), access(y);
}

int a[N], b[N];

signed main(){
	
	int n; cin >> n;

	for (int i = 1; i < n; ++ i) {cin >> a[i] >> b[i]; }

	tr[0].init(-INF);
	for (int i = 1; i <= n; ++ i)
	{
		int v; cin >> v;
		tr[i].init(v);
	}

	for (int i = 1; i < n; ++ i) link(a[i], b[i]);

	int m; cin >> m;

	while (m -- )
	{
		string op; int x, y;
		cin >> op >> x >> y;
		if (op[0] == 'C')
		{
			mkroot(x), tr[x].v = y, pushup(x);
		}
		else if (op[1] == 'M')
		{
			split(x, y), cout << tr[y].maxv << endl;
		}
		else 
		{
			split(x, y), cout << tr[y].sumv << endl;
		}
	}
	return 0;
}
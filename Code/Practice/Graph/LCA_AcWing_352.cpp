#include <iostream>
#include <cstring>

#define CT const 
#define IL inline
#define endl '\n'
#define all(x) x.begin(), x.end()
#define MULTICASE() int sokuritszz, kase; for (cin >> sokuritszz, kase = 0; kase ++ , sokuritszz --;)

using namespace std;

typedef long long i6;

const int N = 1e5 + 10, M = N << 1;

int n, m;

int h[N], e[M], ne[M], idx;
int d[N], dep[N];

void add(int a, int b)
{
	e[ ++ idx] = b, ne[idx] = h[a], h[a] = idx;
}

int q[N];
int ff[N][17];

void bfs()
{
	memset(dep, 0x3f, sizeof dep);
	int hh = 0, tt = 0;
	q[0] = 1;
	dep[0] = 0;
	dep[1] = 1;
	while (hh <= tt)
	{
		int u = q[hh ++ ];
		for (int i = h[u]; i; i = ne[i])
		{
			int v = e[i];
			if (dep[v] > dep[u] + 1)
			{
				dep[v] = dep[u] + 1;
				q[ ++ tt] = v;
				ff[v][0] = u;
				for (int j = 1; j <= 16; ++ j)
					ff[v][j] = ff[ff[v][j - 1]][j - 1];
			}
		}
	}
}

int ans;

int dfs(int u, int f)
{
	int res = d[u];
	for (int i = h[u]; i; i = ne[i])
	{
		int v = e[i];
		if (v == f) continue;
		int s = dfs(v, u);
		if (s == 0) ans += m;
		else if (s == 1) ++ ans;
		res += s;
	}
	return res;
}

int lca(int a, int b)
{
	if (dep[a] < dep[b]) swap(a, b);
	for (int i = 16; i >= 0; -- i)
		if (dep[ff[a][i]] >= dep[b])
			a = ff[a][i];
	if (a == b) return a;
	for (int i = 16; i >= 0; -- i)
		if (ff[a][i] != ff[b][i]) 
			a = ff[a][i], b = ff[b][i];
	return ff[a][0];	
}

signed main()
{	
	cin.tie(0)->sync_with_stdio(false);	
	cin >> n >> m;
	for (int i = 1; i < n; ++ i)
	{
		int a, b; cin >> a >> b;
		add(a, b), add(b, a);
	}	

	bfs();

	for (int i = 0; i < m; ++ i)
	{
		int a, b; cin >> a >> b;
		int p = lca(a, b);
		++ d[a], ++ d[b], d[p] -= 2;
	}

	dfs(1, -1);

	cout << ans << endl;

	return 0;
}
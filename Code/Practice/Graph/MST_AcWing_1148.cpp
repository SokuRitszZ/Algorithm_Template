#include <iostream>
#include <algorithm>

#define CT const 
#define IL inline
#define endl '\n'
#define all(x) x.begin(), x.end()
#define MULTICASE() int sokuritszz, kase; for (cin >> sokuritszz, kase = 0; kase ++ , sokuritszz --;)

using namespace std;

typedef long long i6;

const int N = 510, M = 2e4 + 10;

struct Edge
{
	int a, b, w;
	bool f;
	bool operator < (const Edge &rhs) const
	{
		return w < rhs.w;
	}
}edge[M];

int n, m;
int p[N];
int h[N], e[N << 1], w[N << 1], ne[N << 1], idx;
int dist[N][2][N];

int find(int x)
{
	return x == p[x] ? x : p[x] = find(p[x]);
}

void add(int a, int b, int c)
{
	e[ ++ idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx;
}

void dfs(int u, int f, int maxd[2], int d[][N])
{
	d[0][u] = maxd[0], d[1][u] = maxd[1];
	for (int i = h[u]; i; i = ne[i])
	{
		int v = e[i];
		if (v == f) continue;
		int td0 = maxd[0], td1 = maxd[1];
		if (w[i] > td0) td1 = td0, td0 = w[i];
		else if (w[i] < td0 and w[i] > td1) td1 = w[i];
		int mxd[2]{td0, td1};
		dfs(v, u, mxd, d);
	}
}

signed main()
{	
	cin.tie(0)->sync_with_stdio(false);	
	cin >> n >> m;
	for (int i = 0; i < m; ++ i)
	{
		int a, b, w; cin >> a >> b >> w;
		edge[i] = {a, b, w, 0};
	}
	sort(edge, edge + m);
	for (int i = 1; i <= n; ++ i) p[i] = i;
	i6 sum = 0;
	for (int i = 0; i < m; ++ i)
	{
		auto [a, b, c, t] = edge[i];
		int pa = find(a), pb = find(b);
		if (pa != pb)
		{
			p[pa] = pb;
			sum += c;	
			edge[i].f = 1;
			add(a, b, c), add(b, a, c);
		}
	}
	for (int i = 1; i <= n; ++ i)
	{
		int maxd[2]{(int)-1e9, (int)-1e9};
		dfs(i, 0, maxd, dist[i]);
	}
	i6 res = 1e18;
	for (int i = 0; i < m; ++ i)
	{
		if (!edge[i].f)
		{
			auto [a, b, w, f] = edge[i];
			i6 t = 1e18;
			if (w > dist[a][0][b])
				t = sum + w - dist[a][0][b];
			else if (w > dist[a][1][b])
				t = sum + w - dist[a][1][b];
			res = min(res, t);
		}
	}

	cout << res << endl;
	return 0;
}
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

#define CT const 
#define IL inline
#define endl '\n'
#define all(x) x.begin(), x.end()
#define MULTICASE() int sokuritszz, kase; for (cin >> sokuritszz, kase = 0; kase ++ , sokuritszz --;)

using namespace std;

typedef long long i6;

const int INF = 0x3f3f3f3f, N = 1e5 + 10, M = 3e5 + 10;
int n, m;

struct Edge
{
	int a, b, c;
	bool f;
	bool operator < (const Edge &rhs) const
	{
		return c < rhs.c;
	}
}edge[M];

int h[N], e[M], w[M], ne[M], dep[N], p[N];
int fa[N][17], d1[N][17], d2[N][17];
int idx;

void graph_init(int n, int m)
{
}

int find(int x)
{
	return x == p[x] ? x : p[x] = find(p[x]);
}

void add(int a, int b, int c)
{
	e[ ++ idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx;
}

i6 mst()
{
	i6 sum = 0;
	sort(edge, edge + m);
	for (int i = 1; i <= n; ++ i) p[i] = i;
	for (int i = 0; i < m; ++ i)
	{
		auto& [a, b, c, f] = edge[i];
		int pa = find(a), pb = find(b);
		if (pa != pb)
		{
			add(a, b, c), add(b, a, c);
			p[pa] = pb;
			sum += c;
			f = 1;
		}
	}
	return sum;
}

void bfs()
{
	memset(dep, 0x3f, sizeof dep);
	dep[0] = 0, dep[1] = 1;
	int hh = 0, tt = -1;
	vector<int> q(n + 1);
	q[ ++ tt] = 1;
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
				fa[v][0] = u;
				d1[v][0] = w[i], d2[v][0] = -INF;
				for (int j = 1; j <= 16; ++ j)
				{
					int anc = fa[v][j - 1];
					fa[v][j] = fa[anc][j - 1];
					int distance[4]{
						d1[v][j - 1], d2[v][j - 1], d1[anc][j - 1], d2[anc][j - 1]
					};
					d1[v][j] = d2[v][j] = -INF;
					for (int k = 0; k < 4; ++ k)
					{
						int d = distance[k];
						if (d > d1[v][j])
							d2[v][j] = d1[v][j], d1[v][j] = d;
						else if ((d - d1[v][j]) and d > d2[v][j]) 
							d2[v][j] = d;
					}
				}
			}
		}
	}
}

i6 lca(int a, int b, int c)
{
	static vector<int> distance(n << 1);
	int cnt = 0;
	if (dep[a] < dep[b]) swap(a, b);
	for (int i = 16; i >= 0; -- i)
		if (dep[fa[a][i]] >= dep[b])
		{
			distance[cnt ++ ] = d1[a][i];
			distance[cnt ++ ] = d2[a][i];
			a = fa[a][i];
		}
	if (a != b)
	{
		for (int i = 16; i >= 0; -- i)
			if (fa[a][i] != fa[b][i])
			{
				distance[cnt ++ ] = d1[a][i];
				distance[cnt ++ ] = d2[a][i];
				distance[cnt ++ ] = d1[b][i];
				distance[cnt ++ ] = d2[b][i];
				a = fa[a][i], b = fa[b][i];
			}
		distance[cnt ++ ] = d1[a][0];
		distance[cnt ++ ] = d1[b][0];
	}
	int dist1 = -INF, dist2 = -INF;
	for (int i = 0; i < cnt; ++ i)
		if (distance[i] > dist1)
			dist2 = dist1, dist1 = distance[i];
		else if ((distance[i] - dist1) and distance[i] - dist2)
			dist2 = distance[i];	
	if (c > dist1) return c - dist1;
	if (c > dist2) return c - dist2;
	return (i6) INF << 32 | INF;
}

signed main()
{	
	cin.tie(0)->sync_with_stdio(false);	
	cin >> n >> m;
	graph_init(n, m);
	for (int i = 0; i < m; ++ i)
	{
		int a, b, c; cin >> a >> b >> c;
		edge[i] = {a, b, c, 0};
	}	

	// return 0;
	i6 sum = mst();
	bfs();

	i6 res = (i6) INF << 32 | INF;
	for (int i = 0; i < m; ++ i){
		auto& [a, b, c, f] = edge[i];
		if (!f)
			res = min(res, sum + lca(a, b, c));
	}

	cout << res << endl;
	return 0;
}
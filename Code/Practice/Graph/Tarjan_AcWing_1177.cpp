#include <iostream>
#include <cstring>
#include <algorithm>
#include <unordered_set>

#define CT const 
#define IL inline
#define endl '\n'
#define all(x) x.begin(), x.end()
#define MULTICASE() int sokuritszz, kase; for (cin >> sokuritszz, kase = 0; kase ++ , sokuritszz --;)

using namespace std;

typedef long long i6;

const int N = 1e5 + 10, M = 2e6 + 10;

int n, m, mod;
int h[N], hs[N], e[M], ne[M], idx;
int dfn[N], low[N], timestp;
int stk[N], top;
bool in_stk[N];
int id[N], scc_cnt, sz[N];
int f[N], g[N];

void add(int h[], int a, int b)
{
	e[ ++ idx] = b, ne[idx] = h[a], h[a] = idx;
}

void tarjan(int u)
{
	dfn[u] = low[u] = ++ timestp;
	stk[ ++ top] = u, in_stk[u] = 1;

	for (int i = h[u]; i; i = ne[i])
	{
		int v = e[i];
		if (!dfn[v])
			tarjan(v), low[u] = min(low[u], low[v]);
		else if (in_stk[v])
			low[u] = min(low[u], dfn[v]);
	}

	if (dfn[u] == low[u])
	{
		++ scc_cnt;
		int y; 
		do
		{
			y = stk[top -- ];
			in_stk[y] = 0;
			id[y] = scc_cnt;
			++ sz[scc_cnt];
		}while (y - u);
	}
}

signed main()
{	
	cin.tie(0)->sync_with_stdio(false);	
	cin >> n >> m >> mod;
	while (m -- )
	{
		int a, b; cin >> a >> b;
		add(h, a, b);
	}

	for (int i = 1; i <= n; ++ i)
		if (!dfn[i]) tarjan(i);
	
	unordered_set<i6> S;
	for (int i = 1; i <= n; ++ i)
	{
		for (int j = h[i]; j; j = ne[j])
		{
			int k = e[j];
			int a = id[i], b = id[k];
			i6 hash = 1000000ll * a + b;
			if (a != b and !S.count(hash))
			{
				add(hs, a, b);
				S.insert(hash);
			}	
		}
	}	

	for (int i = scc_cnt; i; -- i)
	{
		if (!f[i])
		{
			f[i] = sz[i];
			g[i] = 1;
		}
		for (int j = hs[i]; j; j = ne[j])
		{
			int k = e[j];
			if (f[k] < f[i] + sz[k])
			{
				f[k] = f[i] + sz[k];
				g[k] = g[i];
			}
			else if (f[k] == f[i] + sz[k])
			{
				g[k] = (g[k] + g[i]) % mod;
			}
		}
	}

	int maxf = 0, sum = 0;
	for (int i = 1; i <= scc_cnt; ++ i)
		{
		if (f[i] > maxf)
		{
			maxf = f[i];
			sum = g[i];
		}
		else if (f[i] == maxf)
		{
			sum = (sum + g[i]) % mod;
		}
	}
	cout << maxf << endl << sum << endl;
	return 0;
}		
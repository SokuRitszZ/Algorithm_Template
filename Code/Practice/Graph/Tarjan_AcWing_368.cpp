#include <iostream>
#include <algorithm>

#define CT const 
#define IL inline
#define endl '\n'
#define all(x) x.begin(), x.end()
#define MULTICASE() int sokuritszz, kase; for (cin >> sokuritszz, kase = 0; kase ++ , sokuritszz --;)

using namespace std;

typedef long long i6;

const int N = 1e5 + 10, M = N * 6;

int n, m;
int h[N], hs[N], e[M], w[M], ne[M], idx;
int dfn[N], low[N], scc_cnt, sz[N], id[N], timestp;
int stk[N], top;
bool in_stk[N];
int d[N];

void add(int h[], int a, int b, int c)
{
	e[ ++ idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx;
}

void tarjan(int u)
{
	dfn[u] = low[u] = ++ timestp;
	in_stk[stk[ ++ top] = u] = 1;

	for (int i = h[u]; i; i = ne[i])
	{
		int v = e[i];
		if (!dfn[v]) tarjan(v), low[u] = min(low[u], low[v]);
		else if (in_stk[v]) low[u] = min(low[u], dfn[v]);
	}

	if (dfn[u] == low[u])
	{
		++ scc_cnt;
		int y;
		do
		{
			in_stk[y = stk[top --]] = 0;
			id[y] = scc_cnt;
			++ sz[scc_cnt];
		}while (y - u);
	}
}

signed main()
{	
	cin.tie(0)->sync_with_stdio(false);	
	cin >> n >> m;
	for (int i = 1; i <= n; ++ i) add(h, 0, i, 1);

	while (m -- )
	{
		int t, a, b; cin >> t >> a >> b;
		if (t == 1) add(h, a, b, 0), add(h, b, a, 0);
		else if (t == 2) add(h, a, b, 1);
		else if (t == 3) add(h, b, a, 0);
		else if (t == 4) add(h, b, a, 1);
		else if (t == 5) add(h, a, b, 0);
	}

	tarjan(0);

	bool success = 1;
	for (int i = 0; i <= n; ++ i)
	{
		for (int j = h[i]; j; j = ne[j])
		{
			int k = e[j];
			int a = id[i], b = id[k];
			if (a == b)
			{
				if (w[j] > 0)
				{
					success = 0;
					break;
				}
			}
			else add(hs, a, b, w[j]); // printf("edge %d %d\n", a, b);
		}
		if (!success) break;
	}

	if (!success) cout << -1 << endl;
	else 
	{
		for (int i = scc_cnt; i; -- i)
		{
			for (int j = hs[i]; j; j = ne[j])
			{
				int k = e[j];
				d[k] = max(d[k], d[i] + w[j]);
			}
			// printf("dist %d %d\n", i, d[i]);
		}
		i6 res = 0;
		for (int i = 1; i <= scc_cnt; ++ i) res += (i6) d[i] * sz[i];
		cout << res << endl;
	}
	return 0;
}
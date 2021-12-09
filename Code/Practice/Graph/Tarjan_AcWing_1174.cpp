#include <iostream>

#define CT const 
#define IL inline
#define endl '\n'
#define all(x) x.begin(), x.end()
#define MULTICASE() int sokuritszz, kase; for (cin >> sokuritszz, kase = 0; kase ++ , sokuritszz --;)

using namespace std;

typedef long long i6;

const int N = 1e4 + 10, M = 5e4 + 10;

int n, m;
int h[N], e[M], ne[M], idx;
int dfn[N], low[N], timestp;
int stk[N], top;
bool in_stk[N];
int id[N], scc_cnt, sz[N];
int dout[N];

void add(int a, int b)
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
			tarjan(v);
		low[u] = min(low[u], low[v]);
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
		}while (y != u);
	}
}

signed main()
{	
	cin.tie(0)->sync_with_stdio(false);	
	cin >> n >> m;
	while (m -- )
	{
		int a, b; cin >> a >> b;
		add(a, b);
	}		

	for (int i = 1; i <= n; ++ i)
		if (!dfn[i]) tarjan(i);

	for (int i = 1; i <= n; ++ i)
	{
		for (int j = h[i]; j; j = ne[j])
		{
			int v = e[j];
			int a = id[i], b = id[v];
			if (a - b) ++ dout[a];	
		}
	}

	int zeros = 0, sum = 0;
	for (int i = 1; i <= scc_cnt; ++ i)
		if (!dout[i])
		{
			++ zeros;
			sum += sz[i];
			if (zeros > 1)
			{
				sum = 0;
				break;
			}
		}

	cout << sum << endl;
	return 0;
}
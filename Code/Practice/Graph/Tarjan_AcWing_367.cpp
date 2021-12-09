#include <iostream>

#define CT const 
#define IL inline
#define endl '\n'
#define all(x) x.begin(), x.end()
#define MULTICASE() int sokuritszz, kase; for (cin >> sokuritszz, kase = 0; kase ++ , sokuritszz --;)

using namespace std;

typedef long long i6;

const int N = 100 + 10, M = N * N;

int n, m;
int h[N], e[M], ne[M], idx;
int low[N], dfn[N], din[N], dout[N], scc_cnt, timestp, id[N];
int stk[N], top;
bool in_stk[N];

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
		if (!dfn[v]) tarjan(v), low[u] = min(low[u], low[v]);
		else if (in_stk[v]) low[u] = min(low[u], dfn[v]);
	}
	if (dfn[u] == low[u])
	{
		++ scc_cnt;
		int y;
		do
		{
			in_stk[y = stk[top -- ]] = 0;
			id[y] = scc_cnt;
		}while (y - u);
	}	
}

signed main()
{	
	cin.tie(0)->sync_with_stdio(false);	
	cin >> n;
	for (int i = 1; i <= n; ++ i)
	{
		int x;
		while (cin >> x, x) add(i, x);
	}

	for (int i = 1; i <= n; ++ i)
		if (!dfn[i]) tarjan(i);
	
	for (int i = 1; i <= n; ++ i)
	{
		for (int j = h[i]; j; j = ne[j])
		{
			int v = e[j];
			int a = id[i], b = id[v];
			if (a != b) ++ din[b], ++ dout[a];
		}
	}

	int a = 0, b = a;
	for (int i = 1; i <= scc_cnt; ++ i)
	{
		if (!din[i]) ++ a;
		if (!dout[i]) ++ b;
	}
	cout << a << endl;
	if (scc_cnt == 1) cout << 0 << endl;
	else cout << max(a, b) << endl;
	return 0;
}
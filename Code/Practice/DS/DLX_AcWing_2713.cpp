#include <iostream>
#include <cstring>

#define CT const 
#define IL inline
#define endl '\n'
#define all(x) x.begin(), x.end()
#define MULTICASE() int sokuritszz, kase; for (cin >> sokuritszz, kase = 0; kase ++ , sokuritszz --;)

using namespace std;

typedef long long i6;

const int N = 1e4 + 10;

int n, m;
int l[N], r[N], u[N], d[N], row[N], col[N], s[N], idx;
int ans[N];
bool st[110];

void init()
{
	for (int i = 0; i <= m; ++ i)
	{
		l[i] = i - 1, r[i] = i + 1;
		col[i] = u[i] = d[i] = i;
		s[i] = 0;
	}
	l[0] = m, r[m] = 0;
	idx = m + 1;
}

void add(int &hh, int &tt, int x, int y)
{
	row[idx] = x, col[idx] = y, ++ s[y];
	u[idx] = y, d[idx] = d[y], u[d[y]] = idx, d[y] = idx;
	r[hh] = l[tt] = idx, l[idx] = hh, r[idx] = tt = idx ++ ;
}

int f()
{
	int cnt = 0;
	memset(st, 0, sizeof st);
	for (int i = r[0]; i; i = r[i])
	{
		if (st[col[i]]) continue;
		++ cnt;
		st[col[i]] = 1;
		for (int j = d[i]; j != i; j = d[j])
			for (int k = r[j]; k != j; k = r[k]) 
				st[col[k]] = 1;
	}
	return cnt;
}

void rm(int p)
{
	for (int i = d[p]; i != p; i = d[i])
	{
		l[r[i]] = l[i], r[l[i]] = r[i];
	}
}

void rs(int p)
{
	for (int i = u[p]; i != p; i = u[i])
		l[r[i]] = r[l[i]] = i;
}

bool dfs(int k, int dep)
{
	if (k + f() > dep) return 0;
	if (!r[0]) return 1;
	int p = r[0];
	for (int i = p; i; i = r[i])
		if (s[i] < s[p]) p = i;

	for (int i = d[p]; i != p; i = d[i])
	{
		ans[k] = row[i];
		rm(i);
		for (int j = r[i]; j != i; j = r[j]) rm(j);
		if (dfs(k + 1, dep)) return 1;
		for (int j = l[i]; j != i; j = l[j]) rs(j);
		rs(i);
	}

	return 0;
}

signed main()
{	
	scanf("%d %d", &n, &m);
	init();
	for (int i = 1; i <= n; ++ i)
	{
		int hh = idx, tt = idx;
		for (int j = 1; j <= m; ++ j)
		{
			int x; scanf("%d", &x);
			if (x) add(hh, tt, i, j);
		}
	}

	int dep = 0;
	while (!dfs(0, dep)) ++ dep;
	printf("%d\n", dep);
	for (int i = 0; i < dep; ++ i) printf("%d ", ans[i]);
	return 0;
}
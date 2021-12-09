#include <iostream>

#define CT const 
#define IL inline
#define endl '\n'
#define all(x) x.begin(), x.end()
#define MULTICASE() int sokuritszz, kase; for (cin >> sokuritszz, kase = 0; kase ++ , sokuritszz --;)

using namespace std;

typedef long long i6;

const int N = 5e4 + 10, M = 3 * N;

int h[N], hs[N], e[M], w[M], ne[M], idx;

void add(int h[], int a, int b, int c)
{
	e[ ++ idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx;
}

int f[N], d[N];
int q[N];
bool st[N];
int n, m;

void spfa()
{
	for (int i = 0; i <= n; ++ i) d[i] = -0x3f3f3f3f;
	d[0] = 0;
	st[0] = 1;
	int hh = 0, tt = 1;
	while (hh != tt)
	{
		int u = q[hh ++ ];
		hh %= n;
		st[u] = 0;

		for (int i = h[u]; i; i = ne[i])
		{
			int v = e[i];
			if (d[v] < d[u] + w[i])
			{
				d[v] = d[u] + w[i];
				if (!st[v])
				{
					st[v] = 1;
					q[tt ++ ] = v;
					tt %= n;
				}
			}
		}
	}
}

signed main()
{	
	cin.tie(0)->sync_with_stdio(false);	
	cin >> m;
	while (m -- )
	{
		int a, b, c; cin >> a >> b >> c;
		++ b;
		n = max(n, max(a, b));
		add(h, a, b, c);
	}

	for (int i = 1; i <= n; ++ i)
		add(h, i - 1, i, 0), add(h, i, i - 1, -1);

	spfa();
	cout << d[n] << endl;
	return 0;
}
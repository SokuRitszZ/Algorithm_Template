#include <iostream>

#define CT const 
#define IL inline
#define endl '\n'
#define all(x) x.begin(), x.end()
#define MULTICASE() int sokuritszz, kase; for (cin >> sokuritszz, kase = 0; kase ++ , sokuritszz --;)

using namespace std;

typedef long long i6;

const int N = 2e4 + 10;

int l[N], r[N], u[N], d[N], row[N], col[N], s[N], idx;
int m = 1 << 10;
int ans[N], top;
char grid[20][20];

struct Op
{
	int x, y;
	char z;
}op[N];

void init()
{
	for (int i = 0; i <= m; ++ i)
	{
		l[i] = i - 1, r[i] = i + 1;
		s[i] = 0;
		d[i] = u[i] = i;
	}
	l[0] = m, r[m] = 0;
	idx = m + 1;
}

void add(int &hh, int &tt, int x, int y)
{
	row[idx] = x, col[idx] = y, ++ s[y];
	u[idx] = y, d[idx] = d[y], u[d[y]] = idx, d[y] = idx;
	r[hh] = l[tt] = idx, r[idx] = tt, l[idx] = hh;
	tt = idx ++ ;
}

void remove(int p)
{
	l[r[p]] = l[p], r[l[p]] = r[p];
	for (int i = d[p]; i != p; i = d[i])
	{
		for (int j = l[i]; j != i; j = l[j])
		{
			-- s[col[j]];
			u[d[j]] = u[j], d[u[j]] = d[j];
		}
	}
}

void resume(int p)
{
	for (int i = u[p]; i != p; i = u[i])
	{
		for (int j = r[i]; j != i; j = r[j])
		{
			u[d[j]] = d[u[j]] = j;
			++ s[col[j]];
		}
	}
	l[r[p]] = r[l[p]] = p;
}

bool dfs()
{
	if (!r[0]) return 1;
	int p = r[0];
	for (int i = r[0]; i; i = r[i]) 
		if (s[p] > s[i]) p = i; 
	remove(p);
	for (int i = d[p]; i != p; i = d[i])
	{
		ans[ ++ top] = row[i];
		for (int j = r[i]; j != i; j = r[j]) remove(col[j]);
		if (dfs()) return 1;
		for (int j = l[i]; j != i; j = l[j]) resume(col[j]);
		-- top;
	}
	resume(p);
	return 0;
}

signed main(){	
	cin.tie(0)->sync_with_stdio(false);	
	
	while (cin >> grid[0])
	{
		for (int i = 1; i < 16; ++ i) cin >> grid[i];
			init();
		for (int i = 0, n = 1; i < 16; ++ i)
		{
			for (int j = 0; j < 16; ++ j)
			{
				int a = 0, b = 15;
				if (grid[i][j] != '-') a = b = grid[i][j] - 'A';
				for (int k = a; k <= b; ++ k, ++ n)
				{
					int hh = idx, tt = idx;
					op[n] = {i, j, k + 'A'};
					add(hh, tt, n, i * 16 + j + 1);
					add(hh, tt, n, 256 + i * 16 + k + 1);
					add(hh, tt, n, 256 * 2 + j * 16 + k + 1);
					add(hh, tt, n, 256 * 3 + (i / 4 * 4 + j / 4) * 16 + k + 1);
				}
			}
		}
		dfs();
		for (int i = 1; i <= top; ++ i)
		{
			auto t = op[ans[i]];
			grid[t.x][t.y] = t.z;
		}

		for (int i = 0; i < 16; ++ i) cout << grid[i] << endl;
		cout << endl;
	}	
	
	return 0;
}
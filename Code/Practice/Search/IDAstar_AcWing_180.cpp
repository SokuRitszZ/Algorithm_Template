#include <iostream>
#include <cstring>

#define CT const 
#define IL inline
#define endl '\n'
#define all(x) x.begin(), x.end()
#define MULTICASE() int sokuritszz, kase; for (cin >> sokuritszz, kase = 0; kase ++ , sokuritszz --;)

using namespace std;

typedef long long i6;

const int N = 20;

int n;
int a[N], w[N][N];

int f()
{
	int tot = 0;
	for (int i = 1; i < n; ++ i)
		tot += a[i + 1] != a[i] + 1;
	return (tot + 2) / 3;
}

bool check()
{
	for (int i = 1; i <= n; ++ i)
		if (i != a[i]) return 0;
	return 1;
}

bool dfs(int dep, int max_dep)
{
	if (dep + f() > max_dep) return 0;
	if (check()) return 1;

	for (int len = 1; len <= n; ++ len)
	{
		for (int l = 1, r; (r = l + len - 1) <= n; ++ l)
		{
			for (int k = r + 1; k <= n; ++ k)
			{
				memcpy(w[dep], a, sizeof a);
				int x, y;
				for (x = r + 1, y = l; x <= k; ++ x, ++ y) a[y] = w[dep][x];
				for (x = l; x <= r; ++ x, ++ y) a[y] = w[dep][x];
				if (dfs(dep + 1, max_dep)) return 1;
				memcpy(a, w[dep], sizeof a);
			}
		}
	}

	return 0;
}

signed main()
{	
	cin.tie(0)->sync_with_stdio(false);	
	MULTICASE()
	{
		cin >> n;
		for (int i = 1; i <= n; ++ i) cin >> a[i];
		int dep = 0;
		while (dep < 5 and !dfs(0, dep)) ++ dep;
		if (dep >= 5) cout << "5 or more" << endl;
		else cout << dep << endl;
	}		
	return 0;
}

// 7 6 5 4 3 2 1 === 6
// 6 7 4 5 2 3 1   + 3
// 1 2 3 4 5 6 7   + 3
// 2 1 3 最理 -> 1 2 3 +1 

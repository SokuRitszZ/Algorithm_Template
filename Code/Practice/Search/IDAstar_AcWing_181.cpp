#include <iostream>
#include <cstring>

#define CT const 
#define IL inline
#define endl '\n'
#define all(x) x.begin(), x.end()
#define MULTICASE() int sokuritszz, kase; for (cin >> sokuritszz, kase = 0; kase ++ , sokuritszz --;)

using namespace std;

typedef long long i6;

/*
      00    01
 	    02    03
04 05 06 07 08 09 10
      11    12
13 14 15 16 17 18 19
      20    21
      22    23
*/

const int N = 24;

int op[8][7]{
	{0, 2, 6, 11, 15, 20, 22},
	{1, 3, 8, 12, 17, 21, 23},
	{10, 9, 8, 7, 6, 5, 4},
	{19, 18, 17, 16, 15, 14, 13},
	{23, 21, 17, 12, 8, 3, 1},
	{22, 20, 15, 11, 6, 2, 0},
	{13, 14, 15, 16, 17, 18, 19},
	{4, 5, 6, 7, 8, 9, 10}
};

int opposite[8]{5, 4, 7, 6, 1, 0, 3, 2};
int center[8]{6, 7, 8, 12, 17, 16, 15, 11};
int q[N], path[100], n;

int f()
{
	static int sum[4];
	memset(sum, 0, sizeof sum);
	for (int i = 0; i < 8; ++ i) ++ sum[q[center[i]]];
	int s = 0;
	for (int i = 1; i <= 3; ++ i) s = max(s, sum[i]);
	return 8 - s;
}

bool check()
{
	for (int i = 1; i < 8; ++ i)
		if (q[center[i]] != q[center[0]]) return 0;
	return 1;
}

void operate(int x)
{
	int t = q[op[x][0]];
	for (int i = 0; i < 6; ++ i) q[op[x][i]] = q[op[x][i + 1]];
	q[op[x][6]] = t;
}

bool dfs(int dep, int max_dep, int last)
{
	if (dep + f() > max_dep) return 0;
	if (check()) return 1;

	for (int i = 0; i < 8; ++ i)
	{
		if (opposite[i] == last) continue;
		operate(i);
		path[dep] = i;
		if (dfs(dep + 1, max_dep, i)) return 1;
		operate(opposite[i]);
	}

	return 0;
}

signed main()
{	
	cin.tie(0)->sync_with_stdio(false);	
	while (cin >> q[0], q[0])
	{
		for (int i = 1; i < N; ++ i) cin >> q[i];
		int dep = 0;
		while (!dfs(0, dep, -1)) ++ dep;
		// cout << dep << endl;
		if (!dep) cout << "No moves needed" << endl;
		else
		{
			for (int i = 0; i < dep; ++ i) cout << char(path[i] + 'A');
			cout << endl;
		}
		cout << q[6] << endl;
	}		
	return 0;
}
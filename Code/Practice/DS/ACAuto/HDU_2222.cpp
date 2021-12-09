#include <iostream>
#include <cstring>
#include <string>

#define CT const 
#define IL inline
#define endl '\n'
#define all(x) x.begin(), x.end()
#define MULTICASE() int _, kase; for (cin >> _, kase = 0; kase ++ , _ --;)

using namespace std;

typedef long long i6;

const int N = 1e4 + 10, M = N * 55;

int tr[M][26], idx;
int cnt[M], fail[M];
int n, m;

void insert(string s)
{
	int u = 0;
	for (int i = 0; i < s.size(); ++ i)
	{
		int v = s[i] - 'a';
		if (!tr[u][v]) tr[u][v] = ++ idx;
		u = tr[u][v];
	}
	++ cnt[u];
}

int q[M];
void get_fail()
{
	int hh = 0, tt = -1;
	for (int i = 0; i < 26; ++ i)
	{
		if (tr[0][i]) q[ ++ tt] = tr[0][i];
	}

	while (hh <= tt)
	{
		int u = q[hh ++ ];
		for (int i = 0; i < 26; ++ i)
		{
			if (tr[u][i]) fail[tr[u][i]] = tr[fail[u]][i], q[ ++ tt] = tr[u][i];
			else tr[u][i] = tr[fail[u]][i];
		}
	}
}

int check(string s)
{
	int u = 0, res = 0;
	for (int i = 0; i < s.size(); ++ i)
	{
		int v = s[i] - 'a';
		int j = u = tr[u][v];
		while (j)
		{
			res += cnt[j];
			cnt[j] = 0;
			j = fail[j];
		}
	}

	return res;
}

signed main(){
	cin.tie(0)->sync_with_stdio(false);

	MULTICASE()
	{
		memset(cnt, 0, sizeof cnt);
		memset(fail, 0, sizeof fail);
		memset(tr, 0, sizeof tr);
		idx = 0;
		cin >> n;
		for (int i = 1; i <= n; ++ i)	
		{
			string s; cin >> s;
			insert(s);
		}

		get_fail();

		string s; cin >> s;
		cout << check(s) << endl;
	}
	return 0;
}
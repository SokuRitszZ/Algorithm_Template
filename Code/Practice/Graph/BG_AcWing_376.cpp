#include <iostream>
#include <cstring>

#define CT const 
#define IL inline
#define endl '\n'
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegia(), x.rend()
#define MULTICASE() int sokuritszz, kase; for (cin >> sokuritszz, kase = 0; kase ++ , sokuritszz --;)

using namespace std;

typedef long long i6;

const int N = 110;

int n, m, k;
bool g[N][N], st[N];
int match[N];

bool find(int u)
{
  for (int i = 1; i < m; ++ i)
  {
    if (!st[i] and g[u][i])
    {
      st[i] = 1;
      int t = match[i];
      if (t == 0 or find(t))
      {
        match[i] = u;
        return 1;
      }
    }
  }

  return 0;
}

signed main()
{ 
  cin.tie(0)->sync_with_stdio(false); 

  while (cin >> n, n)
  {
    cin >> m >> k;

    memset(g, 0, sizeof g);
    memset(match, 0, sizeof match);

    while (k -- )
    {
      int t, a, b; cin >> t >> a >> b;
      if (!a or !b) continue;
      g[a][b] = 1;
    }

    int res = 0;
    for (int i = 1; i < n; ++ i)
    {
      memset(st, 0, sizeof st);
      if (find(i)) ++ res;
    }

    cout << res << endl; 
  }
  return 0;
}
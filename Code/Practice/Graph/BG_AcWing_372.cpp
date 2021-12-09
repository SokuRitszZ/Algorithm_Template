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
typedef pair<int, int> pii;

const int N = 110;

int n, m;

bool g[N][N], st[N][N];
pii match[N][N];

bool dfs(int x, int y)
{
  static int dx[]{0, 0, 1, -1}, dy[]{1, -1, 0, 0};

  for (int i = 0; i < 4; ++ i)
  {
    int xx = x + dx[i], yy = y + dy[i];

    if (xx < 1 or xx > n or yy < 1 or yy > n) continue;
    if (st[xx][yy] or g[xx][yy]) continue;

    st[xx][yy] = 1;
    auto t = match[xx][yy];
    if (t.first == 0 or dfs(t.first, t.second))
    {
      match[xx][yy] = {x, y};
      return 1;
    }
  }

  return 0;
}

signed main()
{ 
  cin.tie(0)->sync_with_stdio(false); 
  cin >> n >> m;

  while (m -- )
  {
    int a, b; cin >> a >> b;
    g[a][b] = 1;
  }

  int res = 0;
  for (int i = 1; i <= n; ++ i)
  {
    for (int j = 1; j <= n; ++ j)
    {
      if ((i + j & 1) and !g[i][j])
      {
        memset(st, 0, sizeof st);
        res += dfs(i, j);
      }
    }
  }

  cout << res << endl;

  return 0;
}
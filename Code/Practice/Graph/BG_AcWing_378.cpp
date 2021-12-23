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

int n, m, k;
pii match[N][N];
bool g[N][N], st[N][N];

bool find(int x, int y)
{
  static int dx[]{-1, 1, 2, 2, 1, -1, -2, -2};
  static int dy[]{-2, -2, -1, 1, 2, 2, 1, -1};

  for (int i = 0; i < 8; ++ i)
  {
    int xx = x + dx[i], yy = y + dy[i];
    if (xx < 1 or xx > n or yy < 1 or yy > m) continue;
    if (g[xx][yy] or st[xx][yy]) continue;
    st[xx][yy] = 1;

    pii t = match[xx][yy];
    if (t.first == 0 or find(t.first, t.second))
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
  cin >> n >> m >> k;

  for (int i = 0; i < k; ++ i)
  {
    int x, y; cin >> x >> y;
    g[x][y] = 1;
  }

  int res = 0;
  for (int i = 1; i <= n; ++ i)
  {
    for (int j = 1; j <= m; ++ j)
    {
      if ((i + j & 1) or g[i][j]) continue;
      memset(st, 0, sizeof st);
      res += find(i, j);
    }
  }

  cout << n * m - k - res << endl;
  return 0;
}
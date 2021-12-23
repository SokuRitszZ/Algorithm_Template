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

const int N = 2010, M = 1000010;

int n, m;
int h[N], e[M], ne[M], w[M], idx;
int q[N], d[N];
int dist[N];
bool st[N];

void add(int a, int b, int c)
{
  e[ ++ idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx;
  ++ d[b];
}

void topsort()
{
  int hh = 0, tt = -1;

  for (int i = 1; i <= n + m; ++ i)
  {
    if (!d[i]) q[ ++ tt] = i;
  }

  while (hh <= tt)
  {
    int u = q[hh ++ ];

    for (int i = h[u]; i; i = ne[i])
    {
      int v = e[i];
      if ( -- d[v] == 0) q[ ++ tt] = v;
    }
  }
}

signed main()
{ 
  cin.tie(0)->sync_with_stdio(false); 
  cin >> n >> m;
  for (int i = 1; i <= m; ++ i)
  {
    memset(st, 0, sizeof st);
    int cnt; cin >> cnt;
    int start = n, end = 1;
    while (cnt -- )
    {
      int ver; cin >> ver;
      st[ver] = 1;
      start = min(ver, start);
      end = max(ver, end);
    }

    int ver = i + n;
    for (int i = start; i <= end; ++ i)
    {
      if (!st[i]) add(i, ver, 0);
      else add(ver, i, 1);
    }
  }

  topsort();

  for (int i = 1; i <= n; ++ i) dist[i] = 1;

  for (int i = 0; i < n + m; ++ i)
  {
    int u = q[i];
    for (int j = h[u]; j; j = ne[j])
    {
      int v = e[j];
      dist[v] = max(dist[v], dist[u] + w[j]);
    }
  }

  int res = 0;

  for (int i = 1; i <= n; ++ i)
    res = max(res, dist[i]);

  cout << res << endl;
  return 0;
}
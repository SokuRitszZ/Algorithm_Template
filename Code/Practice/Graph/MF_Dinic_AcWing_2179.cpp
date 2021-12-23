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

const int N = 430 + 10, M = (150 * 270 + N) * 2, INF = 1e8;

int n, m, S, T;
int h[N], e[M], f[M], ne[M], idx;
int q[N], d[N], cur[N];

void add(int a, int b, int c)
{
  e[idx] = b, f[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
  e[idx] = a, f[idx] = 0, ne[idx] = h[b], h[b] = idx ++ ;
}

bool bfs()
{
  int hh = 0, tt = 0;
  memset(d, -1, sizeof d);
  q[0] = S, d[S] = 0, cur[S] = h[S];
  while (hh <= tt)
  {
    int u = q[hh ++ ];
    for (int i = h[u]; ~i; i = ne[i])
    {
      int v = e[i];
      if (d[v] == -1 && f[i])
      {
        d[v] = d[u] + 1;
        cur[v] = h[v];
        if (v == T) return 1;
        q[ ++ tt] = v;
      }
    }
  }  

  return 0;
}

int find(int u, int limit)
{
  if (u == T) return limit;
  int flow = 0;
  for (int i = cur[u]; ~i && flow < limit; i = ne[i])
  {
    cur[u] = i;
    int v = e[i];
    if (d[v] == d[u] + 1 && f[i])
    {
      int t = find(v, min(f[i], limit - flow));
      if (!t) d[v] = -1;
      f[i] -= t, f[i ^ 1] += t, flow += t;
    }
  }

  return flow;
}

int dinic()
{
  int r = 0, flow;
  while (bfs())
    while (flow = find(S, INF)) 
      r += flow;
  return r;
}

signed main()
{ 
  cin.tie(0)->sync_with_stdio(false); 
  cin >> m >> n;
  S = 0, T = n + m + 1;

  memset(h, -1, sizeof h);

  int tot = 0;
  for (int i = 1; i <= m; ++ i)
  {
    int c; cin >> c;
    add(S, i, c);    
    tot += c;
  }

  for (int i = 1; i <= n; ++ i)
  {
    int c; cin >> c;
    add(i + m, T, c);
  }

  for (int i = 1; i <= m; ++ i)
    for (int j = 1; j <= n; ++ j)
      add(i, m + j, 1);

  if (dinic() != tot) cout << 0 << endl;
  else
  {
    cout << 1 << endl;
    for (int i = 1; i <= m; ++ i)
    {
      for (int j = h[i]; ~j; j = ne[j])
      {
        int v = e[j];
        if (v > m && v <= n + m && !f[j])
          cout << e[j] - m << ' ';
      }
      cout << endl;
    }
  }
  return 0;
}
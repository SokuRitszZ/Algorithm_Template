#include <iostream>
#include <cstring>

#define CT const 
#define IL inline
#define endl '\n'
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define pb push_back
#define eb emplace_back
#define MULTICASE() int sokuritszz, kase; for (std::cin >> sokuritszz, kase = 0; kase ++ , sokuritszz --;)

typedef long long i6;
typedef std::pair<int, int> pii;

const int N = 510, M = (3010 + N * 2) * 2, INF = 1e8;

struct Edge
{
  int a, b;
}edges[M];

int n, m, k;
int S, T;
int h[N], e[M], ne[M], f[M], idx;
int p[N];

void add(int a, int b, int c, int d)
{
  e[idx] = b, ne[idx] = h[a], f[idx] = c, h[a] = idx ++ ;
  e[idx] = a, ne[idx] = h[b], f[idx] = d, h[b] = idx ++ ;
}
  
void build(int x)
{
  memset(h, -1, sizeof h); idx = 0;
  for (int i = 0; i < m; ++ i)
  {
    auto [a, b] = edges[i];
    add(a, b, 1, 1);
  } 

  for (int i = 1; i <= n; ++ i)
    if (p[i] != -1)
    {
      if (p[i] >> x & 1) add(S, i, INF, 0);
      else add(i, T, INF, 0);
    }
}

int d[N], q[N], cur[N];

bool bfs()
{
  memset(d, -1, sizeof d);
  q[0] = S, d[S] = 0, cur[S] = h[S];
  int hh = 0, tt = 0;
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
    int v = e[i];
    cur[u] = i;
    if (d[v] == d[u] + 1 && f[i])
    {
      int t = find(v, std::min(f[i], limit - flow));
      if (!t) d[v] = -1;
      f[i] -= t, f[i ^ 1] += t, flow += t;
    }
  }
  return flow;
}

i6 max_flow(int x)
{
  build(x);
  int r = 0, flow;
  while (bfs())
    while (flow = find(S, INF))
      r += flow;
  return r;
}

signed main()
{
  std::cin.tie(0)->sync_with_stdio(false);
  std::cin >> n >> m;

  S = 0, T = n + 1;

  for (int i = 0; i < m; ++ i) std::cin >> edges[i].a >> edges[i].b;
  std::cin >> k;
  memset(p, -1, sizeof p);
  while (k -- )
  {
    int a, b; std::cin >> a >> b;
    p[a] = b;
  }

  i6 res = 0;
  for (int i = 0; i < 31; ++ i) res += max_flow(i) << i;

  std::cout << res << endl;

  return 0;
}


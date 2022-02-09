#include <iostream>
#include <cstring>

#define CT const 
#define IL inline
#define endl '\n'
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define pb push_back
#define eb emplace_back
#define MULTICASE() int sokuritszz, kase; for (cin >> sokuritszz, kase = 0; kase ++ , sokuritszz --;)

using namespace std;

typedef long long i6;
typedef pair<int, int> pii;

const int N = 1010 << 1, M = N * N << 1, INF = 1e8;

int h[N], e[M], ne[M], f[M], idx;

void add(int a, int b, int c)
{
  e[idx] = b, ne[idx] = h[a], f[idx] = c, h[a] = idx ++ ;
  e[idx] = a, ne[idx] = h[b], f[idx] = 0, h[b] = idx ++ ;
}

int m, n, S, T;
int w[N], belong[N];
int d[N], q[N], cur[N];

bool bfs()
{
  memset(d, -1, sizeof d);
  d[S] = 0, q[0] = S, cur[S] = h[S];
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
      int t = find(v, min(f[i], limit - flow));
      if (!t) d[v] = -1;
      f[i] -= t, f[i ^ 1] += t, flow += t;
    }
  }

  return flow;
}

int max_flow()
{
  int res = 0, flow;
  while (bfs())
    while (flow = find(S, INF))
      res += flow;
  return res;
}

signed main()
{ 
  cin.tie(0)->sync_with_stdio(false); 
  cin >> m >> n;
  S = 0, T = n + 1;
  memset(h, -1, sizeof h);
  for (int i = 1; i <= m; ++ i) cin >> w[i];
  for (int i = 1; i <= n; ++ i)
  {
    int a, b; cin >> a;
    while (a -- )
    {
      int x; cin >> x;
      if (!belong[x]) add(S, i, w[x]);
      else add(belong[x], i, INF);
      belong[x] = i;
    }
    cin >> b;
    add(i, T, b);
  }

  cout << max_flow() << endl;
  return 0;
}
#include <iostream>
#include <cstring>

#define CT const 
#define IL inline
#define endl '\n'
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegia(), x.rend()
#define pb push_back
#define eb emplace_back
#define MULTICASE() int sokuritszz, kase; for (cin >> sokuritszz, kase = 0; kase ++ , sokuritszz --;)

using namespace std;

typedef long long i6;
typedef pair<int, int> pii;

const int N = 210, M = 80010, INF = 1e8;

int n, m, S, T, K;
int h[N], e[M], ne[M], f[M], w[M], idx;
int q[N], d[N], cur[N];

void add(int a, int b, int c)
{
  e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx ++ ;
  e[idx] = a, ne[idx] = h[b], w[idx] = c, h[b] = idx ++ ;
}

bool bfs()
{
  memset(d, -1, sizeof d);
  int hh = 0, tt = 0;
  d[q[0] = S] = 0, cur[S] = h[S];
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

int dinic()
{
  int r = 0, flow;

  while (bfs()) while (flow = find(S, INF)) r += flow;

  return r;
}

bool check(int mid)
{
  for (int i = 0; i < idx; ++ i)
    if (w[i] > mid) f[i] = 0;
    else f[i] = 1;

  int res = dinic();
  return res >= K;
}

signed main()
{ 
  cin.tie(0)->sync_with_stdio(false); 
  cin >> n >> m >> K;
  S = 1, T = n;
  memset(h, -1, sizeof h);

  while (m -- )
  {
    int a, b, c; cin >> a >> b >> c;
    add(a, b, c);
  }

  // for (int i = 1; i <= n; ++ i)
  // {
  //   cout << i << ':';
  //   for (int j = h[i]; ~j; j = ne[j])
  //     cout << ' ' << e[j];
  //   cout << endl;
  // }
  
  int l = 1, r = 1e6;
  while (l < r)
  {
    int mid = l + r >> 1;
    if (check(mid)) r = mid;
    else l = mid + 1;
  }

  cout << r << endl;

  return 0;
}
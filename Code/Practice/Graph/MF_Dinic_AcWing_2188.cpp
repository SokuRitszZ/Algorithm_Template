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

const int N = 210, M = (10200 + N) * 2, INF = 1e8;

int h[N], e[M], ne[M], f[M], l[M], idx;
int q[N], d[N], cur[N], A[N];
int n, m, S, T;

void add(int a, int b, int c, int d)
{
  e[idx] = b, ne[idx] = h[a], f[idx] = d - c, l[idx] = c, h[a] = idx ++ ;
  e[idx] = a, ne[idx] = h[b], f[idx] = 0, h[b] = idx ++ ;
}

bool bfs()
{
  memset(d, -1, sizeof d);
  int hh = 0, tt = 0;
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
  cin >> n >> m;
  memset(h, -1, sizeof h);
  S = 0, T = n + 1;
  for (int i = 0; i < m; ++ i)
  {
    int a, b, c, d; cin >> a >> b >> c >> d;
    add(a, b, c, d);
    A[a] -= c, A[b] += c;
  }

  int tot = 0;
  for (int i = 1; i <= n; ++ i)
    if (A[i] > 0) add(S, i, 0, A[i]), tot += A[i];
    else if (A[i] < 0) add(i, T, 0, -A[i]);

  if (dinic() != tot) cout << "NO\n";
  else
  {
    cout << "YES\n";
    for (int i = 0; i < m * 2; i += 2)
      cout << f[i ^ 1] + l[i] << endl;
  }
  return 0;
}
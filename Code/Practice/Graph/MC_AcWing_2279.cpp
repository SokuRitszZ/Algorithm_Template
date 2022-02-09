#include <iostream>
#include <iomanip>
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

const int N = 110, M = 410 << 1, INF = 1e8;
const double eps = 1e-8;

int h[N], e[M], ne[M], idx;
double f[M], w[M];

void add(int a, int b, int c)
{
  e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx ++ ;
  e[idx] = a, ne[idx] = h[b], w[idx] = c, h[b] = idx ++ ;
}

int n, m, S, T;
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
      if (d[v] == -1 && f[i] > 0)
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

double find(int u, double limit)
{
  if (u == T) return limit;

  double flow = 0;
  for (int i = cur[u]; ~i && flow < limit; i = ne[i])
  {
    int v = e[i];
    cur[u] = i;
    if (d[v] == d[u] + 1 && f[i] > 0)
    {
      double t = find(v, min(f[i], limit - flow));
      if (t < eps) d[v] = -1;
      f[i] -= t, f[i ^ 1] += t, flow += t;
    }
  }

  return flow;
}

double max_flow(double mid)
{
  double res = 0;
  for (int i = 0; i < m * 2; i += 2)
    if (w[i] <= mid)
    {
      res += w[i] - mid;
      f[i] = f[i ^ 1] = 0;
    }
    else
      f[i] = f[i ^ 1] = w[i] - mid;

  double r = 0, flow;
  while (bfs())
    while (flow = find(S, INF))
      r += flow;

  return r + res;
}

signed main()
{ 
  cin.tie(0)->sync_with_stdio(false); 
  cin >> n >> m >> S >> T;

  memset(h, -1, sizeof h);
  for (int i = 0; i < m; ++ i)
  {
    int a, b, c; cin >> a >> b >> c;
    add(a, b, c);
  }

  double l = 0, r = 1e7;
  while (r - l > eps)
  {
    double mid = (l + r) / 2;
    if (max_flow(mid) < 0) r = mid;
    else l = mid;
  }

  cout << ios::fixed << setprecision(2) << r;
  return 0;
}
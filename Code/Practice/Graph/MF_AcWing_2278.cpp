#include <iostream>
#include <cmath>
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

const int N = 110 << 1, M = N * N << 1, INF = 1e8;
const double eps = 1e-8;

int h[N], e[M], ne[M], f[M], idx;

void add(int a, int b, int c)
{
  e[idx] = b, ne[idx] = h[a], f[idx] = c, h[a] = idx ++ ;
  e[idx] = a, ne[idx] = h[b], f[idx] = 0, h[b] = idx ++ ;
}

int n, S, T;
double dist;

pii pos[N];

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

bool check(pii a, pii b)
{
  int dx = a.first - b.first, dy = a.second - b.second;
  return dx * dx + dy * dy < dist * dist + eps;
}

signed main()
{ 
  cin.tie(0)->sync_with_stdio(false); 
  MULTICASE()
  {
    cin >> n >> dist;
    S = 0;

    memset(h, -1, sizeof h); idx = 0;
    int tot = 0;
    for (int i = 1; i <= n; ++ i)
    {
      int pencnt, maxjump;
      cin >> pos[i].first >> pos[i].second >> pencnt >> maxjump;
      add(i, i + n, maxjump);
      add(S, i, pencnt);
      tot += pencnt;
    }

    for (int i = 1; i <= n; ++ i)
      for (int j = 1; j < i; ++ j)
      {
        if (check(pos[i], pos[j]))
        {
          add(n + i, j, INF);
          add(n + j, i, INF);
        }
      }

    bool flg = 0;
    for (int i = 1; i <= n; ++ i)
    {
      T = i;
      for (int j = 0; j < idx; j += 2)
      {
        f[j] += f[j ^ 1]; // 流量回收
        f[j ^ 1] = 0;
      }
      if (max_flow() == tot)
      {
        cout << i - 1 << ' ';
        flg = 1;
      }
    }
    if (!flg) cout << -1 << endl;
    else cout << endl;
  }
  return 0;
}
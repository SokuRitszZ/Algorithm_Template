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

const int N = 210, M = N + 10010 << 1, INF = 1e8 + 10;

int h[N], e[M], ne[M], f[M], idx;
int q[N], d[N], cur[N], A[N];
int n, m, S, T;

void add(int a, int b, int c)
{
  e[idx] = b, ne[idx] = h[a], f[idx] = c, h[a] = idx ++ ;
  e[idx] = a, ne[idx] = h[b], f[idx] = 0, h[b] = idx ++ ;
}

bool bfs()
{
  memset(d, -1, sizeof d);
  d[q[0] = S] = 0, cur[S] = h[S];

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
  int s, t;
  cin >> n >> m >> s >> t;
  S = 0, T = n + 1;

  memset(h, -1, sizeof h);

  while (m -- )
  {
    int a, b, c, d; cin >> a >> b >> c >> d;
    add(a, b, d - c);
    A[a] -= c, A[b] += c;
  }

  int tot = 0;
  for (int i = 1; i <= n; ++ i)
    if (A[i] > 0) add(S, i, A[i]), tot += A[i];
    else if (A[i] < 0) add(i, T, -A[i]);

  add(t, s, INF); // 保留原流网络的最大流，就加一个无限大的反向流

  if (dinic() < tot) cout << "No Solution\n"; // 先求新残留网络的最大流
  else
  {
    int res = f[idx - 1]; // 拿出当前的最大流
    f[idx - 1] = f[idx - 2] = 0; // 删掉加的反边
    S = s, T = t; // 求原流网络的最大流
    cout << dinic() + res << endl; // 答案
  }
  return 0;
}
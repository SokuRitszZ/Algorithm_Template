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

const int N = 510, M = 5010 << 1, INF = 1e8;

int n, m, S, T;
int h[N], e[M], ne[M], f[M], idx;
int q[N], d[N], cur[N];
bool vis_s[N], vis_t[N];

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
    cur[u] = i;
    int v = e[i];
    if (d[v] == d[u] + 1 && f[i])
    {
      int t = find(v, min(limit - flow, f[i]));
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

void dfs(int u, bool st[], int t)
{
  st[u] = 1;
  for (int i = h[u]; ~i; i = ne[i])
  {
    int j = i ^ t, v = e[i];
    if (f[j] && !st[v])
      dfs(v, st, t);
  }
}

signed main()
{ 
  cin.tie(0)->sync_with_stdio(false); 
  cin >> n >> m;
  S = 0, T = n - 1;
  memset(h, -1, sizeof h);
  for (int i = 0; i < m; ++ i)
  {
    int a, b, c; cin >> a >> b >> c;
    add(a, b, c);
  }

  dinic();
  dfs(S, vis_s, 0);
  dfs(T, vis_t, 1);

  int res = 0;
  for (int i = 0; i < m * 2; i += 2)
    if (!f[i] && vis_s[e[i ^ 1]] && vis_t[e[i]])
      ++ res;
  cout << res << endl;
  return 0;
}
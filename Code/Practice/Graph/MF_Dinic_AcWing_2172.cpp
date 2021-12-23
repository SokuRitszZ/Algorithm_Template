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

template<int N, int M> struct Dinic
{
  const static int INF = 1e8 + 10;

  int S, T;
  int h[N], e[M], f[M], ne[M], idx;
  int q[N], d[N], cur[N];

  Dinic(int S, int T): S(S), T(T), idx(0)
  {
    memset(h, -1, sizeof h);
  }

  void add_edge(int a, int b, int c)
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
        if (d[v] == -1 && f[i]) // 增广路的必要条件：容量 > 0
        {
          d[v] = d[u] + 1;
          cur[v] = h[v];
          if (v == T) return 1; // 有增广路
          q[ ++ tt] = v;
        } 
      }
    }    

    return 0;
  }

  int find(int u, int limit) // 暴力搜能跑limit流的最大的流量
  {
    if (u == T) return limit;
    int flow = 0;
    for (int i = cur[u]; ~i && flow < limit; i = ne[i]) // 从当前未满的边开始枚举
    {
      cur[u] = i; // 当前弧优化
      int v = e[i];
      if (d[v] == d[u] + 1 && f[i]) // 按照分层图来搜
      {
        int t = find(v, min(f[i], limit - flow));
        if (!t) d[v] = -1; // 不存在增广路径，删点
        f[i] -= t, f[i ^ 1] += t, flow += t; // 更新残留网络
      }
    } 

    return flow;
  }

  int max_flow()
  {
    int r = 0, flow;
    while (bfs())
      while (flow = find(S, INF))
        r += flow;

    return r;
  }
};

signed main()
{ 
  cin.tie(0)->sync_with_stdio(false); 

  int n, m, S, T; cin >> n >> m >> S >> T;

  Dinic<10010, 200010> dinic(S, T);

  while (m -- )
  {
    int a, b, c; cin >> a >> b >> c;
    dinic.add_edge(a, b, c);
  }
  cout << dinic.max_flow();
  return 0;
}
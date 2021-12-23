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

template<int N, int M> struct EK
{
  const int INF = 1e8 + 10;

  int h[N], e[M << 1], f[M << 1], ne[M << 1], idx; 
  int d[N], pre[N], q[N];
  int S, T;
  bool st[N];

  EK(int S, int T): S(S), T(T)
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
    memset(st, 0, sizeof st);
    int hh = 0, tt = 0;
    d[S] = INF, q[0] = S, st[S] = 1;

    while (hh <= tt)
    {
      int u = q[hh ++ ];
      for (int i = h[u]; ~i; i = ne[i])
      {
        int v = e[i];
        if (!st[v] && f[i])
        {
          pre[v] = i;
          d[v] = min(d[u], f[i]);
          st[v] = 1;
          if (v == T) return 1;
          q[ ++ tt] = v;
        }
      }
    }

    return 0;
  }

  int max_flow()
  {
    int r = 0;
    while (bfs())
    {
      r += d[T];
      for (int i = T; i != S; i = e[pre[i] ^ 1])
        f[pre[i]] -= d[T], f[pre[i] ^ 1] += d[T];
    }

    return r;
  }
};

signed main()
{ 
  cin.tie(0)->sync_with_stdio(false); 
  int n, m, s, t; cin >> n >> m >> s >> t;
  EK<1010, 20010> ek(s, t);
  while (m -- )
  {
    int a, b, c; cin >> a >> b >> c;
    ek.add_edge(a, b, c);
  }

  cout << ek.max_flow() << endl;

  return 0;
}
#include <iostream>
#include <queue>
#include <vector>
#include <cstring>

#define CT const 
#define IL inline
#define endl '\n'
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegia(), x.rend()
#define MULTICASE() int sokuritszz, kase; for (cin >> sokuritszz, kase = 0; kase ++ , sokuritszz --;)

using namespace std;

typedef long long i6;

const int N = 110, M = N * N;

int h[N], e[M], ne[M], w[M], idx;

void add(int a, int b, int ww)
{
  e[ ++ idx] = b, w[idx] = ww, ne[idx] = h[a], h[a] = idx;
}

int n, m;
int p[N], l[N];
int d[N];

struct Node
{
  int u;
  int w, mxl, mnl;
  bool operator > (const Node& rhs) const
  {
    return w > rhs.w;
  }
};

int bfs(int u)
{
  memset(d, 0x3f, sizeof d);
  d[u] = p[u];
  d[1] = 10000;

  priority_queue<Node, vector<Node>, greater<Node> > q;

  q.push({u, d[u], l[u], l[u]});

  while (q.size())
  {
    auto [u, dist, mxl, mnl] = q.top(); q.pop();

    for (int i = h[u]; i; i = ne[i])
    {
      int v = e[i];
      if (abs(l[v] - mnl) > m or abs(l[v] - mxl) > m) continue;
      if (d[v] > dist + w[i])
      {
        d[v] = dist + w[i];
        q.push({v, d[v], max(l[v], mxl), min(l[v], mnl)});
      }
    }
  }

  return d[1];
}

signed main()
{ 
  cin.tie(0)->sync_with_stdio(false); 

  cin >> m >> n;

  for (int i = 1; i <= n; ++ i)
  {
    int x;
    cin >> p[i] >> l[i] >> x;
    while (x -- )
    {
      int v, ww; cin >> v >> ww;
      add(v, i, ww);      
    }
  }

  int res = 10000;

  for (int i = 1; i <= n; ++ i)
    res = min(res, bfs(i));

  cout << res << endl; 
  return 0;
}
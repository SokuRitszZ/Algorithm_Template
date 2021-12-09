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

const int N = 1e4 + 10, M = 3e4 + 10;

int n, m;
int h[N], e[M], ne[M], idx;
int dfn[N], low[N], timestp;
int ans, root;

void add(int a, int b)
{
  e[ ++ idx] = b, ne[idx] = h[a], h[a] = idx;
}

void tarjan(int u)
{
  dfn[u] = low[u] = ++ timestp;
  int cnt = 0;

  for (int i = h[u]; i; i = ne[i])
  {
    int v = e[i];
    if (!dfn[v])
    {
      tarjan(v);
      low[u] = min(low[u], low[v]);
      if (dfn[u] <= low[v]) ++ cnt;
    }
    else low[u] = min(low[u], dfn[v]);
  }

  if (u != root) ++ cnt;
  ans = max(ans, cnt);
}

signed main()
{ 
  while (scanf("%d %d", &n, &m), n or m)
  {
    memset(h, 0, sizeof h); idx = 0;
    memset(dfn, 0, sizeof dfn); timestp = 0;
    while (m -- )
    {
      int a, b; scanf("%d %d", &a, &b);
      add(a, b), add(b, a);
    }

    ans = 0;
    int cnt = 0;
    for (root = 0; root < n; ++ root)
      if (!dfn[root]) tarjan(root), ++ cnt;

    printf("%d\n", ans + cnt - 1);
  }
  return 0;
}
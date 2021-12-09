#include <iostream>
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
typedef unsigned long long ui6;

const int N = 1010, M = 1010;

int n, m;
int h[N], e[M], ne[M], idx;

void add(int a, int b)
{
  e[ ++ idx] = b, ne[idx] = h[a], h[a] = idx;
}
int dfn[N], low[N], timestp;
int stk[N], top;
int dcc_cnt;
vector<int> dcc[N];
bool cut[N];
int root;

void tarjan(int u)
{
  dfn[u] = low[u] = ++ timestp;
  stk[ ++ top] = u;

  if (u == root and !h[u])
  {
    ++ dcc_cnt;
    dcc[dcc_cnt].push_back(u);
    return ;
  }

  int cnt = 0;
  for (int i = h[u]; i; i = ne[i])
  {
    int v = e[i];
    if (!dfn[v])
    {
      tarjan(v);
      low[u] = min(low[u], low[v]);
      if (dfn[u] <= low[v])
      {
        ++ cnt;
        if (u != root or cnt > 1) cut[u] = 1;
        ++ dcc_cnt;
        int y;
        do
        {
          y = stk[top -- ];
          dcc[dcc_cnt].push_back(y);
        }while (y != v);
        dcc[dcc_cnt].push_back(u);
      }
    }
    else low[u] = min(low[u], dfn[v]);
  }
}

signed main()
{ 
  cin.tie(0)->sync_with_stdio(false); 
  int kase = 0;

  while (cin >> m, m)
  {
    for (int i = 1; i <= dcc_cnt; ++ i) dcc[i].clear();

    n = top = 0;
    memset(h, 0, sizeof h); idx = 0;
    memset(dfn, 0, sizeof dfn); timestp = 0;
    memset(cut, 0, sizeof cut); dcc_cnt = 0; 

    while (m -- )
    {
      int a, b; cin >> a >> b;
      n = max(n, max(a, b));
      add(a, b), add(b, a);
    }

    for (root = 1; root <= n; ++ root)
    {
      if (!dfn[root]) tarjan(root);
    } 

    int res = 0;
    ui6 num = 1;
    for (int i = 1; i <= dcc_cnt; ++ i)
    {
      int cnt = 0;
      for (int j = 0; j < dcc[i].size(); ++ j)
      {
        if (cut[dcc[i][j]]) ++ cnt;
      }  
      if (cnt == 0)
      {
        if (dcc[i].size() > 1) res += 2, num *= dcc[i].size() * (dcc[i].size() - 1) / 2;
        else ++ res;
      }
      else if (cnt == 1) ++ res, num *= dcc[i].size() - 1;
    }

    cout << "Case " << ++ kase << ": " << res << ' ' << num << endl;
  }
  return 0;
}
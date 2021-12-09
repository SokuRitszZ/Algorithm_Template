#include <iostream>
#include <cstring>
#include <algorithm>

#define CT const 
#define IL inline
#define endl '\n'
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegia(), x.rend()
#define MULTICASE() int sokuritszz, kase; for (cin >> sokuritszz, kase = 0; kase ++ , sokuritszz --;)

using namespace std;

typedef long long i6;

const int N = 5010, M = 2e4 + 10;

int n, m;
int h[N], e[M], ne[M], idx;
int dfn[N], low[N], timestp;
int d[N];
int stk[N], top;
int id[N], dcc_cnt;
bool is_bridge[M];

void add(int a, int b)
{
  e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

void tarjan(int u, int from)
{
  dfn[u] = low[u] = ++ timestp;
  stk[ ++ top] = u;

  for (int i = h[u]; i; i = ne[i])
  {
    int v = e[i];
    if (!dfn[v])
    {
      tarjan(v, u);
      low[u] = min(low[u], low[v]);
      if (dfn[u] < low[v])
        is_bridge[i] = is_bridge[i ^ 1] = 1;
    }
    else if (i != (from ^ 1))
      low[u] = min(low[u], dfn[v]);
  }

  if (dfn[u] == low[u])
  {
    ++ dcc_cnt;
    int y;
    do
    {
      y = stk[top -- ];
      id[y] = dcc_cnt;
    }while (y != u);
  }
}

signed main()
{ 
  cin.tie(0)->sync_with_stdio(false); 

  cin >> n >> m;
 
  memset(h, -1, sizeof h);

  while (m -- )
  {
    int a, b; cin >> a >> b;
    add(a, b), add(b, a);
  }  

  tarjan(1, -1);

  for (int i = 0; i < idx; ++ i)
  {
    if (is_bridge[i])
      ++ d[id[e[i]]];
  }

  int cnt = 0;
  for (int i = 1; i <= dcc_cnt; ++ i)
  {
    if (d[i] == 1) ++ cnt;
  }

  cout << (cnt + 1 >> 1) << endl;
  return 0;
}
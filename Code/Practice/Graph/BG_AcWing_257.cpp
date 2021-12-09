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

const int N = 20010, M = 200010;

int n, m;
int h[N], e[M], ne[M], w[M], idx;
int color[N];

void add(int a, int b, int c)
{
  e[ ++ idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx;
}

bool dfs(int u, int c, int mid)
{
  color[u] = c;
  for (int i = h[u]; i; i = ne[i])
  {
    int v = e[i];
    if (w[i] <= mid) continue;
    if (color[v])
    {
      if (color[v] == c) return 0;
    }
    else if (!dfs(v, 3 - c, mid)) return 0;
  }

  return 1;
}

bool check(int mid)
{
  memset(color, 0, sizeof color);
  for (int i = 1; i <= n; ++ i)
    if (color[i] == 0)
      if (!dfs(i, 1, mid)) return 0; 
  return 1;
}

signed main()
{ 
  cin.tie(0)->sync_with_stdio(false); 
  cin >> n >> m;
  while (m -- )
  {
    int a, b, c; cin >> a >> b >> c;
    add(a, b, c), add(b, a, c);
  }

  int l = 0, r = 1e9;
  while (l < r)
  {
    int mid = l + r >> 1;
    if (check(mid)) r = mid;
    else l = mid + 1;
  }

  cout << r << endl;
  return 0;
}
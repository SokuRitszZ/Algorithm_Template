#include <iostream>
#include <algorithm>
#include <cstring>

#define all(x) x.begin(), x.end()
#define MULTICASE() int sokuritszz, kase; for (std::cin >> sokuritszz, kase = 0; kase ++ , sokuritszz --;)

typedef long long i6;
struct pii {int x, y; pii(int x = 0, int y = 0): x(x), y(y){}};
bool operator < (const pii &a, const pii &b){return a.x == b.x ? a.y < b.y : a.x < b.x;}

const int N = 10010, M = N << 1;

int n, m; 
int h[N], e[M], ne[M], w[M], idx;
bool st[N];

void add(int a, int b, int c)
{
  e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx ++ ;
}

int get_wc(int u, int fa, int tot, int &wc)
{
  if (st[u]) return 0;
  
  int res = 1, ms = 0;
  for (int i = h[u]; ~i; i = ne[i])
  {
    int v = e[i];
    if (v == fa) continue;
    int t = get_wc(v, u, tot, wc);
    ms = std::max(ms, t);
    res += t;
  }
  ms = std::max(ms, tot - res);
  if (ms <= tot / 2) wc = u; 
  return res;
}

int get_size(int u, int fa)
{
  if (st[u]) return 0;
  int res = 1;
  for (int i = h[u]; ~i; i = ne[i])
    if (e[i] != fa) res += get_size(e[i], u);
  return res;
}

int p[N], q[N];

int get(int a[], int cnt)
{
  std::sort(a, a + cnt);

  int res = 0;
  for (int i = 0; i < cnt - 1; ++ i)
    res += std::upper_bound(a + i + 1, a + cnt, m - a[i]) - (a + i + 1);

  return res;
}

void get_dist(int u, int fa, int dist, int &qt)
{
  if (st[u]) return ;
  q[qt ++ ] = dist;
  for (int i = h[u]; ~i; i = ne[i])
    if (e[i] != fa)
      get_dist(e[i], u, dist + w[i], qt);
}

int calc(int u)
{
  if (st[u]) return 0;

  int res = 0;
  get_wc(u, -1, get_size(u, -1), u);

  st[u] = 1;

  int pt = 0;
  for (int i = h[u]; ~i; i = ne[i])
  {
    int v = e[i], qt = 0;
    get_dist(v, -1, w[i], qt);
    res -= get(q, qt);
    for (int j = 0; j < qt; ++ j)
    {
      if (q[j] <= m) ++ res;
      p[pt ++ ] = q[j];
    }
  }
  res += get(p, pt);

  for (int i = h[u]; ~i; i = ne[i])
    res += calc(e[i]);

  return res;
}

signed main()
{
  std::cin.tie(0)->sync_with_stdio(false);
  while (std::cin >> n >> m, n || m)
  {
    memset(h, -1, sizeof h);
    memset(st, 0, sizeof st);
    idx = 0;

    for (int i = 1; i < n; ++ i)
    {
      int a, b, c; std::cin >> a >> b >> c;
      add(a, b, c), add(b, a, c);
    }

    std::cout << calc(0) << '\n';
  }
  return 0;
}

// Time: Thu Jan 20 13:58:20 2022
// Authorized by: SokuRitszZ
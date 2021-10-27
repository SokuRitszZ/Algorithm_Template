#include <bits/stdc++.h>

#define CT const 
#define IL inline
#define PB emplace_back
#define PP pop
#define FT front
#define endl '\n'
#define MULTICASE() for (int _ = read(), kase = 0; kase ++ , _ --;)

using namespace std;

typedef long long i6;

inline int read(){
  int x = 0, flg = 1; char ch = getchar();
  if (ch == '-')  flg = -1;
  while (ch < '0' or ch > '9') ch = getchar();
  while ('0' <= ch and ch <= '9') x = (x << 3) + (x << 1) + (ch ^ 48), ch = getchar();
  return x * flg;
}

CT int N = 1e5 + 10, M = N;

struct Query{
  int i, l, r, p;
}q[N];

vector<int> nums;
vector<vector<int>> G;
int n, m;
int w[N], d[N], first[N], last[N], grp[N];
int f[N][16];
int ans[M], cnt[N], seq[N], st[N];
int res, top, len;

IL int get(int x){
  return x / len;
}

IL void add_edge(int u, int v){
  G[u].push_back(v);
}

IL void add(int x){
  st[x] ^= 1;
  if (st[x]){
    if (cnt[w[x]] == 0) res ++ ;
    cnt[w[x]] ++ ;
  }else{
    cnt[w[x]] -- ;
    if (cnt[w[x]] == 0) res -- ;
  }
};

void dfs(int u, int fa){
  seq[ ++ top] = u;
  first[u] = top;
  for (int v : G[u]) {
    if (v == fa) continue;
    dfs(v, u);
  }
  seq[ ++ top] = u;
  last[u] = top;
}

int qq[N];

void bfs(){
  memset(d, 0x3f, sizeof d);
  d[0] = 0, d[1] = 1;
  int hh = 0, tt = -1;
  qq[ ++ tt] = 1;
  while (hh <= tt){
    int u = qq[hh ++ ];
    for (int v : G[u])
      if (d[v] > d[u] + 1) {
        d[v] = d[u] + 1;
        f[v][0] = u;
        for (int i = 1; i <= 15; i ++ )
          f[v][i] = f[f[v][i - 1]][i - 1];
        qq[ ++ tt] = v;
      }
  }
}

IL int lca(int a, int b){
  if (d[a] < d[b]) swap(a, b);

  for (int i = 15; i >= 0; i -- )
    if (d[f[a][i]] >= d[b]) 
      a = f[a][i];

  if (a == b) return a;

  for (int i = 15; i >= 0; i -- )
    if (f[a][i] != f[b][i]) 
      a = f[a][i], b = f[b][i];

  return f[a][0];
}

signed main(){
  // ----
  n = read(), m = read();
  G.resize(n + 1);

  for (int i = 1; i <= n; i ++ ) nums.push_back(w[i] = read());

  sort(nums.begin(), nums.end());
  nums.erase(unique(nums.begin(), nums.end()), nums.end());

  for (int i = 1; i <= n; i ++ ) w[i] = lower_bound(nums.begin(), nums.end(), w[i]) - nums.begin();

  for (int i = 1; i < n; i ++ ){
    int a = read(), b = read();
    add_edge(a, b), add_edge(b, a);
  }

  dfs(1, 0);
  bfs();
  for (int i = 0; i < m; i ++ ){
    int a = read(), b = read();
    if (first[a] > first[b]) swap(a, b);
    int p = lca(a, b);
    if (p == a) q[i] = {i, first[a], first[b]};
    else q[i] = {i, last[a], first[b], p};
  }

  len = sqrt(top);

  sort(q, q + m, [&](Query a, Query b){
    int ll = get(a.l), rr = get(b.l);
    if (ll != rr) return ll < rr;
    return a.r < b.r;
  });
  
  int L = 1, R = 0;
  for (int i = 0; i < m; i ++ ){
    auto [id, l, r, p] = q[i];
    while (R > r) add(seq[R -- ]);
    while (R < r) add(seq[ ++ R]);
    while (L < l) add(seq[L ++ ]);
    while (L > l) add(seq[ -- L]);
    if (p) add(p);
    ans[id] = res;
    if (p) add(p);
  }

  for (int i = 0; i < m; i ++ ) cout << ans[i] << endl;
  // ---- 
  return 0;
}
#include <bits/stdc++.h>

using namespace std;
using cint = const int &;

cint &N = 2010, &M = 1010;

inline int read(){
  int x = 0, flg = 1; char ch = getchar();
  if (ch == '-')  flg = -1;
  while (ch < '0' or ch > '9') ch = getchar();
  while ('0' <= ch and ch <= '9') x = (x << 3) + (x << 1) + (ch ^ 48), ch = getchar();
  return x * flg;
}

struct item{
  int v, w; 
};

int f[N][M], g[N][M];
vector<item> items[N];

signed main(){
#ifdef LOCAL
  freopen("in.in", "r", stdin);
  freopen("out.out", "w", stdout);
#endif 
// ----
  int n = read();
  for (int i = 1; i <= n; i ++ ){
    int v = read(), w = read(), s = read();
    int t = 1;
    while (s){
      int vv = t * v, ww = t * w;
      items[i].push_back({vv, ww});
      s -= t;
      t = min(t << 1, s); 
    }
  }

  for (int i = 1; i <= n; i ++ ){
    for (int j = 0; j < M; j ++ ) f[i][j] = f[i - 1][j];
    for (auto [v, w] : items[i]){
      for (int j = 1e3; j >= v; j -- )
        f[i][j] = max(f[i][j], f[i][j - v] + w);
    }
  }

  for (int i = n; i; i -- ){
    for (int j = 0; j < M; j ++ ) g[i][j] = g[i + 1][j];
    for (auto [v, w] : items[i]){
      for (int j = 1e3; j >= v; j -- )
        g[i][j] = max(g[i][j], g[i][j - v] + w);
    }
  }

  int m = read();
  while (m -- ){
    int id = read() + 1, v = read();
    int ans = 0;
    for (int i = 0; i <= v; i ++ )
      ans = max(ans, f[id - 1][i] + g[id + 1][v - i]);
    printf("%d\n", ans);
  }

// ---- 
  return 0;
}
#include <bits/stdc++.h>

using namespace std;
using cint = const int &;

cint K = 60, M = 5010, N = 210;

int f[M][K], now[K];

signed main(){
#ifdef LOCAL
  freopen("in.in", "r", stdin);
  freopen("out.out", "w", stdout);
#endif 
// ----
  int k, m, n; scanf("%d %d %d", &k, &m, &n);
  memset(f, -0x3f, sizeof f);
  f[0][1] = 0;
  for (int i = 1; i <= n; i ++ ){
    int v, w; scanf("%d %d", &v, &w);
    for (int j = m; j >= v; j -- ){
      int c1 = 1, c2 = 1, cnt = 0;
      while (cnt <= k){
        if (f[j][c1] > f[j - v][c2] + w) now[ ++ cnt] = f[j][c1 ++ ];
        else now[ ++ cnt] = f[j - v][c2 ++ ] + w;
      }
      for (int u = 1; u <= k; u ++ )
        f[j][u] = now[u];
    }
  }

  int ans = 0;
  for (int i = 1; i <= k; i ++ ) ans += f[m][i];

  printf("%d", ans);
  
// ---- 
  return 0;
}
#include <bits/stdc++.h>

#define int long long 

using namespace std;
using cint = const int;

cint &N = 1e5 + 10, &M = N;

struct item{
  int a, b, c;
  int value(cint x) const{
    return a * x * x + b * x + c;
  }
};

int f[2][M], q[M], ff[M];
item items[6];
int n, m, c;

signed main(){
#ifdef LOCAL
  freopen("in.in", "r", stdin);
  freopen("out.out", "w", stdout);
#endif 
// ----
  scanf("%lld %lld %lld", &n, &m, &c);
  for (int i = 1; i <= n; i ++ ){
    int v, w, s; scanf("%lld %lld %lld", &v, &w, &s);
    for (int j = 0; j < v; j ++ ){
      int hh = 0, tt = -1;
      for (int k = 0; k * v + j <= c; k ++ ){
        cint x = f[i - 1 & 1][k * v + j] - k * w;
        if (hh <= tt and k - q[hh] > s) hh ++ ;
        while (hh <= tt and x >= ff[tt]) tt -- ;
        q[ ++ tt] = k, ff[tt] = x;
        f[i & 1][k * v + j] = ff[hh] + k * w;
      }
    }
  }  
  
  for (int i = n + 1; i <= n + m; i ++ ){
    scanf("%lld %lld %lld", &items[i - n].a, &items[i - n].b, &items[i - n].c);
    for (int j = c; j >= 0; j -- )
      for (int k = 0; k <= j; k ++ ){
        int vv = k, ww = items[i - n].value(vv);
        f[i & 1][j] = max(f[i & 1][j], f[i - 1 & 1][j - vv] + ww);
      }
  }

  printf("%lld", f[n + m & 1][c]);

// ---- 
  return 0;
}

// v, w, s;
// f[m] = max(f[m], f[m % v] + m / v * w)
// n * c
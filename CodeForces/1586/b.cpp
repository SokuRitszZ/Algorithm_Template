#include <bits/stdc++.h>

#define CT const 
#define MULTICASE() for (int _ = read(); _ --;)

using namespace std;
using i64 = long long;

inline int read(){
  int x = 0, flg = 1; char ch = getchar();
  if (ch == '-')  flg = -1;
  while (ch < '0' or ch > '9') ch = getchar();
  while ('0' <= ch and ch <= '9') x = (x << 3) + (x << 1) + (ch ^ 48), ch = getchar();
  return x * flg;
}

signed main(){
#ifdef LOCAL
  freopen("in.in", "r", stdin);
  freopen("out.out", "w", stdout);
#endif 
  // ----
  MULTICASE(){
    int n = read(), m = read();

    map<int, bool> st;

    for (int i = 0; i < m; i ++ ){
      int a = read(), b = read(), c = read();
      st[b] = 1;
    }

    for (int i = 1; i <= n; i ++ )
      if (!st[i]) {
        for (int j = 1; j <= n; j ++ )
          if (j != i){
            cout << i << ' ' << j << endl;
          }
          break;
      }
  }

  // ---- 
  return 0;
}

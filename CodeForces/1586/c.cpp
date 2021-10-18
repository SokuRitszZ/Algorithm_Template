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
  int n = read(), m = read();
  
  vector<string> s(n);
  for (auto &it : s) cin >> it;

  int q = read();
  vector<int> check(m + 1), pre(m + 2);
  
  for (int i = 1; i < n; i ++ )
    for (int j = 1; j < m; j ++ )
      if (s[i - 1][j] == 'X' and s[i][j - 1] == 'X')
        check[j] = 1;
  
  for (int i = 0; i < m; i ++ ) pre[i + 1] = pre[i] + check[i];
  
  while (q -- ){
    int a = read() - 1, b = read() - 1;
    if (a == b) cout << "YES\n";
    else {
      if (pre[b + 1] - pre[a + 1]) {
        cout << "NO\n";
      }else {
        cout << "YES\n";
      }
    }
  }
  // ---- 
  return 0;
}

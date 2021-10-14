#include <bits/stdc++.h>

using namespace std;
using cint = const int &;
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
  for (int t = read(); t -- ;) {
    int a, b, c;
    cin >> a >> b >> c;
    
    cout << max(max(b, c) - a + 1, 0) << ' ';
    cout << max(max(a, c) - b + 1, 0) << ' ';
    cout << max(max(a, b) - c + 1, 0) << endl;
  }

  // ---- 
  return 0;
}

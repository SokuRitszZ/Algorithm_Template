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
  for (int t = read(); t -- ;){
    int n = read();
    vector<int> a(n);
    for (int &it : a) it = read();
    sort(a.begin(), a.end());
    if (a[0] == a[n - 1]) {
      cout << -1 << endl;
      continue;
    }
    vector<int> b;
    for (int i = a.size() - 1; i; i -- ){
      a[i] -= a[i - 1];
      if (a[i]) b.push_back(a[i]);
    }
    sort(b.begin(), b.end());
    int res = 1e9;
    if (b.size() == 1) res = b[0];
    else{
      for (int i = 1; i < b.size(); i ++ )
        res = min(res, __gcd(b[i], b[i - 1]));
    }
      
    cout << res << endl;
  }

  // ---- 
  return 0;
}

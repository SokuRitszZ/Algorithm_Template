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

const int N = 2e6 + 10;

int cnt[N];
signed main(){
#ifdef LOCAL
  freopen("in.in", "r", stdin);
  freopen("out.out", "w", stdout);
#endif 
  // ----
  for (int _ = read(); _ -- ;){
    int n = read();
    vector<int> a(n);
    for (int &it : a) it = read();
    
    sort(a.begin(), a.end());
    
    bool ok = 0;
    for (int i = 0; i < n; i ++ ){
      int cnt = 1;
      while (i + 1 < a.size() and a[i] == a[i + 1]) cnt ++ , i ++ ;
      if (cnt >= n >> 1){
        ok = 1;
        cout << -1 << endl;
        break;
      }
    }
    if (ok) continue;

    for (int i = n - 1; i >= 0; i -- ) a[i] -= a[0];

    for (int k = a[n - 1]; k >= 1; k -- ){
      for (int i = 0; i < n; i ++ ){
        int md = a[i] % k;
        if ( ++ cnt[md] >= n >> 1) {
          ok = 1;
          cout << k << endl;
          break;
        }
      }
      for (int i = 0; i < n; i ++ ) cnt[a[i] % k] = 0;
      if (ok) break;
    }
  }

  // ---- 
  return 0;
}

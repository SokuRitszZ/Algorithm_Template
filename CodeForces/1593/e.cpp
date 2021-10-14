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
  for (int _ = read(); _ -- ;){
    int n = read(), k = read();
    
    vector<vector<int>> G(n + 1);
    vector<int> deg(n + 1);
    
    for (int i = 1; i < n; i ++ ){
      int a = read(), b = read();
      deg[a] ++ , deg[b] ++ ;
      G[a].push_back(b), G[b].push_back(a);
    }
    if (k >= n or n == 1 or n == 2) {
      cout << 0 << endl;
      continue;
    }
    queue<int> q;
    vector<int> d(n + 1, 0);
    for (int i = 1; i <= n; i ++ )
      if (deg[i] == 1) {
        q.push(i);
        d[i] = 1;
      }
    
    while (q.size()){
      int u = q.front(); q.pop();
      deg[u] -- ;
      for (int v : G[u]) {
        if (deg[v] == 0) continue;
        if ( -- deg[v] == 1) {
          d[v] = d[u] + 1;
          q.push(v);
        }
      }
    }

    vector<int> cnt(n + 1);
    
    for (int i = 1; i <= n; i ++ ) cnt[d[i]] ++ ;
    
    int ans;
    if (k > n) ans = 0;
    else {
      for (int i = 1; i <= k; i ++ ) n -= cnt[i];
      ans = n;
    }
    cout << ans << endl;
  }

  // ---- 
  return 0;
}

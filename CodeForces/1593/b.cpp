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

bool ok(char a, char b){
  return (a == '0' and b == '0') or (a == '5' and b == '2') or (a == '5' and b == '7') or (a == '0' and b == '5');
}

signed main(){
#ifdef LOCAL
  freopen("in.in", "r", stdin);
  freopen("out.out", "w", stdout);
#endif 
  // ----
  for (int t = read(); t -- ;){
    string s;
    cin >> s;
    reverse(s.begin(), s.end());
    if (ok(s[0], s[1])) cout << 0 << endl;
    else {
      int i = 0;
      while (i < s.size() and s[i] != '0' and s[i] != '5') i ++ ;
      int pos0, pos5;
      int start = i;
      while (i < s.size() and s[i] != '0') i ++ ;
      pos0 = i;
      i = start;
      while (i < s.size() and s[i] != '5') i ++ ;
      pos5 = i;
      
      int ans = 1e9;
      
      i = pos0 + 1;
      while (i < s.size() and s[i] != '0' and s[i] != '5') i ++ ;
      if (i < s.size()) ans = min(ans, i - pos0 - 1 + pos0);
    
      i = pos5 + 1;
      while (i < s.size() and s[i] != '2' and s[i] != '7') i ++ ;
      if (i < s.size()) ans = min(ans, i - 1 - pos5 + pos5);
      
      cout << ans << endl;
    }
  }

  // ---- 
  return 0;
}

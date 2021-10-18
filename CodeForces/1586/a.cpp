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

bool isprime(int x){
  for (int i = 2; i * i <= x; i ++ )
    if (x % i == 0) return 0;

  return 1;
}

signed main(){
#ifdef LOCAL
  freopen("in.in", "r", stdin);
  freopen("out.out", "w", stdout);
#endif 
  // ----
  MULTICASE(){
    int n = read();
    int sum = 0;
    vector<int> a(n);
    for (int &it : a) it = read(), sum += it;
    if (!isprime(sum)){
      cout << n << endl;
      for (int i = 1; i <= n; i ++ )
        cout << i << ' ';
    }
    else 
      for (int i = 0; i < n; i ++ ){
        if (!isprime(sum - a[i])){
          cout << n - 1 << endl;
          for (int j = 0; j < n; j ++ )
            if (i != j)
              cout << j + 1 << ' ';
          break;
        }
      }

    cout << endl;
  } 

  // ---- 
  return 0;
}

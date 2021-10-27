#include <bits/stdc++.h>

#define CT const 
#define IL inline
#define PB emplace_back
#define PP pop
#define FT front
#define endl '\n'
#define MULTICASE() for (int _ = read(), kase = 0; kase ++ , _ --;)

using namespace std;

typedef long long i6;

inline int read(){
  int x = 0, flg = 1; char ch = getchar();
  if (ch == '-')  flg = -1;
  while (ch < '0' or ch > '9') ch = getchar();
  while ('0' <= ch and ch <= '9') x = (x << 3) + (x << 1) + (ch ^ 48), ch = getchar();
  return x * flg;
}

CT int N = 1e4 + 10, M = 1e6 + 10;

struct Query{
  int i, l, r, t;
};

struct Modify{
  int k, c;
};

vector<Query> querys;
vector<Modify> modifies;

int cnt[M], ans[N];
int res;

IL void add(int x){
  if (cnt[x] == 0) res ++ ;
  cnt[x] ++ ;
}

IL void del(int x){
  cnt[x] -- ;
  if (cnt[x] == 0) res -- ;
}

signed main(){
  // ----
  int n = read(), m = read();
  vector<int> a(n + 1), grp(n + 1);

  for (int i = 1; i <= n; i ++ ) a[i] = read();
  
  modifies.push_back({0, 0});

  while (m -- ){
    if (getchar() == 'Q'){
      int l = read(), r = read();
      querys.push_back({querys.size(), l, r, modifies.size() - 1});
    }else {
      int k = read(), c = read();
      modifies.push_back({k, c});
    }
  }

  int len = sqrt(n);

  for (int i = 1; i <= n; i ++ ) grp[i] = i / len;

  sort(querys.begin(), querys.end(), [&](Query a, Query b){
    if (grp[a.l] != grp[b.l]) return grp[a.l] < grp[b.l];
    if (grp[a.r] != grp[b.r]) return grp[a.r] < grp[b.r];
    return a.t < b.t;
  }); 

  int t = 0, L = 1, R = 0;

  for (auto [i, l, r, tt] : querys){
    while (R < r) add(a[ ++ R]);
    while (R > r) del(a[R -- ]);
    while (L < l) del(a[L ++ ]);
    while (L > l) add(a[ -- L]);
    while (t < tt){
      ++ t;
      int k = modifies[t].k, &c = modifies[t].c;
      if (L <= k and k <= R) {
        del(a[k]);
        add(c);
      }
      swap(a[k], c);
    }
    while (t > tt){
      int k = modifies[t].k, &c = modifies[t].c;
      if (L <= k and k <= R) {
        del(a[k]);
        add(c);
      }
      swap(a[k], c);
      -- t;
    }

    ans[i] = res;
  }

  for (int i = 0; i < querys.size(); i ++ ) cout << ans[i] << endl;
  return 0;
}
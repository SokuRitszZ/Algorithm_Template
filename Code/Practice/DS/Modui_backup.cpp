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

struct Query{
  int i, l, r;
};

CT int M = 1e5 + 10;

int n, m, len;
vector<int> nums, w, grp;
vector<i6> ans;
vector<Query> q;
i6 res;
int cnt[M];

IL void add(int x){
  cnt[x] ++ ;
  res = max(res, (i6) cnt[x] * nums[x]);
}

signed main(){
  // ----
  n = read(), m = read(), len = sqrt(n);

  w.resize(n + 1), grp.resize(n + 1), ans.resize(m);

  for (int i = 1; i <= n; i ++ ) nums.push_back(w[i] = read()), grp[i] = i / len;

  sort(nums.begin(), nums.end());
  nums.erase(unique(nums.begin(), nums.end()), nums.end());

  for (int i = 1; i <= n; i ++ ) w[i] = lower_bound(nums.begin(), nums.end(), w[i]) - nums.begin();

  for (int i = 0; i < m; i ++ )
    q.push_back({i, read(), read()});

  sort(q.begin(), q.end(), [&](Query a, Query b){
    if (grp[a.l] != grp[b.l]) return grp[a.l] < grp[b.l];
    return a.r < b.r;
  });

  for (int x = 0; x < m;){
    int y = x;
    while (y < m and grp[q[y].l] == grp[q[x].l]) y ++ ;
    int right = grp[q[x].l] * len + len - 1;

    while (x < y and q[x].r <= right){
      res = 0;
      auto [i, l, r] = q[x];
      for (int k = l; k <= r; k ++ ) add(w[k]);
      ans[i] = res;
      for (int k = l; k <= r; k ++ ) cnt[w[k]] -- ;
      ++ x;
    } 

    res = 0;
    int R = right, L = right + 1;
    while (x < y){
      auto [i, l, r] = q[x];
      while (R < r) add(w[ ++ R]);
      i6 backup = res;
      while (L > l) add(w[ -- L]);
      ans[i] = res;
      while (L <= right) cnt[w[L ++ ]] -- ;
      res = backup;
      ++ x;
    }

    memset(cnt, 0, sizeof cnt);
  }

  for (int i = 0; i < m; i ++ ) cout << ans[i] << endl;

  // ---- 
  return 0;
}
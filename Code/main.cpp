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

CT int N = 1e5 + 10, M = 1 << 14;

int n, m, k, len;
vector<int> nums;

IL int lowbit(int x){
  return x & -x;
}

IL int popcount(int x){
  int res = 0;
  while (x) x -= lowbit(x), ++ res;
  return res;
}

int f[N], g[M], w[N];
i6 ans[N];

struct Query{
  int i, l, r;
  i6 res;
}q[N];

struct Range{
  int i, l, r, t;
};

vector<Range> ranges[N];

signed main(){
  cin.tie(0)->sync_with_stdio(0);
  // ----
  cin >> n >> m >> k;

  for (int i = 0; i < 1 << 14; i ++ )
    if (popcount(i) == k) nums.push_back(i);

  for (int i = 1; i <= n; i ++ ){
    cin >> w[i];
    f[i] = g[w[i]];

    for (int &x : nums) ++ g[w[i] xor x];
  } 
  
  for (int i = 0; i < m; i ++ ){
    int l, r; cin >> l >> r;
    q[i] = {i, l, r};
  }
  
  len = sqrt(n);
  sort(q, q + m, [&](Query a, Query b){
    int ll = a.l / len, rr = b.l / len;
    if (ll != rr) return ll < rr;
    return a.r < b.r;
  });

  for (int i = 0, L = 1, R = 0; i < m; i ++ ){
    auto [id, l, r, res] = q[i];
    if (R > r) ranges[L - 1].push_back({i, r + 1, R, 1});
    while (R > r) q[i].res -= f[R -- ];
    if (R < r) ranges[L - 1].push_back({i, R + 1, r, -1});
    while (R < r) q[i].res += f[ ++ R];
    if (L > l) ranges[R].push_back({i, l, L - 1, 1});
    while (L > l) q[i].res -= f[ -- L];
    if (L < l) ranges[R].push_back({i, L, l - 1, -1});
    while (L < l) q[i].res += f[L ++ ]; 
  }

  memset(g, 0, sizeof g);

  for (int i = 1; i <= n; i ++ ){
    for (int &x : nums) ++ g[w[i] xor x];
    for (auto [id, l, r, t] : ranges[i])
      for (int j = l; j <= r; j ++ )
        q[id].res += t * g[w[j]];
  }
  
  for (int i = 0; i < m; i ++ ) q[i].res += q[i - 1].res, ans[q[i].i] = q[i].res;
  for (int i = 0; i < m; i ++ ) cout << ans[i] << endl;

  // ---- 
  return 0;
}
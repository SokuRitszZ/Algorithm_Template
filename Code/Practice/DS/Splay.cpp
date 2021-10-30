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

CT int N = 1e5 + 10;

struct Node{
  int s[2], fa;
  int v, tag, size;
  IL void init(int _v, int _f){
    v = _v, fa = _f, size = 1;
  }
}tr[N];

int idx;
int n, m;

IL void pushup(int u){
  tr[u].size = tr[tr[u].s[0]].size + tr[tr[u].s[1]].size + 1;
}

IL void pushdown(int u){
  if (tr[u].tag){
    tr[u].tag = 0;
    tr[tr[u].s[0]].tag ^= 1, tr[tr[u].s[1]].tag ^= 1;
    swap(tr[u].s[0], tr[u].s[1]);
  }
}

IL void rotate(int x){
  int y = tr[x].fa, z = tr[y].fa;
  int p = tr[y].s[1] == x, c = tr[x].s[!p];
  tr[z].s[tr[z].s[1] == y] = x, tr[x].fa = z;
  tr[x].s[!p] = y, tr[y].fa = x;
  tr[y].s[p] = c, tr[c].fa = y;
  pushup(y), pushup(x);
}

int root;

IL void splay(int x, int fa){
  while (tr[x].fa != fa){
    int y = tr[x].fa, z = tr[y].fa;
    if (z != fa)
      (tr[y].s[1] == x) xor (tr[z].s[1] == y) ? rotate(x) : rotate(y);
    rotate(x);
  }
  if (!fa) root = x;
}

IL void insert(int v){
  int u = root, p = 0;
  while (u) p = u, u = tr[u].s[tr[u].v < v];
  u = ++ idx;
  if (p) tr[p].s[tr[p].v < v] = u;
  tr[u].init(v, p);
  splay(u, 0);
}

IL int kth(int k){
  int u = root;
  while (1){
    pushdown(u);
    int Left = tr[tr[u].s[0]].size;
    if (k == Left + 1) return u;
    if (k <= Left) u = tr[u].s[0];
    else u = tr[u].s[1], k -= Left + 1;
  } 
  return -1;
}

IL void rev(int l, int r){
  l = kth(l), r = kth(r + 2);
  splay(l, 0), splay(r, l);
  tr[tr[r].s[0]].tag ^= 1;
}

void dfs(int u){
  if (!u) return;
  pushdown(u);
  dfs(tr[u].s[0]);
  if (tr[u].v <= n and tr[u].v >= 1) cout << tr[u].v << ' ';
  dfs(tr[u].s[1]);
}

signed main(){
  cin.tie(0)->sync_with_stdio(0);
  // ----
  cin >> n >> m;
  
  for (int i = 0; i <= n + 1; i ++ ) insert(i);

  while (m -- ){
    int l, r; cin >> l >> r;
    rev(l, r);
  }

  dfs(root);
  // ---- 
  return 0;
}
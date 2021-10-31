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

CT int N = 1e5 + 10, INF = 0x3f3f3f3f;

struct Node{
  int f, s[2];
  int v, size;
  IL void init(int _v, int _f){
    v = _v, f = _f, size = 1;
  }
}tr[N];

int n, m, delta;

IL void pushup(int x){
  tr[x].size = tr[tr[x].s[0]].size + tr[tr[x].s[1]].size + 1;
}

IL void rotate(int x){
  int y = tr[x].f, z = tr[y].f;
  int p = tr[y].s[1] == x, c = tr[x].s[p xor 1];

  tr[z].s[tr[z].s[1] == y] = x, tr[x].f = z;
  tr[x].s[p xor 1] = y, tr[y].f = x;
  tr[y].s[p] = c, tr[c].f = y;

  pushup(y), pushup(x);
}

int root;

IL void splay(int x, int f){
  while (tr[x].f != f){
    int y = tr[x].f, z = tr[y].f;
    if (z != f) 
      (tr[y].s[1] == x) xor (tr[z].s[1] == y) ? rotate(x) : rotate(y);
    rotate(x);
  }

  if (!f) root = x;
}

int idx;

IL int insert(int v){
  int u = root, p = 0;
  while (u) p = u, u = tr[u].s[tr[u].v < v];

  u = ++ idx;
  tr[u].init(v, p);
  if (p) tr[p].s[tr[p].v < v] = u;
  splay(u, 0);

  return u;
}

IL int kth(int k){
  int u = root;
  while (u){
    int Left = tr[tr[u].s[0]].size;
    if (k == Left + 1) return tr[u].v;
    if (k <= Left) u = tr[u].s[0];
    else u = tr[u].s[1], k -= Left + 1; 
  }

  return -1;
}

IL int find(int v){
  int u = root, res = 0;
  while (u){
    if (tr[u].v >= v) res = u, u = tr[u].s[0];
    else u = tr[u].s[1];
  }
  return res;
}

signed main(){
  cin.tie(0)->sync_with_stdio(0);
  // ----
  cin >> n >> m;
  int L = insert(-INF), R = insert(INF), tot = 0;

  while (n -- ){
    char op[2]; int k; cin >> op >> k;

    if (op[0] == 'I' and k >= m) insert(k - delta), ++ tot;
    else if (op[0] == 'A') delta += k;
    else if (op[0] == 'S'){
      delta -= k;
      R = find(m - delta);
      splay(R, 0), splay(L, R);
      tr[L].s[1] = 0;
      pushup(L), pushup(R);
    }else if (op[0] == 'F'){
      if (tr[root].size - 2 < k) cout << -1 << endl;
      else cout << kth(tr[root].size - k) + delta << endl;
    }
  }

  cout << tot - tr[root].size + 2 << endl;
  // ---- 
  return 0;
}
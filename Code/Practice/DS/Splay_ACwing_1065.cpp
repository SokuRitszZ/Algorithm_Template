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

CT int N = 18e5 + 10;

struct Node{
  int s[2], f;
  int v, size, i;
  void init(int _v, int _f, int _i){
    v = _v, f = _f, size = 1, i = _i; 
  }
}tr[N];

int p[N], root[N];
int idx;

int find(int x){
  return x == p[x] ? x : p[x] = find(p[x]);
}

IL void pushup(int x){
  tr[x].size = tr[tr[x].s[0]].size + tr[tr[x].s[1]].size + 1;
}

IL void rotate(int x){
  int y = tr[x].f, z = tr[y].f;
  int p = tr[y].s[1] == x, c = tr[x].s[p ^ 1];
  tr[z].s[tr[z].s[1] == y] = x, tr[x].f = z;
  tr[x].s[p xor 1] = y, tr[y].f = x;
  tr[y].s[p] = c, tr[c].f = y;
  pushup(y), pushup(x);
}

IL void splay(int x, int f, int b){
  while (tr[x].f != f) {
    int y = tr[x].f, z = tr[y].f;
    if (z != f)
      (tr[y].s[1] == x) xor (tr[z].s[1] == y) ? rotate(x) : rotate(y);
    rotate(x);
  }

  if (!f) root[b] = x;
}

IL void insert(int v, int i, int b){
  int u = root[b], p = 0;
  while (u) p = u, u = tr[u].s[tr[u].v < v];
  tr[u = ++ idx].init(v, p, i);
  if (p) tr[p].s[tr[p].v < v] = u;
  splay(u, 0, b);
}

IL void dfs(int a, int b){
  if (!a) return ;
  insert(tr[a].v, tr[a].i, b);
  dfs(tr[a].s[0], b), dfs(tr[a].s[1], b);
}

IL int kth(int k, int b){
  int u = root[b];
  while (u){
    int Left = tr[tr[u].s[0]].size;
    if (k == Left + 1) return tr[u].i;
    if (k <= Left) u = tr[u].s[0];
    else u = tr[u].s[1], k -= Left + 1;
  }
  
  return -1;
}

signed main(){
	cin.tie(0)->sync_with_stdio(0);
  // ----
  int n, m; cin >> n >> m;
  for (int i = 1; i <= n; i ++ ){
    p[i] = root[i] = i;
    int v; cin >> v;
    tr[i].init(v, 0, i);
  }

  idx = n;

  while (m -- ){
    int a, b; cin >> a >> b;
    a = find(a), b = find(b);
    if (a != b){
      if (tr[root[a]].size > tr[root[b]].size) swap(a, b);
      dfs(root[a], b);
      p[a] = b;
    }
  }

  int q; cin >> q;

  while (q -- ){
    char op[2]; int a, b; cin >> op >> a >> b;
    if (op[0] == 'Q'){
      a = find(a);
      if (tr[root[a]].size < b) cout << -1 << endl;
      else cout << kth(b, a) << endl; 
    }else {
      a = find(a), b = find(b);
      if (a != b){
        if (tr[root[a]].size > tr[root[b]].size) swap(a, b);
        dfs(root[a], b);
        p[a] = b;
      }
    }
  }
  // ---- 
  return 0;
}
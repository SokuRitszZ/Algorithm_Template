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
	int s[2], f, v;
	int rev, sum;
}tr[N];

void pushup(int u){
	tr[u].sum = tr[tr[u].s[0]].sum xor tr[u].v xor tr[tr[u].s[1]].sum;
}

void pushrev(int u){
	tr[u].rev ^= 1;
	swap(tr[u].s[0], tr[u].s[1]);
}

void pushdown(int u){
	if (tr[u].rev){
		pushrev(tr[u].s[0]), pushrev(tr[u].s[1]);
		tr[u].rev = 0;
	}
}

bool is_root(int x){
	return tr[tr[x].f].s[0] != x and tr[tr[x].f].s[1] != x;
}

void rotate(int x){
	int y = tr[x].f, z = tr[y].f;
	int p = tr[y].s[1] == x, c = tr[x].s[p xor 1];
	if (!is_root(y)) tr[z].s[tr[z].s[1] == y] = x;
	tr[x].f = z;
	tr[x].s[p xor 1] = y, tr[y].f = x;
	tr[y].s[p] = c, tr[c].f = y;
	pushup(y), pushup(x);
}

int stk[N];

void splay(int x){
	int top = 0, r = x;
	stk[ ++ top] = r;
	while (!is_root(r)) stk[ ++ top] = r = tr[r].f;
	while (top) pushdown(stk[top -- ]);

	while (!is_root(x)) {
		int y = tr[x].f, z = tr[y].f;
		if (!is_root(y))
			(tr[y].s[1] == x) xor (tr[z].s[1] == y) ? rotate(x) : rotate(y);
		rotate(x);
	}
}

void access(int x){ // craete a real path between x and root
	int z = x;
	for (int y = 0; x; y = x, x = tr[x].f) {
		splay(x);
		tr[x].s[1] = y, pushup(x);
	}
	splay(z);
}

void make_root(int x){ // let x become the root of this original tree
	access(x);
	pushrev(x);
}

int find_root(int x){ // find the root of this original tree and let x become the root
	access(x);
	while (tr[x].s[0]) pushdown(x), x = tr[x].s[0];
	splay(x);
	return x;
}

void split(int x, int y){ // make a path between x_splay and y_splay
	make_root(x);
	access(y);	
}

void link(int x, int y){ // add a link between x and y if x is unlinked y
	make_root(x);
	if (find_root(y) != x) tr[x].f = y;
}

void cut(int x, int y){ // remove a link between x and y if x is linked y
	make_root(x);
	if (find_root(y) == x and tr[y].f == x and !tr[y].s[0]) {
		tr[x].s[1] = tr[y].f = 0;
		pushup(x);
	} 
}

signed main(){
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;

	for (int i = 1; i <= n; i ++ ) cin >> tr[i].v;

	while (m -- ){
		int op, x, y; cin >> op >> x >> y;
		if (op == 0) split(x, y), cout << tr[y].sum << endl;
		else if (op == 1) link(x, y);
		else if (op == 2) cut(x, y);
		else splay(x), tr[x].v = y, pushup(x);
	}

  return 0;
}
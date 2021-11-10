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
	int l, r, tag, sum;
}tr[N << 1];

int h[N], e[N], ne[N], idx;

void add(int a, int b){
	e[ ++ idx] = b, ne[idx] = h[a], h[a] = idx;
}

int dep[N], sz[N], son[N], fa[N];

void dfs1(int u, int depth){
	dep[u] = depth, sz[u] = 1;

	for (int i = h[u]; i; i = ne[i]){
		int v = e[i];
		fa[v] = u;
		dfs1(v, depth + 1);
		sz[u] += sz[v];
		if (sz[son[u]] < sz[v]) son[u] = v;
	}

}

int top[N], dfn[N], cnt;

void dfs2(int u, int t){
	top[u] = t, dfn[u] = ++ cnt;

	if (!son[u]) return ;
	dfs2(son[u], t);

	for (int i = h[u]; i; i = ne[i]){
		int v = e[i];
		if (v != son[u]) dfs2(v, v);
	}
}

void build(int l, int r, int u = 1){
	tr[u] = {l, r, 2, 0};
	if (l == r) return ;
	int mid = l + r >> 1;
	build(l, mid, u << 1), build(mid + 1, r, u << 1 | 1);
}

void pushup(int u){
	tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
}

void pushdown(int u){
	auto &x = tr[u], &l = tr[u << 1], &r = tr[u << 1 | 1];
	if (x.tag != 2){
		l.tag = x.tag, l.sum = (l.r - l.l + 1) * x.tag;
		r.tag = x.tag, r.sum = (r.r - r.l + 1) * x.tag;
		x.tag = 2;
	}
}

void modify(int l, int r, int c, int u = 1){
	if (l <= tr[u].l and tr[u].r <= r) {
		tr[u].tag = c;
		tr[u].sum = (tr[u].r - tr[u].l + 1) * c;
		return ;
	}

	pushdown(u);

	int mid = tr[u].l + tr[u].r >> 1;
	if (l <= mid) modify(l, r, c, u << 1);
	if (mid < r) modify(l, r, c, u << 1 | 1);

	pushup(u);
}

int modify_path(int u, int v, int c){
	int res = tr[1].sum;
	while (top[u] != top[v]){
		if (dep[u] < dep[v]) swap(u, v);
		modify(dfn[top[u]], dfn[u], c);
		u = fa[top[u]];
	}
	if (dep[u] < dep[v]) swap(u, v);
	modify(dfn[v], dfn[u], c);

	return res = abs(res - tr[1].sum);
}

int modify_tree(int u, int c){
	int res = tr[1].sum;

	modify(dfn[u], dfn[u] + sz[u] - 1, c);

	return res = abs(res - tr[1].sum);
}

signed main(){
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	for (int i = 2; i <= n; i ++ )	{
		int x; cin >> x;
		add( ++ x, i);
	}

	dfs1(1, 1);
	dfs2(1, 1);
	build(1, n);

	int m; cin >> m;

	while (m -- ){
		string op; int c; cin >> op >> c;
		++ c;
		if (op == "install") cout << modify_path(1, c, 1) << endl;
		else cout << modify_tree(c, 0) << endl;

	}
  return 0;
}
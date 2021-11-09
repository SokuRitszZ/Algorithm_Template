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

CT int N = 1e5 + 10, M = N << 1;

int e[M], ne[M], h[N], idx;
int w[N];

void add(int a, int b){
	e[ ++ idx] = b, ne[idx] = h[a], h[a] = idx;
}

int f[N], dep[N], son[N], sz[N], fa[N];

void dfs1(int u, int f, int depth){
	fa[u] = f, dep[u] = depth, son[u] = 0, sz[u] = 1;
	for (int i = h[u]; i; i = ne[i]){
		int v = e[i];
		if (v == f) continue;
		dfs1(v, u, depth + 1);
		sz[u] += sz[v];
		if (sz[son[u]] < sz[v]) son[u] = v;
	}
}

int dfn[N], top[N], nw[N], cnt;

void dfs2(int u, int t){
	dfn[u] = ++ cnt, top[u] = t, nw[cnt] = w[u];

	if (!son[u]) return ;
	dfs2(son[u], t);

	for (int i = h[u]; i; i = ne[i]) 
		if (e[i] != fa[u] and e[i] != son[u]) 
			dfs2(e[i], e[i]);

}

struct Node{
	int l, r;
	i6 tag, sum;
}tr[N << 2];

void pushup(int u){
	tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
}

void build(int l, int r, int u = 1){
	tr[u] = {l, r, 0, nw[l]};

	if (l == r) return;

	int mid = l + r >> 1;

	build(l, mid, u << 1), build(mid + 1, r, u << 1 | 1);

	pushup(u);
}

void pushdown(int u){
	auto &x = tr[u], &l = tr[u << 1], &r = tr[u << 1 | 1];
	if (x.tag){
		l.tag += x.tag, l.sum += x.tag * (l.r - l.l + 1);
		r.tag += x.tag, r.sum += x.tag * (r.r - r.l + 1);
		x.tag = 0;
	}
}

void modify(int l, int r, int c, int u = 1){
	if (l <= tr[u].l and tr[u].r <= r) 
		return tr[u].tag += c, tr[u].sum += (tr[u].r - tr[u].l + 1) * c, void();

	pushdown(u);

	int mid = tr[u].l + tr[u].r >> 1;
	if (l <= mid) modify(l, r, c, u << 1);
	if (mid < r) modify(l, r, c, u << 1 | 1);

	pushup(u);
}

i6 query(int l, int r, int u = 1){
	if (l <= tr[u].l and tr[u].r <= r) 
		return tr[u].sum;

	pushdown(u);

	int mid = tr[u].l + tr[u].r >> 1;
	i6 res = 0;
	if (l <= mid) res += query(l, r, u << 1);
	if (mid < r) res += query(l, r, u << 1 | 1);

	return res;
}

void modify_path(int u, int v, int c){
	while (top[u] != top[v]){
		if (dep[top[u]] < dep[top[v]]) swap(u, v);
		modify(dfn[top[u]], dfn[u], c);
		u = fa[top[u]];
	}

	if (dep[u] < dep[v]) swap(u, v); 
	modify(dfn[v], dfn[u], c);
}

void modify_tree(int u, int c){
	modify(dfn[u], dfn[u] + sz[u] - 1, c);
}

i6 query_path(int u, int v){
	i6 res = 0;
	while (top[u] != top[v]) {
		if (dep[top[u]] < dep[top[v]]) swap(u, v);
		res += query(dfn[top[u]], dfn[u]);
		u = fa[top[u]];
	}
	if (dep[u] < dep[v]) swap(u, v);
	res += query(dfn[v], dfn[u]);

	return res;
}

i6 query_tree(int u){
	return query(dfn[u], dfn[u] + sz[u] - 1);
}

signed main(){
	cin.tie(0)->sync_with_stdio(0);
  // ----
	int n; cin >> n;
	for (int i = 1; i <= n; i ++ ) cin >> w[i];

	for (int i = 1; i < n; i ++ ){
		int a, b; cin >> a >> b;
		add(a, b), add(b, a);
	}

	dfs1(1, 0, 1);
	dfs2(1, 1);
	build(1, n);

	// for (int i = 1; i <= n; i ++ ) cout << sz[i] << ' ';
	// cout << endl;

	int m; cin >> m;
	while (m -- ){
		int op; cin >> op;
		int a, b, c;
		if (op == 1){
			cin >> a >> b >> c;
			modify_path(a, b, c);
			// cout << query_path(a, b) << endl;
		}else if (op == 2){
			cin >> a >> c;
			modify_tree(a, c);
			// cout << query_tree(a) << endl;
		}else if (op == 3){
			cin >> a >> b;
			cout << query_path(a, b) << endl;
		}else {
			cin >> a;
			cout << query_tree(a) << endl;
		}
	}
  // ---- 
  return 0;
}
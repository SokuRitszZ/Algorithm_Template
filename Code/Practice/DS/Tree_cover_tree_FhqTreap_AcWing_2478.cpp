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

CT int N = 5e5 + 10, INF = 1e9;

struct Fhq{
	int v, size;
	int s[2], rnd;
	void init(int _v){
		v = _v; size = 1; s[0] = s[1] = 0; rnd = rand();
	}
}tr[N * 6];

int L[N << 2], R[N << 2], T[N << 2];
int idx, w[N];

IL void pushup(int u){
	tr[u].size = tr[tr[u].s[0]].size + tr[tr[u].s[1]].size + 1;
}

void split(int u, int v, int &x, int &y){
	if (!u) return x = y = 0, void();
	if (tr[u].v <= v) x = u, split(tr[u].s[1], v, tr[u].s[1], y);
	else y = u, split(tr[u].s[0], v, x, tr[u].s[0]);
	pushup(u);
}

int merge(int x, int y){

	if (!x or !y) return x + y;
	if (tr[x].rnd > tr[y].rnd) return tr[x].s[1] = merge(tr[x].s[1], y), pushup(x), x;
	return tr[y].s[0] = merge(x, tr[y].s[0]), pushup(y), y;
}

int NEW(int v){
	tr[ ++ idx].init(v);
	return idx;
}

void insert(int &root, int v){
	int x, y;
	split(root, v, x, y);
	root = merge(merge(x, NEW(v)), y);
}

void dfs(int u){
	if (!u) return ;

	dfs(tr[u].s[0]);
	cout << tr[u].v << ' ';
	dfs(tr[u].s[1]);
}

void build(int l, int r, int u = 1){
	L[u] = l, R[u] = r, insert(T[u], -INF), insert(T[u], INF);
	for (int i = l; i <= r; ++ i) insert(T[u], w[i]);
	// dfs(T[u]); cout << endl;
	if (l == r) return ;
	
	int mid = l + r >> 1;
	build(l, mid, u << 1), build(mid + 1, r, u << 1 | 1);
}

void remove(int &root, int v){
	int x, y, z;
	split(root, v - 1, x, y), split(y, v, y, z);
	y = merge(tr[y].s[0], tr[y].s[1]);
	root = merge(x, merge(y, z));	
}

int query_rnk(int l, int r, int v, int u = 1){
	if (l <= L[u] and R[u] <= r) {
		int x, y; split(T[u], v - 1, x, y);
		int res = tr[x].size - 1;
		return T[u] = merge(x, y), res;
	}

	int mid = L[u] + R[u] >> 1, res = 0;
	if (l <= mid) res += query_rnk(l, r, v, u << 1);
	if (mid < r) res += query_rnk(l, r, v, u << 1 | 1);

	return res;
}

void modify(int pos, int v, int u = 1){
	remove(T[u], w[pos]), insert(T[u], v);

	if (L[u] == R[u]) return ;

	int mid = L[u] + R[u] >> 1;
	if (pos <= mid) modify(pos, v, u << 1);
	else modify(pos, v, u << 1 | 1);
}

int query_pre(int l, int r, int v, int u = 1){
	if (l <= L[u] and R[u] <= r){
		int x, y; split(T[u], v - 1, x, y);
		int t = x;
		while (tr[t].s[1]) t = tr[t].s[1];
		return T[u] = merge(x, y), tr[t].v;
	}

	int mid = L[u] + R[u] >> 1, res = -INF;
	if (l <= mid) res = max(res, query_pre(l, r, v, u << 1));
	if (mid < r) res = max(res, query_pre(l, r, v, u << 1 | 1));

	return res;
}

int query_suf(int l, int r, int v, int u = 1){
	if (l <= L[u] and R[u] <= r){
		int x, y; split(T[u], v, x, y);
		int t = y;
		while (tr[t].s[0]) t = tr[t].s[0];
		return T[u] = merge(x, y), tr[t].v;
	}

	int mid = L[u] + R[u] >> 1, res = INF;
	if (l <= mid) res = min(res, query_suf(l, r, v, u << 1));
	if (mid < r) res = min(res, query_suf(l, r, v, u << 1 | 1));

	return res;
}

signed main(){
	cin.tie(0)->sync_with_stdio(0);
  // ----
	int n, m; cin >> n >> m;

	for (int i = 1; i <= n; i ++ ) cin >> w[i];

	build(1, n);
	
	while (m -- ){
		int op; cin >> op;
		int l, r, x;
		if (op == 1){
			cin >> l >> r >> x;
			cout << query_rnk(l, r, x) + 1 << endl;
		}else if (op == 2){
			cin >> l >> r >> x;
			int ll = 0, rr = 1e8;
			while (ll < rr){
				int mid = ll + rr + 1 >> 1;
				if (query_rnk(l, r, mid) + 1 <= x) ll = mid;
				else rr = mid - 1;
			}
			cout << rr << endl;
		}else if (op == 3){
			cin >> l >> x;
			modify(l, x);
			w[l] = x;
		}else if (op == 4){
			cin >> l >> r >> x;
			cout << query_pre(l, r, x) << endl;
		}else {
			cin >> l >> r >> x;
			cout << query_suf(l, r, x) << endl;
		}
	}

  // ---- 
  return 0;
}
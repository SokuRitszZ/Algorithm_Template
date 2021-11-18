#include <iostream>
#include <cstring>

#define CT const 
#define IL inline
#define endl '\n'
#define all(x) x.begin(), x.end()
#define MULTICASE() int _, kase; for (scanf("%d", &_), kase = 0; kase ++ , _ --;)

using namespace std;

typedef long long i6;

CT int N = 5e4 + 10, M = N;

int h[N], e[M], ne[M], idx;
int deg[N];
int dfn[N], sz[N], seq[N], cnt;

struct Node{
	int l, r, v;
	int tag;

	void init(int _l, int _r, int _v){
		l = _l, r = _r, v = tag = _v;
	}
}tr[N << 2];

void add(int a, int b){
	e[ ++ idx] = b, ne[idx] = h[a], h[a] = idx;
}

void dfs(int u){
	dfn[u] = ++ cnt, sz[u] = 1, seq[cnt] = u;

	for (int i = h[u]; i; i = ne[i]){
		int v = e[i];
		dfs(v);
		sz[u] += sz[v];
	}
}

void build(int l, int r, int u = 1){
	tr[u].init(l, r, -1);

	if (l == r) return ;

	int mid = l + r >> 1;
	build(l, mid, u << 1), build(mid + 1, r, u << 1 | 1);

}

void pushdown(int u){
	if (~tr[u].tag){
		tr[u << 1].tag = tr[u << 1].v = tr[u << 1 | 1].tag = tr[u << 1 | 1].v = tr[u].tag;
		tr[u].tag = -1;
	}
}

void modify(int l, int r, int c, int u = 1){
	if (l <= tr[u].l && tr[u].r <= r)
		return void(tr[u].v = tr[u].tag = c);

	pushdown(u);

	int mid = tr[u].l + tr[u].r >> 1;
	if (l <= mid) modify(l, r, c, u << 1);
	if (mid < r) modify(l, r, c, u << 1 | 1);
}

int query(int k, int u = 1){
	if (tr[u].l == tr[u].r) return tr[u].v;

	pushdown(u);

	int mid = tr[u].l + tr[u].r >> 1;
	if (k <= mid) return query(k, u << 1);
	return query(k, u << 1 | 1);

}

signed main(){
	cin.tie(0)->sync_with_stdio(0);
	MULTICASE(){
		printf("Case #%d:\n", kase);
		memset(h, 0, sizeof h);
		memset(deg, 0, sizeof deg);
		idx = cnt = 0;

		int n; scanf("%d", &n);

		for (int i = 1; i < n; ++ i){
			int a, b; scanf("%d %d", &a, &b);

			add(b, a), ++ deg[a];
		}

		int root = 0;
		for (int i = 1; i <= n; ++ i) {
			if (!deg[i]){
				root = i; break;
			}
		}

		dfs(root);
		build(1, n);

		// for (int i = 1; i <= n; ++ i) printf("%d ", seq[i]);
		// puts("");
		// for (int i = 1; i <= n; ++ i) printf("%d ", sz[seq[i]]);
		// puts("");
			
		int m; scanf("%d", &m); 

		while (m -- ){
			char op[2]; int x, y; scanf("%s", op);
			if (*op == 'C') 
				scanf("%d", &x), printf("%d\n", query(dfn[x]));
			else 
				scanf("%d %d", &x, &y), modify(dfn[x], dfn[x] + sz[x] - 1, y);

			// for (int i = 1; i <= n; ++ i) printf("%d ", query(seq[i]));
			// puts("");
		}
	}
  return 0;
}
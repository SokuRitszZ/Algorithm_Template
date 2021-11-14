#include <iostream>

#define CT const 
#define IL inline
#define endl '\n'
#define MULTICASE() int _, kase; for (scanf("%d", &_), kase = 0; kase ++ , _ --;)

using namespace std;

typedef long long i6;

CT int N = 1e5 + 10;

struct Node{
	int l, r, sum, tag;
	void init(int _l, int _r){
		l = _l, r = _r, sum = 1, tag = 0;
	}
}tr[N << 2];

void pushup(int u){
	tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
}

void build(int l, int r, int u = 1){
	tr[u].init(l, r);

	if (l == r) return ;

	int mid = l + r >> 1;
	build(l, mid, u << 1), build(mid + 1, r, u << 1 | 1);

	pushup(u);
}

void pushdown(int u){
	if (tr[u].tag) {
		auto &l = tr[u << 1], &r = tr[u << 1 | 1];
		l.tag = r.tag = tr[u].tag;
		l.sum = l.tag * (l.r - l.l + 1), r.sum = r.tag * (r.r - r.l + 1);
		tr[u].tag = 0;
	}
}

void modify(int l, int r, int c, int u = 1){
	if (l <= tr[u].l && tr[u].r <= r) return tr[u].sum = c * (tr[u].r - tr[u].l + 1), tr[u].tag = c, void();

	pushdown(u);

	int mid = tr[u].l + tr[u].r >> 1;

	if (l <= mid) modify(l, r, c, u << 1);
	if (mid < r) modify(l, r, c, u << 1 | 1);

	pushup(u);
}

int query(int l, int r, int u = 1){
	if (l <= tr[u].l && tr[u].r <= r) return tr[u].sum;

	pushdown(u);

	int mid = tr[u].l + tr[u].r >> 1, res = 0;
	if (l <= mid) res += query(l, r, u << 1);
	if (mid < r) res += query(l, r, u << 1 | 1);

	return res;
}

signed main(){
	cin.tie(0)->sync_with_stdio(0);
	MULTICASE(){
		int n; scanf("%d", &n);

		build(1, n);

		int m; scanf("%d", &m);

		while (m -- ){
			int l, r, v; scanf("%d %d %d", &l, &r, &v);
			modify(l, r, v);
		}

		printf("Case %d: The total value of the hook is %d.\n", kase, query(1, n));
	}
  return 0;
}
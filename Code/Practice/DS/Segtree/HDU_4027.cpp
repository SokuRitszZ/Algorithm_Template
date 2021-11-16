#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>

#define CT const 
#define IL inline
#define endl '\n'
#define all(x) x.begin(), x.end()
#define MULTICASE() i6 _, kase; for (cin >> _, kase = 0; kase ++ , _ --;)

using namespace std;

typedef long long i6;

CT int N = 1e5 + 10;

struct Node{
	int l, r;
	i6 sum, maxv;
	void init(int _l, int _r, i6 _sum){
		l = _l, r = _r, sum = maxv = _sum;
	}
}tr[N << 2];

i6 w[N];

void pushup(int u){
	tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
	tr[u].maxv = max(tr[u << 1].maxv, tr[u << 1 | 1].maxv);
}

void build(int l, int r, int u = 1){
	tr[u].init(l, r, w[r]);

	if (l == r) return ;

	i6 mid = l + r >> 1;
	build(l, mid, u << 1), build(mid + 1, r, u << 1 | 1);

	pushup(u);
}

void modify(int l, int r, int u = 1){
	if (tr[u].maxv <= 1) return;
	if (tr[u].l == tr[u].r) return void(tr[u].maxv = tr[u].sum = sqrt(tr[u].sum));

	int mid = tr[u].l + tr[u].r >> 1;
	if (l <= mid) modify(l, r, u << 1);
	if (mid < r) modify(l, r, u << 1 | 1);

	pushup(u);
}

i6 query(int l, int r, int u = 1){
	if (l <= tr[u].l && tr[u].r <= r) return tr[u].sum;

	int mid = tr[u].l + tr[u].r >> 1;
	i6 res = 0;

	if (l <= mid) res += query(l, r, u << 1);
	if (mid < r) res += query(l, r, u << 1 | 1);

	return res;
}

signed main(){
	cin.tie(0)->sync_with_stdio(0);
	int kase = 0;
	int n; while (~scanf("%d", &n)){
		printf("Case #%d:\n", ++ kase);

		for (int i = 1; i <= n; ++ i) scanf("%lld", &w[i]);

		build(1, n);

		int m; scanf("%d", &m);

		while (m -- ){
			int op, l, r; scanf("%d %d %d", &op, &l, &r);
			if (l > r) swap(l, r);
			if (op)	printf("%lld\n", query(l, r));
			else modify(l, r);
		}

		puts("");
	}
  return 0;
}
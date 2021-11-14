#include <iostream>
#include <cstdio>

#define CT const 
#define IL inline
#define endl '\n'
#define MULTICASE() i6 _, kase; for (cin >> _, kase = 0; kase ++ , _ --;)

using namespace std;

typedef long long i6;

CT i6 N = 1e5 + 10;

struct Node{
	i6 l, r, sum, tag;
	void init(i6 _l, i6 _r, i6 _sum, i6 _tag){
		l = _l, r = _r, sum = _sum, tag = _tag;
	}
}tr[N << 2];

void pushup(i6 u){
	tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
}

i6 w[N];

void build(i6 l, i6 r, i6 u = 1){
	tr[u].init(l, r, w[r], 0);

	if (l == r) return ;

	i6 mid = l + r >> 1;

	build(l, mid, u << 1), build(mid + 1, r, u << 1 | 1);

	pushup(u);
}

void pushdown(i6 u){
	if (tr[u].tag){
		tr[u << 1].tag += tr[u].tag, tr[u << 1 | 1].tag += tr[u].tag;
		tr[u << 1].sum += tr[u].tag * (tr[u << 1].r - tr[u << 1].l + 1);
		tr[u << 1 | 1].sum += tr[u].tag * (tr[u << 1 | 1].r - tr[u << 1 | 1].l + 1);
		tr[u].tag = 0;
	}
}

void modify(i6 l, i6 r, i6 c, i6 u = 1){
	if (l <= tr[u].l and tr[u].r <= r) {
		tr[u].sum += c * (tr[u].r - tr[u].l + 1);
		tr[u].tag += c;
		return ;
	}

	pushdown(u);

	i6 mid = tr[u].l + tr[u].r >> 1;
	if (l <= mid) modify(l, r, c, u << 1);
	if (mid < r) modify(l, r, c, u << 1 | 1);

	pushup(u);
}

i6 query(i6 l, i6 r, i6 u = 1){
	if (l <= tr[u].l and tr[u].r <= r) return tr[u].sum;

	pushdown(u);

	i6 mid = tr[u].l + tr[u].r >> 1, res = 0;
	if (l <= mid) res += query(l, r, u << 1);
	if (mid < r) res += query(l, r, u << 1 | 1);

	pushup(u);
	return res;
}

signed main(){
	cin.tie(0)->sync_with_stdio(0);
	i6 n, m; scanf("%lld %lld", &n, &m);

	for (i6 i = 1; i <= n; ++ i) scanf("%lld", &w[i]);

	build(1, n);
	
	while (m -- ){
		char op[2]; scanf("%s", op);
		i6 x, y, z; scanf("%lld %lld", &x, &y);
		if (*op == 'Q') printf("%lld\n", query(x, y));
		else scanf("%lld", &z), modify(x, y, z);
	}

  return 0;
}
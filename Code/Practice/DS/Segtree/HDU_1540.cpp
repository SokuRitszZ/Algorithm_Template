#include <iostream>
#include <algorithm>

#define CT const 
#define IL inline
#define endl '\n'
#define all(x) x.begin(), x.end()
#define MULTICASE() int _, kase; for (cin >> _, kase = 0; kase ++ , _ --;)

using namespace std;

typedef long long i6;

CT int N = 5e4 + 10;

struct Node{
	int l, r, v;
	int maxl, minr;
	void init(int _l, int _r, int _v, int _maxl, int _minr){
		l = _l, r = _r, v = _v, maxl = _maxl, minr = _minr;
	}
}tr[N << 2];

int n, m;
int destroyed[N], top;

void build(int l, int r, int u = 1){
	tr[u].init(l, r, 1, 0, n + 1);

	if (l == r) return ;

	int mid = l + r >> 1;
	build(l, mid, u << 1), build(mid + 1, r, u << 1 | 1);

}

void pushup(int u){
	tr[u].maxl = max(tr[u << 1].maxl, tr[u << 1 | 1].maxl);
	tr[u].minr = min(tr[u << 1].minr, tr[u << 1 | 1].minr);
}

void modify(int k, int c, int u = 1){
	if (tr[u].l == tr[u].r){
		tr[u].v = c;

		if (c) tr[u].maxl = 0, tr[u].minr = n + 1;
		else tr[u].maxl = tr[u].minr = k;

		return ;
	}
	int mid = tr[u].l + tr[u].r >> 1;
	if (k <= mid) modify(k, c, u << 1);
	else modify(k, c, u << 1 | 1);

	pushup(u);	
}

int query(int type, int l, int r, int u = 1){
	if (l <= tr[u].l && tr[u].r <= r)
		return type ? tr[u].minr : tr[u].maxl;

	int mid = tr[u].l + tr[u].r >> 1, res = type * (n + 1);

	if (l <= mid) res = type ? min(res, query(type, l, r, u << 1)) : max(res, query(type, l, r, u << 1));
	if (mid < r) res = type ? min(res, query(type, l, r, u << 1 | 1)) : max(res, query(type, l, r, u << 1 | 1));

	return res;
}

signed main(){
	cin.tie(0)->sync_with_stdio(0);
	while (~scanf("%d %d", &n, &m)){
		top = 0;
		build(1, n);
		while (m -- ){
			char op[2]; int x; scanf("%s", op);
			if (*op == 'D'){
				scanf("%d", &x);
				modify(x, 0);
				destroyed[ ++ top] = x;
			}
			else if (*op == 'Q'){
				scanf("%d", &x);
				int Left = query(0, 1, x), Right = query(1, x, n);
				// printf("%d %d\n", Left, Right);
				printf("%d\n", max(0, Right - Left - 1));
			}
			else modify(destroyed[top -- ], 1);
		}
	}
  return 0;
}
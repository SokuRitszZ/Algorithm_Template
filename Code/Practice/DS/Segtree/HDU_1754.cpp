#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

#define CT const 
#define IL inline
#define endl '\n'
#define MULTICASE() int _, kase; for (scanf("%d", &_), kase = 0; kase ++ , _ --;)

using namespace std;

typedef long long i6;


CT int N = 2e5 + 10;

struct Node{
	int l, r;
	int sum;
}tr[N << 2];

int w[N];

void pushup(int u){
	tr[u].sum = max(tr[u << 1].sum, tr[u << 1 | 1].sum);
}

void build(int l, int r, int u = 1){
	tr[u] = {l, r, w[r]};

	if (l == r) return ;

	int mid = l + r >> 1;
	build(l, mid, u << 1), build(mid + 1, r, u << 1 | 1);

	pushup(u);
}

int query(int l, int r, int u = 1){
	if (l <= tr[u].l && tr[u].r <= r) return tr[u].sum;

	int mid = tr[u].l + tr[u].r >> 1, res = 0;

	if (l <= mid) res = max(res, query(l, r, u << 1));
	if (mid < r) res = max(res, query(l, r, u << 1 | 1));

	return res;
}

void modify(int k, int c, int u = 1){
	if (tr[u].l == tr[u].r) return tr[u].sum = c, void();

	int mid = tr[u].l + tr[u].r >> 1;
	if (k <= mid) modify(k, c, u << 1);
	else modify(k, c, u << 1 | 1);

	pushup(u);
}

signed main(){
	cin.tie(0)->sync_with_stdio(0);
	int n, m;
	while (~scanf("%d %d", &n, &m)){
		for (int i = 1; i <= n; ++ i) scanf("%d", &w[i]);
		build(1, n);

		while (m -- ){
			char op[2]; scanf("%s", op);
			int x, y; scanf("%d %d", &x, &y);
			if (*op == 'Q') printf("%d\n", query(x, y));
			else modify(x, y);
		}
	}	
	return 0;
}
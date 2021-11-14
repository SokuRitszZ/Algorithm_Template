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
	int l, r, maxv, minv;
}tr[N << 2];

int w[N];

void pushup(int u){
	tr[u].maxv = max(tr[u << 1].maxv, tr[u << 1 | 1].maxv);
	tr[u].minv = min(tr[u << 1].minv, tr[u << 1 | 1].minv);
}

void build(int l, int r, int u = 1){
	tr[u].l = l, tr[u].r = r, tr[u].maxv = tr[u].minv = w[r];
	if (l == r) return ;

	int mid = l + r >> 1;
	build(l, mid, u << 1), build(mid + 1, r, u << 1 | 1);

	pushup(u);
}

int max_query(int l, int r, int u = 1){
	if (l <= tr[u].l and tr[u].r <= r) return tr[u].maxv;

	int mid = tr[u].l + tr[u].r >> 1, res = 0;
	if (l <= mid) res = max(res, max_query(l, r, u << 1));
	if (mid < r) res = max(res, max_query(l, r, u << 1 | 1));

	return res;
}

int min_query(int l, int r, int u = 1){
	if (l <= tr[u].l and tr[u].r <= r) return tr[u].minv;

	int mid = tr[u].l + tr[u].r >> 1, res = 1e6;
	if (l <= mid) res = min(res, min_query(l, r, u << 1));
	if (mid < r) res = min(res, min_query(l, r, u << 1 | 1));

	return res;
}

signed main(){
	cin.tie(0)->sync_with_stdio(0);
	int n, m; scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; ++ i) scanf("%d", &w[i]);

	build(1, n);

	while (m -- ){
		int l, r; scanf("%d %d", &l, &r);

		printf("%d\n", max_query(l, r) - min_query(l, r));
	}
  return 0;
}
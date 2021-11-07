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

CT int N = 5e4 + 10, INF = 0x3f3f3f3f;

struct Node{
	int l, r;
	multiset<int> s;
}tr[N << 2];

int w[N];

void build(int l, int r, int u = 1){
	tr[u] = {l, r};
	tr[u].s.insert(-INF), tr[u].s.insert(INF);
	for (int i = l; i <= r; i ++ ) tr[u].s.insert(w[i]);

	if (l == r) return ;
	int mid = l + r >> 1;
	build(l, mid, u << 1), build(mid + 1, r, u << 1 | 1);
}

void modify(int pos, int x, int u = 1){
	tr[u].s.erase(tr[u].s.find(w[pos]));
	tr[u].s.insert(x);

	if (tr[u].l == tr[u].r) return ;

	int mid = tr[u].l + tr[u].r >> 1;
	if (pos <= mid) modify(pos, x, u << 1);
	else modify(pos, x, u << 1 | 1);
}

int query(int l, int r, int x, int u = 1){
	if (l <= tr[u].l and tr[u].r <= r) {
		auto it = tr[u].s.lower_bound(x);
		-- it;
		return *it;
	}
	int mid = tr[u].l + tr[u].r >> 1, res = -INF;
	if (l <= mid) res = max(res, query(l, r, x, u << 1));
	if (mid < r) res = max(res, query(l, r, x, u << 1 | 1));

	return res;
}

signed main(){
	cin.tie(0)->sync_with_stdio(0);
  // ----
	int n, m; cin >> n >> m;
	for (int i = 1; i <= n; ++ i) cin >> w[i];

	build(1, n);
	
	while (m -- ){
		int op; cin >> op;
		if (op == 1) {
			int pos, x; cin >> pos >> x;
			modify(pos, x);
			w[pos] = x;
		}else if (op == 2){
			int l, r, x; cin >> l >> r >> x;
			cout << query(l, r, x) << endl;
		}
	}
  // ---- 
  return 0;
}
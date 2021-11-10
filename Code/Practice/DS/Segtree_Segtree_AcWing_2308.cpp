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

CT int N = 5e4 + 10, P = N * 17 * 17, M = N << 2;

struct Node{
	int l, r, sum, add;
}tr[P];

struct Query{
	int op, a, b, c;
}q[N];

int L[M], R[M], T[M], idx;
int n, m;
vector<int> nums;

void build(int l, int r, int u = 1){
	L[u] = l, R[u] = r, T[u] = ++ idx;
	if (l == r) return ;

	int mid = l + r >> 1;

	build(l, mid, u << 1), build(mid + 1, r, u << 1 | 1);
}

int get(int x){
	return lower_bound(nums.begin(), nums.end(), x) - nums.begin();
}

int intersection(int a, int b, int c, int d){
	return min(b, d) - max(a, c) + 1;
}

// update can be more simple
void update(int l, int r, int pl, int pr, int u = 1){
	tr[u].sum += intersection(l, r, pl, pr);
	if (pl <= l and r <= pr) return ++ tr[u].add, void();

	int mid = l + r >> 1;
	if (pl <= mid) {
		if (!tr[u].l) tr[u].l = ++ idx;
		update(l, mid, pl, pr, tr[u].l);
	}
	if (mid < pr){
		if (!tr[u].r) tr[u].r = ++ idx;
		update(mid + 1, r, pl, pr, tr[u].r);
	}
}

void change(int l, int r, int c, int u = 1){
	update(1, n, l, r, T[u]);

	if (L[u] == R[u]) return ;

	int mid = L[u] + R[u] >> 1;

	if (c <= mid) change(l, r, c, u << 1);
	else change(l, r, c, u << 1 | 1);
}

int get_sum(int l, int r, int pl, int pr, int add, int u = 1){
	if (pl <= l and r <= pr) return tr[u].sum + (r - l + 1) * add;

	int mid = l + r >> 1, res = 0;
	add += tr[u].add;

	if (pl <= mid){
		if (tr[u].l) res += get_sum(l, mid, pl, pr, add, tr[u].l);
		else res += intersection(l, mid, pl, pr) * add;
	}
	if (pr > mid){
		if (tr[u].r) res += get_sum(mid + 1, r, pl, pr, add, tr[u].r);
		else res += intersection(mid + 1, r, pl, pr) * add;
	}
	return res;
}

int query(int l, int r, int c, int u = 1){
	if (L[u] == R[u]) return R[u];

	int mid = L[u] + R[u] >> 1, k = get_sum(1, n, l, r, 0, T[u << 1 | 1]);
	if (k >= c) return query(l, r, c, u << 1 | 1);
	return query(l, r, c - k, u << 1);
}

signed main(){
	cin.tie(0)->sync_with_stdio(0);
	cin >> n >> m;

	for (int i = 0; i < m; i ++ ){
		cin >> q[i].op >> q[i].a >> q[i].b >> q[i].c;
		if (q[i].op == 1) nums.push_back(q[i].c);
	}

	sort(nums.begin(), nums.end());
	nums.erase(unique(nums.begin(), nums.end()), nums.end());
	build(0, nums.size() - 1);

	for (int i = 0; i < m; i ++ ){
		auto [op, a, b, c] = q[i];
		if (op == 1) change(a, b, get(c));
		else cout << nums[query(a, b, c)] << endl;
	}

  return 0;
}
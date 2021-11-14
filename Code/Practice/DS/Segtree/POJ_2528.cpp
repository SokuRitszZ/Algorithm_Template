#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

#define CT const 
#define IL inline
#define endl '\n'
#define MULTICASE() int _, kase; for (scanf("%d", &_), kase = 0; kase ++ , _ --;)

using namespace std;

typedef long long i6;

vector<int> nums;

int get(int x){return lower_bound(nums.begin(), nums.end(), x) - nums.begin(); }

CT int N = 2e4 + 10;

struct Query{
	int l, r;
}q[N];

struct Node{
	int l, r, v, tag;
	void init(int _l, int _r, int _v, int _tag){
		l = _l, r = _r, v = _v, tag = _tag;
	}
}tr[N << 2];

void build(int l, int r, int u = 1){
	tr[u].init(l, r, nums[r], -1);
	if (l == r) return ;

	int mid = l + r >> 1;

	build(l, mid, u << 1), build(mid + 1, r, u << 1 | 1);
}

void pushdown(int u){
	if (~tr[u].tag){
		tr[u << 1].tag = tr[u << 1 | 1].tag = tr[u << 1].v = tr[u << 1 | 1].v = tr[u].tag;
		tr[u].tag = -1;
	}
}

void modify(int l, int r, int c, int u = 1){
	if (l <= tr[u].l and tr[u].r <= r) return tr[u].v = tr[u].tag = c, void();

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
	else return query(k, u << 1 | 1);
}

bool st[N];

signed main(){
	cin.tie(0)->sync_with_stdio(0);

	MULTICASE(){
		nums.resize(0);
		memset(st, 0, sizeof st);

		int n; scanf("%d", &n);

		for (int i = 0; i < n; ++ i){
			int l, r; scanf("%d %d", &l, &r);
			q[i].l = l, q[i].r = r;
			nums.push_back(l), nums.push_back(r);
		}

		sort(nums.begin(), nums.end());
		nums.erase(unique(nums.begin(), nums.end()), nums.end());

		build(0, nums.size() - 1);

		for (int i = 0; i < n; ++ i) 
			modify(get(q[i].l), get(q[i].r), i);

		for (int i = 0; i < nums.size(); ++ i)
			st[query(i)] = 1;

		int res = 0;
		for (int i = 0; i < nums.size(); ++ i) 
			res += st[i];

		printf("%d\n", res);
	}
  return 0;
}
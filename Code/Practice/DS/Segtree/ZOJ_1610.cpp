#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>

#define CT const 
#define IL inline
#define endl '\n'
#define all(x) x.begin(), x.end()
#define MULTICASE() int _, kase; for (cin >> _, kase = 0; kase ++ , _ --;)

using namespace std;

typedef long long i6;

CT int N = 1e5 + 10;

struct Query{
	int l, r, c;
}q[N];

struct Node{
	int l, r, v, tag;
	void init(int _l, int _r){
		l = _l, r = _r, v = 0, tag = 0;
	}
}tr[N << 2];

vector<int> nums, colors;
int st[N];

int get(int x){return lower_bound(all(nums), x) - nums.begin(); }

void build(int l, int r, int u = 1){
	tr[u].init(l, r);

	if (l == r) return ;

	int mid = l + r >> 1;
	build(l, mid, u << 1), build(mid + 1, r, u << 1 | 1);
}

void pushdown(int u){
	if (tr[u].tag){
		auto &l = tr[u << 1], &r = tr[u << 1 | 1];
		l.tag = l.v = r.tag = r.v = tr[u].tag;
		tr[u].tag = 0;
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
	return query(k, u << 1 | 1);

}

signed main(){
	cin.tie(0)->sync_with_stdio(0);
	int n;
	while (~scanf("%d", &n)){

		memset(st, 0, sizeof st);
		for (int i = 0; i < n; ++ i) {
			scanf("%d %d %d", &q[i].l, &q[i].r, &q[i].c);
			colors.push_back( ++ q[i].c);
			nums.push_back( ++ q[i].l), nums.push_back(q[i].r);
			nums.push_back(q[i].l - 1), nums.push_back(q[i].r + 1);
		}

		sort(all(nums));
		nums.erase(unique(all(nums)), nums.end());

		sort(all(colors));
		colors.erase(unique(all(colors)), colors.end());

		build(0, nums.size() - 1);

		for (int i = 0; i < n; ++ i) modify(get(q[i].l), get(q[i].r), q[i].c);
		
		++ st[query(0)];
		// printf("%d ", query(0));
		for (int i = 1, j = 0; i < nums.size(); ++ i){
			int ci = query(i), cj = query(j);
			// printf("%d ", ci);
			if (ci != cj) ++ st[ci], j = i;
		}
		for (int i = 0; i < colors.size(); ++ i) 
			if (st[colors[i]]) 
				printf("%d %d\n", colors[i] - 1, st[colors[i]]);

		puts("");
	}
  return 0;
}
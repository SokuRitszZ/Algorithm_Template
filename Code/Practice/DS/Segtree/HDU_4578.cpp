#include <iostream>
#include <cstring>

#define CT const 
#define IL inline
#define endl '\n'
#define all(x) x.begin(), x.end()
#define MULTICASE() int _, kase; for (cin >> _, kase = 0; kase ++ , _ --;)

using namespace std;

typedef long long i6;

const int N = 1e5 + 10, MOD = 10007;

struct Node{
	int l, r, len;
	int sum[3];
	int tg_add, tg_mul, tg_sm;

	void init(int _l, int _r){
		l = _l, r = _r;
		len = r - l + 1;
		sum[0] = sum[1] = sum[2] = 0;
		tg_add = 0, tg_mul = 1, tg_sm = 0;
	}
}tr[N << 2];

IL int sq(int x){return x * x % MOD; }

IL int cb(int x){return x * x % MOD * x % MOD; }

void push_add(int u, int x){
	(tr[u].sum[2] += 3 * sq(x) * tr[u].sum[0] + 3 * x * tr[u].sum[1] + tr[u].len * cb(x)) %= MOD;
	(tr[u].sum[1] += 2 * x * tr[u].sum[0] + tr[u].len * sq(x)) %= MOD;
	(tr[u].sum[0] += tr[u].len * x) %= MOD;
	(tr[u].tg_add += x) %= MOD;
}

void push_mul(int u, int x){
	(tr[u].sum[2] *= cb(x)) %= MOD;
	(tr[u].sum[1] *= sq(x)) %= MOD;
	(tr[u].sum[0] *= x) %= MOD;

	(tr[u].tg_mul *= x) %= MOD;	
	(tr[u].tg_add *= x) %= MOD;
}

void push_sm(int u, int x){
	tr[u].sum[2] = cb(x) * tr[u].len % MOD;
	tr[u].sum[1] = sq(x) * tr[u].len % MOD;
	tr[u].sum[0] = x * tr[u].len % MOD;

	tr[u].tg_add = 0, tr[u].tg_mul = 1;
	tr[u].tg_sm = x;
}

void pushup(int u){
	for (int i = 0; i < 3; ++ i) 
		tr[u].sum[i] = (tr[u << 1].sum[i] + tr[u << 1 | 1].sum[i]) % MOD;
}

void pushdown(int u){
	if (tr[u].tg_sm){
		push_sm(u << 1, tr[u].tg_sm), push_sm(u << 1 | 1, tr[u].tg_sm);
		tr[u].tg_sm = 0;
	}
	if (tr[u].tg_mul != 1){
		push_mul(u << 1, tr[u].tg_mul), push_mul(u << 1 | 1, tr[u].tg_mul);
		tr[u].tg_mul = 1;
	}
	if (tr[u].tg_add){
		push_add(u << 1, tr[u].tg_add), push_add(u << 1 | 1, tr[u].tg_add);
		tr[u].tg_add = 0;
	}
}

void build(int l, int r, int u = 1){
	tr[u].init(l, r);
	if (l == r) return ;

	int mid = l + r >> 1;
	build(l, mid, u << 1), build(mid + 1, r, u << 1 | 1);

	pushup(u);
}

void modify_add(int l, int r, int x, int u = 1){
	if (l <= tr[u].l && tr[u].r <= r) {
		push_add(u, x);
		return ;
	}

	pushdown(u);

	int mid = tr[u].l + tr[u].r >> 1;
	if (l <= mid) modify_add(l, r, x, u << 1);
	if (mid < r) modify_add(l, r, x, u << 1 | 1);

	pushup(u);
}

void modify_mul(int l, int r, int x, int u = 1){
	if (l <= tr[u].l && tr[u].r <= r){
		push_mul(u, x);
		return ;
	}

	pushdown(u);

	int mid = tr[u].l + tr[u].r >> 1;
	if (l <= mid) modify_mul(l, r, x, u << 1);
	if (mid < r) modify_mul(l, r, x, u << 1 | 1);

	pushup(u);
}

void modify_sm(int l, int r, int x, int u = 1){
	if (l <= tr[u].l && tr[u].r <= r){
		push_sm(u, x);
		return ;
	}

	pushdown(u);

	int mid = tr[u].l + tr[u].r >> 1;
	if (l <= mid) modify_sm(l, r, x, u << 1);
	if (mid < r) modify_sm(l, r, x, u << 1 | 1);

	pushup(u);
}

int query(int l, int r, int x, int u = 1){
	if (l <= tr[u].l && tr[u].r <= r)
		return tr[u].sum[x];

	pushdown(u);

	int mid = tr[u].l + tr[u].r >> 1, res = 0;
	if (l <= mid) (res += query(l, r, x, u << 1)) %= MOD;
	if (mid < r) (res += query(l, r, x, u << 1 | 1)) %= MOD;

	return res;
}

signed main(){
	cin.tie(0)->sync_with_stdio(0);
	int n, m;
	while (scanf("%d %d", &n, &m), n || m){
		build(1, n);

		while (m -- ){
			int op, l, r, x; scanf("%d %d %d %d", &op, &l, &r, &x);

			if (op == 1)
				modify_add(l, r, x);
			else if (op == 2)
				modify_mul(l, r, x);
			else if (op == 3)
				modify_sm(l, r, x);
			else 
				printf("%d\n", query(l, r, x - 1));

			// printf("-----\n");
			// for (int i = 0; i < 3; ++ i){
			// 	for (int j = 1; j <= n; ++ j)
			// 		printf("%d ", query(j, j, i));
			// 	puts("");
			// }
			// printf("-----\n");
		}
	}

  return 0;
}
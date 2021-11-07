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

const int N = 5e5 + 10, INF = 1e9;

struct Node{
	int s[2], f;
	int v, size, ms, ls, rs, sum;
	int same, rev;
	void init(int _v, int _f){
		v = _v, f = _f, s[0] = s[1] = 0;
		size = 1;
		ms = sum = v;
		same = rev = 0;
		ls = rs = max(v, 0);
	}
}tr[N];

int bin[N], tt;
int w[N];

IL void pushup(int u){
	auto &l = tr[tr[u].s[0]], &r = tr[tr[u].s[1]];
	tr[u].size = l.size + r.size + 1;
	tr[u].sum = l.sum + r.sum + tr[u].v;
	tr[u].ls = max(l.ls, l.sum + tr[u].v + r.ls);
	tr[u].rs = max(r.rs, r.sum + tr[u].v + l.rs);
	tr[u].ms = max(max(l.ms, r.ms), l.rs + r.ls + tr[u].v);
}

IL void pushdown(int u){
	auto &l = tr[tr[u].s[0]], &r = tr[tr[u].s[1]];
	if (tr[u].same){
		tr[u].same = tr[u].rev = 0;
		if (tr[u].s[0]){
		 	l.same = 1;
		 	l.v = tr[u].v;
			l.sum = l.v * l.size;
			l.ls = l.rs = max(0, l.sum);
			l.ms = max(l.v, l.sum);
		}
		if (tr[u].s[1]){
			r.same = 1;
			r.v = tr[u].v;
			r.sum = r.v * r.size;
			r.ls = r.rs = max(0, r.sum);
			r.ms = max(r.v, r.sum);
		}
	}else if(tr[u].rev){
		tr[u].rev = 0;
		l.rev ^= 1, r.rev ^= 1;
		swap(l.s[0], l.s[1]), swap(r.s[0], r.s[1]);
		swap(l.ls, l.rs), swap(r.ls, r.rs);
	}
}

IL void rotate(int x){
	int y = tr[x].f, z = tr[y].f;
	int p = tr[y].s[1] == x, c = tr[x].s[p xor 1];
	tr[z].s[tr[z].s[1] == y] = x, tr[x].f = z;
	tr[x].s[p xor 1] = y, tr[y].f = x;
	tr[y].s[p] = c, tr[c].f = y;
	pushup(y), pushup(x);
}

int root;

IL void splay(int x, int f){
	while (tr[x].f xor f){
		int y = tr[x].f, z = tr[y].f;
		if (z xor f) 
			(tr[y].s[1] == x) xor (tr[z].s[1] == y) ? rotate(x) : rotate(y);
		rotate(x);
	}

	if (!f) root = x;
}

IL int kth(int k){
	int u = root;
	while (u){
		pushdown(u);
		int left = tr[tr[u].s[0]].size;
		if (left + 1 == k) return u;
		if (k <= left) u = tr[u].s[0];
		else u = tr[u].s[1], k -= left + 1;
	}
	return -1;
}

void find(int &l, int &r){
	l = kth(l), r = kth(r);
	splay(l, 0), splay(r, l);
}

int build(int l, int r, int p = 0){
	int mid = l + r >> 1;
	int u = bin[tt -- ];
	tr[u].init(w[mid], p);
	if (l < mid) tr[u].s[0] = build(l, mid - 1, u);
	if (mid < r) tr[u].s[1] = build(mid + 1, r, u);
	pushup(u);
	return u;
}

void dfs(int u){
	if (!u) return;
	bin[ ++ tt] = u;
	dfs(tr[u].s[0]), dfs(tr[u].s[1]);
}

int n, m;

signed main(){
	cin.tie(0)->sync_with_stdio(0);
  // ----
  for (int i = 1; i < N; ++ i) bin[ ++ tt] = i;

	cin >> n >> m;
	tr[0].ms = w[0] = w[n + 1] = -INF;
	for (int i = 1; i <= n; ++ i) cin >> w[i];

	root = build(0, n + 1);
	
	while (m -- ){
		string op; cin >> op;
		if (op == "INSERT"){
			int pos, tot; cin >> pos >> tot;
			for (int i = 1; i <= tot; i ++ ) cin >> w[i];
			int t = build(1, tot), l = pos + 1, r = pos + 2;
			find(l, r);
			tr[r].s[0] = t;
			tr[t].f = r;
			pushup(r), pushup(l);
		}else if (op == "DELETE"){
			int pos, tot; cin >> pos >> tot;
			int l = pos, r = pos + tot + 1;
			find(l, r);
			dfs(tr[r].s[0]);
			tr[r].s[0] = 0;
			pushup(r), pushup(l);
		}else if (op == "MAKE-SAME"){
			int pos, tot, c; cin >> pos >> tot >> c;
			int l = pos, r = pos + 1 + tot;
			find(l, r);	
			auto &u = tr[tr[r].s[0]];
			u.v = c, u.same = 1;
			u.sum = c * u.size;
			u.ls = u.rs = max(0, u.sum);
			u.ms = max(u.v, u.sum);
			pushup(r), pushup(l);
		}else if (op == "REVERSE"){
			int pos, tot; cin >> pos >> tot;
			int l = pos, r = pos + 1 + tot;
			find(l, r);
			auto &u = tr[tr[r].s[0]];
			u.rev ^= 1;
			swap(u.s[0], u.s[1]), swap(u.ls, u.rs);	
			pushup(r), pushup(l);
		}else if (op == "GET-SUM"){
			int pos, tot; cin >> pos >> tot;
			int l = pos, r = pos + 1 + tot;
			find(l, r);
			cout << tr[tr[r].s[0]].sum << endl;
		}else {
			cout << tr[root].ms << endl;
		}
	}	
  // ---- 
  return 0;
}
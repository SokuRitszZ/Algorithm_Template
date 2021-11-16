#include <bits/stdc++.h>

#define CT const 
#define IL inline
#define endl '\n'
#define all(x) x.begin(), x.end()
#define MULTICASE() int _, kase; for (cin >> _, kase = 0; kase ++ , _ --;)

using namespace std;

typedef long long i6;

inline int read(){
  int x = 0, flg = 1; char ch = getchar();
  if (ch == '-')  flg = -1;
  while (ch < '0' or ch > '9') ch = getchar();
  while ('0' <= ch and ch <= '9') x = (x << 3) + (x << 1) + (ch ^ 48), ch = getchar();
  return x * flg;
}

CT int N = 15e4 + 10, INF = 1e8;

struct Edge{
	int x, y, a, b;
	bool operator < (CT Edge &rhs) CT{return a < rhs.a; }
}e[N];

struct Node{
	int s[2], f, v;
	int mx, rev;
}tr[N];

int stk[N], p[N];
int n, m;

int find(int x){return x == p[x] ? x : p[x] = find(p[x]); }

void pushrev(int u){
	swap(tr[u].s[0], tr[u].s[1]);
	tr[u].rev ^= 1;
}

void pushup(int x){
	tr[x].mx = x;
	for (int i = 0; i < 2; ++ i)
		if (tr[tr[tr[x].s[i]].mx].v > tr[tr[x].mx].v)
			tr[x].mx = tr[tr[x].s[i]].mx;
}

void pushdown(int x){
	if (tr[x].rev){
		pushrev(tr[x].s[0]), pushrev(tr[x].s[1]);
		tr[x].rev = 0;
	}
}

bool is_root(int x){
	return tr[tr[x].f].s[0] != x and tr[tr[x].f].s[1] != x;
}

void rotate(int x){
	int y = tr[x].f, z = tr[y].f;
	int p = tr[y].s[1] == x, c = tr[x].s[p xor 1];

	if (!is_root(y)) tr[z].s[tr[z].s[1] == y] = x;
	tr[x].f = z;
	tr[x].s[p xor 1] = y, tr[y].f = x;
	tr[y].s[p] = c, tr[c].f = y;
	pushup(y), pushup(x);
}

void splay(int x){
	int top = 0, r = x;
	stk[ ++ top] = r;
	while (!is_root(r)) stk[ ++ top] = r = tr[r].f;
	while (top) pushdown(stk[top -- ]);

	while (!is_root(x)){
		int y = tr[x].f, z = tr[y].f;
		if (!is_root(y))
			(tr[y].s[1] == x) xor (tr[z].s[1] == y) ? rotate(x) : rotate(y);
		rotate(x);
	}	
}

void access(int x){
	int z = x;
	for (int y = 0; x; y = x, x = tr[x].f){
		splay(x);
		tr[x].s[1] = y, pushup(x);
	}
	splay(z);
}

void make_root(int x){
	access(x);
	pushrev(x);
}

int find_root(int x){
	access(x);
	while (tr[x].s[0]) pushdown(x), x = tr[x].s[0];

	splay(x);
	return x;
}

void split(int x, int y){
	make_root(x);
	access(y);
}

void link(int x, int y){
	make_root(x);
	if (find_root(y) != x) tr[x].f = y;
}

void cut(int x, int y){
	make_root(x);
	if (find_root(y) == x and tr[y].f == x and !tr[y].s[0]){
		tr[x].s[1] = tr[y].f = 0; pushup(x);
	}
}

signed main(){
	cin.tie(0)->sync_with_stdio(0);
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= m; ++ i){
		int x, y, a, b; scanf("%d %d %d %d", &x, &y, &a, &b);
		e[i] = {x, y, a, b};
	}

	sort(e + 1, e + 1 + m);

	for (int i = 1; i <= n + m; ++ i) {
		p[i] = i;
		if (i > n) tr[i].v = e[i - n].b;
		tr[i].mx = i;
	}
	
	int res = INF;	
	for (int i = 1; i <= m; ++ i){
		auto [x, y, a, b] = e[i];
		if (find(x) == find(y)){
			split(x, y);
			int t = tr[y].mx;
			if (tr[t].v > b){
				cut(e[t - n].x, t), cut(t, e[t - n].y);
				link(x, n + i), link(n + i, y);
			}
		}else{
			p[find(x)] = find(y);
			link(x, n + i), link(n + i, y);
		}

		if (find(1) == find(n)){
			split(1, n);
			res = min(res, tr[tr[n].mx].v + a);
		}
	}	

	if (res == INF) res = -1;
	printf("%d\n", res);


  return 0;
}
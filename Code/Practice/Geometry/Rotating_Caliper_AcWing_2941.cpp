#include <bits/stdc++.h>

#define CT const 
#define IL inline
#define endl '\n'
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

CT int N = 5e4 + 10;

struct Node{
	int x, y;
	Node operator + (CT Node &rhs) CT{return {x + rhs.x, y + rhs.y}; }
	Node operator - (CT Node &rhs) CT{return {x - rhs.x, y - rhs.y}; }
	int operator * (CT Node &rhs) CT{return x * rhs.y - y * rhs.x; }
	bool operator < (CT Node &rhs) CT{if (x != rhs.x) return x < rhs.x; return y < rhs.y; }
}p[N];

int n;
int stk[N], top;
bool st[N];

int area(CT Node &a, CT Node &b, CT Node &c){
	return (b - a) * (c - a);
}

void get_convex(){
	sort(p, p + n);
	for (int i = 0; i < n; ++ i) {
		while (top >= 2 and area(p[stk[top - 2]], p[stk[top - 1]], p[i]) <= 0){
			if (area(p[stk[top - 2]], p[stk[top - 1]], p[i]) < 0)
				st[stk[ -- top]] = 0;
			else -- top;
		}
		st[stk[top ++ ] = i] = 1;
	}
	st[0] = 0;
	for (int i = n - 1; i >= 0; -- i) {
		if (st[i]) continue;
		while (top >= 2 and area(p[stk[top - 2]], p[stk[top - 1]], p[i]) <= 0) 
			-- top;
		stk[top ++ ] = i;
	}

	-- top;
}

int get_dist(Node &a, Node &b){
	int dx = a.x - b.x, dy = a.y - b.y;
	return dx * dx + dy * dy;
}

int rotating_calipers(){
	int res = 0;
	if (top <= 2) return get_dist(p[0], p[n - 1]);
	for (int i = 0, j = 2; i < top; ++ i){
		auto d = p[stk[i]], e = p[stk[i + 1]];
		while (area(d, e, p[stk[j]]) < area(d, e, p[stk[j + 1]])) j = (j + 1) % top; 
		res = max(res, max(get_dist(d, p[stk[j]]), get_dist(e, p[stk[j]])));
	}

	return res;
}

signed main(){
	cin.tie(0)->sync_with_stdio(0);

	scanf("%d", &n);	
	for (int i = 0; i < n; ++ i) scanf("%d %d", &p[i].x, &p[i].y);
	get_convex();
	
	printf("%d\n", rotating_calipers());
  return 0;
}
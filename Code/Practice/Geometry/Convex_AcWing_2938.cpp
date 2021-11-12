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

CT int N = 4e4 + 10;
CT double pi = acos(-1);

struct Node{
	double x, y;
	bool operator < (CT Node &rhs) CT{
		if (x != rhs.x) return x < rhs.x;
		return y < rhs.y;
	}
}p[N];

int n, cnt;

Node rotate(Node a, double b){
	return {a.x * cos(b) + a.y * sin(b), -a.x * sin(b) + a.y * cos(b)};
}

Node operator - (CT Node &a, CT Node &b){
	return {a.x - b.x, a.y - b.y};
}

double cross(Node a, Node b){
	return a.x * b.y - a.y * b.x;
}

double area(Node a, Node b, Node c){
	return cross(b - a, c - a);
}

double get_dist(Node a, Node b){
	double dx = a.x - b.x, dy = a.y - b.y;

	return sqrt(dx * dx + dy * dy);
}

int stk[N];
bool st[N];

double andrew(){
	sort(p + 1, p + 1 + cnt);

	int top = 0;
	for (int i = 1; i <= cnt; ++ i){
		while (top >= 2 and area(p[stk[top - 1]], p[stk[top]], p[i]) >= 0) 	
			st[stk[top -- ]] = 0;
		st[stk[ ++ top] = i] = 1;
	}

	st[1] = 0;

	for (int i = cnt; i; -- i){
		if (st[i]) continue;
		while (top >= 2 and area(p[stk[top - 1]], p[stk[top]], p[i]) >= 0) 
			-- top;
		stk[ ++ top] = i;
	}

	double res = 0.00;
	for (int i = 1; i < top; ++ i) res += get_dist(p[stk[i]], p[stk[i + 1]]);

	return res;
}

signed main(){
	cin.tie(0)->sync_with_stdio(0);
	scanf("%d", &n);

	double a, b, r; scanf("%lf %lf %lf", &a, &b, &r);

	a = a / 2 - r, b = b / 2 - r;
	
	int dx[]{1, -1, 1, -1}, dy[]{1, 1, -1, -1};

	for (int i = 1; i <= n; ++ i){
		double x, y, z; scanf("%lf %lf %lf", &x, &y, &z);

		for (int i = 0; i < 4; ++ i){
			auto t = rotate({dx[i] * b, dy[i] * a}, -z);
			p[ ++ cnt] = {x + t.x, y + t.y};
		}
	}

	printf("%.2lf", andrew() + 2 * pi * r);
  return 0;
}


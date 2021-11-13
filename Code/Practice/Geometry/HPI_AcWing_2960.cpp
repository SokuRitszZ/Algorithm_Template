#include <bits/stdc++.h>

#define CT const 
#define IL inline
#define endl '\n'
#define MULTICASE() int _, kase; for (cin >> _, kase = 0; kase ++ , _ --;)

#define double long double

using namespace std;

typedef long long i6;

inline int read(){
  int x = 0, flg = 1; char ch = getchar();
  if (ch == '-')  flg = -1;
  while (ch < '0' or ch > '9') ch = getchar();
  while ('0' <= ch and ch <= '9') x = (x << 3) + (x << 1) + (ch ^ 48), ch = getchar();
  return x * flg;
}

CT int N = 1e4 + 10;
CT double eps = 1e-18;

struct Node{
	double x, y;
	Node operator + (CT Node &rhs) CT{return {x + rhs.x, y + rhs.y}; }
	Node operator - (CT Node &rhs) CT{return {x - rhs.x, y - rhs.y}; }
	Node operator * (CT double &t) CT{return {x * t, y * t}; }
	double operator * (CT Node &rhs) CT{return x * rhs.y - y * rhs.x; }
	bool operator < (CT Node &rhs) CT{
		if (x != rhs.x) return x < rhs.x;
		return y < rhs.y;
	}
};

struct Line{
	Node st, ed;
	vector<int> ids;
}line[N];

int dcmp(double a, double b){
	if (fabs(a - b) < eps) return 0;
	if (a < b) return -1; return 1;
}

int sign(double x){
	if (fabs(x) < eps) return 0;
	if (x < 0) return -1; return 1;
}

double area(Node &a, Node &b, Node &c){return (b - a) * (c - a); }

double get_angle(Line &a){return atan2(a.ed.y - a.st.y, a.ed.x - a.st.x); }

bool operator < (Line &a, Line &b){
	double A = get_angle(a), B = get_angle(b);
	if (!dcmp(A, B)) return area(a.st, a.ed, b.ed) < 0; return A < B;
}

Node get_line_intersection(Node p, Node v, Node q, Node w){
	auto u = q - p; double t = (u * w) / (v * w);
	return p + v * t;
}

Node get_line_intersection(Line &a, Line &b){
	return get_line_intersection(a.st, a.ed - a.st, b.st, b.ed - b.st);
}

bool on_right(Line &a, Line &b, Line &c){
	auto o = get_line_intersection(b, c);
	return area(a.st, a.ed, o) < 0;
}

int cnt, q[N];
int ans[N];

void hpi(){
	sort(line, line + cnt);

	int hh = 0, tt = -1;

	for (int i = 0; i < cnt; ++ i) {
		if (i and !dcmp(get_angle(line[i - 1]), get_angle(line[i]))) continue;
		while (hh + 1 <= tt and on_right(line[i], line[q[tt - 1]], line[q[tt]])) -- tt;
		while (hh + 1 <= tt and on_right(line[i], line[q[hh]], line[q[hh + 1]])) ++ hh;
		q[ ++ tt] = i;
	}
	while (hh + 1 <= tt and on_right(line[q[hh]], line[q[tt - 1]], line[q[tt]])) -- tt;
	while (hh + 1 <= tt and on_right(line[q[tt]], line[q[hh]], line[q[hh + 1]])) ++ hh;

	int k = 0;
	for (int i = hh; i <= tt; ++ i) 
		for (auto id : line[q[i]].ids) 
			ans[k ++ ] = id;

	sort(ans, ans + k);

	printf("%d\n", k);
	for (int i = 0; i < k; ++ i) printf("%d ", ans[i]);
	puts("");	
}

int ki[N], vi[N];
int n;

signed main(){
	cin.tie(0)->sync_with_stdio(0);
	map<Node, vector<int> > ids;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++ i) scanf("%d", &ki[i]);
	for (int i = 1; i <= n; ++ i) scanf("%d", &vi[i]);
	for (int i = 1; i <= n; ++ i) ids[{ki[i], vi[i]}].push_back(i);

	line[cnt ++ ] = {{0, 10000}, {0, 0}};
	line[cnt ++ ] = {{0, 0}, {10000, 0}};
	for (auto& [k, v] : ids)
		line[cnt ++ ] = {{0, k.x}, {1, k.x + k.y}, v};
	
	hpi();	
  return 0;
}
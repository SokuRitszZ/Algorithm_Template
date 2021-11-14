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

CT int N = 1e5 + 10;
CT double eps = 1e-12, pi = acos(-1);

struct Node{
	double x, y;
	Node operator + (CT Node &rhs) CT{return {x + rhs.x, y + rhs.y}; }
	Node operator - (CT Node &rhs) CT{return {x - rhs.x, y - rhs.y}; }
	Node operator * (CT double &t) CT{return {x * t, y * t}; }
	Node operator / (CT double &t) CT{return {x / t, y / t}; }
	double operator * (CT Node &rhs) CT{return x * rhs.y - y * rhs.x; }
	bool operator < (CT Node &rhs) CT{if (x != rhs.x) return x < rhs.x; return y < rhs.y; }
}q[N];

struct Line{
	Node p, v;
};

struct Circle{
	Node o;
	double r;
};

int sign(double x){
	if (fabs(x) < eps) return 0;
	if (x < 0) return -1; return 1;
}

int dcmp(double a, double b){
	if (fabs(a - b) < eps) return 0;
	if (a < b) return -1; return 1;
}

Node get_line_intersection(Node p, Node v, Node q, Node w){
	auto u = q - p; double t = (u * w) / (v * w);
	return p + v * t;
}

Node get_line_intersection(CT Line &a, CT Line &b){
	return get_line_intersection(a.p, a.v, b.p, b.v);
}

Node rotate(Node a, double b){return {a.x * cos(b) + a.y * sin(b), -a.x * sin(b) + a.y * cos(b)}; }

double get_dist(Node a, Node b){
	double dx = a.x - b.x, dy = a.y - b.y;
	return sqrt(dx * dx + dy * dy);
}

Line get_line(Node a, Node b){
	return {(a + b) / 2, rotate(b - a, pi / 2)};
}

Circle get_circle(Node a, Node b, Node c){
	auto p = get_line_intersection(get_line(a, b), get_line(a, c));
	return {p, get_dist(p, a)};
}

int n;

signed main(){
	cin.tie(0)->sync_with_stdio(0);

	scanf("%d", &n);
	for (int i = 0; i < n; ++ i) scanf("%lf %lf", &q[i].x, &q[i].y);

	random_shuffle(q, q + n);

	Circle c({q[0], 0});

	for (int i = 1; i < n; ++ i) 
		if (dcmp(c.r, get_dist(c.o, q[i])) < 0){
			c = {q[i], 0};
			for (int j = 0; j < i; ++ j)
				if (dcmp(c.r, get_dist(c.o, q[j])) < 0){
					c = {(q[i] + q[j]) / 2, get_dist(q[i], q[j]) / 2};
					for (int k = 0; k < j; ++ k)
						if (dcmp(c.r, get_dist(c.o, q[k])) < 0)
							c = get_circle(q[i], q[j], q[k]);
				}
		}

	printf("%.10lf\n", c.r);
	printf("%.10lf %.10lf\n", c.o.x, c.o.y);

  return 0;
}
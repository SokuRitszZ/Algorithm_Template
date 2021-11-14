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
CT double eps = 1e-5, pi = acos(-1);

struct Node{
	double x, y;

	Node operator + (CT Node &rhs) CT{return {x + rhs.x, y + rhs.y}; }
	Node operator - (CT Node &rhs) CT{return {x - rhs.x, y - rhs.y}; }
	Node operator * (CT double &t) CT{return {x * t, y * t}; }
	Node operator / (CT double &t) CT{return {x / t, y / t}; }
	double operator * (CT Node &rhs) CT{return x * rhs.y - y * rhs.x; }

}p[N];

struct Line{
	Node p, v;
};

struct Circle{
	Node o;
	double r;

	Circle(CT Node &_o, CT double &_r): o(_o), r(_r){}
};

int dcmp(double x, double y){
	if (fabs(x - y) < eps) return 0;
	if (x < y) return -1; return 1;
}

double get_dist(CT Node &a, CT Node &b){
	double dx = a.x - b.x, dy = a.y - b.y;
	return sqrt(dx * dx + dy * dy);
}

Node get_line_intersection(Node p, Node v, Node q, Node w){
	auto u = q - p; double t = (u * w) / (v * w);
	return p + v * t;
}

Node get_line_intersection(CT Line &a, CT Line &b){
	return get_line_intersection(a.p, a.v, b.p, b.v);
}

Node rotate(Node v, double theta){
	return {v.x * cos(theta) + v.y * sin(theta), -v.x * sin(theta) + v.y * cos(theta)};
}

Line get_line(Node a, Node b){
	return {(a + b) / 2, rotate(b - a, pi / 2)};
}

Circle get_circle(Node a, Node b, Node c){
	auto O = get_line_intersection(get_line(a, b), get_line(a, c));
	return {O, get_dist(O, a)};
}

signed main(){
	cin.tie(0)->sync_with_stdio(0);

	int n; scanf("%d", &n);

	for (int i = 0; i < n; ++ i) scanf("%lf %lf", &p[i].x, &p[i].y);

	double power, theta; scanf("%lf %lf", &theta, &power);

	for (int i = 0; i < n; ++ i){
		p[i] = rotate(p[i], theta / 180 * pi);
		p[i].x /= power;
	}

	random_shuffle(p, p + n);

	Circle c(p[0], 0);

	for (int i = 1; i < n; ++ i)
		if (dcmp(c.r, get_dist(c.o, p[i])) < 0){
			c = {p[i], 0};
			for (int j = 0; j < i; ++ j)
				if (dcmp(c.r, get_dist(c.o, p[j])) < 0){
					c = {(p[i] + p[j]) / 2, get_dist(p[i], p[j]) / 2};
					for (int k = 0; k < j; ++ k)
						if (dcmp(c.r, get_dist(c.o, p[k])) < 0)
							c = get_circle(p[i], p[j], p[k]);
				}
		}

	printf("%.3lf", c.r);
	return 0;
}
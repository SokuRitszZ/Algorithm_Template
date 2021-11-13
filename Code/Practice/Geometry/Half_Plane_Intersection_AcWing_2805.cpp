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

CT int N = 510;
CT double eps = 1e-8;

struct Node{
	double x, y;

	Node operator + (CT Node &rhs) CT{
		return {x + rhs.x, y + rhs.y};
	}

	Node operator - (CT Node &rhs) CT{
		return {x - rhs.x, y - rhs.y};
	}

	Node operator * (double t) CT{
		return {x * t, y * t};
	}

	double operator * (CT Node &rhs){
		return x * rhs.y - y * rhs.x;
	}

}p[N], ans[N];

struct Line{
	Node st, ed;
}line[N];

int n, cnt;
int q[N];

int sign(double x){
	if (fabs(x) < eps) return 0;
	if (x < 0) return -1;
	return 1;
}

int dcmp(double x, double y){
	if (fabs(x - y) < eps) return 0;
	if (x < y) return -1;
	return 1;
}

double get_angle(CT Line &a){
	return atan2(a.ed.y - a.st.y, a.ed.x - a.st.x);
}

double area(Node a, Node b, Node c){
	return (b - a) * (c - a);
}

bool operator < (CT Line &a, CT Line &b){
	double A = get_angle(a), B = get_angle(b);
	if (!dcmp(A, B)) return area(a.st, a.ed, b.ed) < 0;
	return A < B;
}

Node get_line_intersection(Node p, Node v, Node q, Node w){
	Node u = q - p;
	double t = (u * w) / (v * w);
	return p + v * t;
}

Node get_line_intersection(Line a, Line b){
	return get_line_intersection(a.st, a.ed - a.st, b.st, b.ed - b.st);
}

bool on_right(Line &a, Line &b, Line &c){
	auto o = get_line_intersection(b, c);
	return sign(area(a.st, a.ed, o)) <= 0;
}

double hpi(){
	sort(line, line + cnt);
	int hh = 0, tt = -1;
	for (int i = 0; i < cnt; ++ i){
		if (i && !dcmp(get_angle(line[i]), get_angle(line[i - 1]))) continue;
		while (hh + 1 <= tt and on_right(line[i], line[q[tt - 1]], line[q[tt]])) -- tt;
		while (hh + 1 <= tt and on_right(line[i], line[q[hh]], line[q[hh + 1]])) ++ hh;
		q[ ++ tt] = i;
	}
	while (hh + 1 <= tt and on_right(line[q[hh]], line[q[tt - 1]], line[q[tt]])) -- tt;
	while (hh + 1 <= tt and on_right(line[q[tt]], line[q[hh]], line[q[hh + 1]])) ++ hh;

	q[ ++ tt] = q[hh];
	int k = 0;
	for (int i = hh; i < tt; ++ i)
		ans[k ++ ] = get_line_intersection(line[q[i]], line[q[i + 1]]);
	double res = 0;
	for (int i = 1; i + 1 < k; ++ i)
		res += area(ans[0], ans[i], ans[i + 1]);

	return res / 2;
}

signed main(){
	cin.tie(0)->sync_with_stdio(0);
	int t; scanf("%d", &t); while (t -- ){
		scanf("%d", &n);

		for (int i = 0; i < n; ++ i){
			double x, y; scanf("%lf %lf", &x, &y);
			p[i] = {x, y};
		}

		for (int i = 0; i < n; ++ i)
			line[cnt ++ ] = {p[i], p[(i + 1) % n]};
	}

	printf("%.3lf", hpi());
  return 0;
}
#include <bits/stdc++.h>

#define CT const 
#define IL inline
#define PB emplace_back
#define PP pop
#define FT front
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

CT int N = 110;
CT double eps = 1e-8;

struct Point{
	double x, y;
}p[N << 1];

int n;

int sign(double x){
	if (fabs(x) < eps) return 0;
	if (x < 0) return -1;
	return 1;
}

int cmp(double x, double y){
	if (fabs(x - y) < eps) return 0;
	if (x < y) return -1;
	return 1;
}

double cross(double x1, double y1, double x2, double y2){
	return x1 * y2 - x2 * y1;
}

double area(Point a, Point b, Point c){
	return cross(b.x - a.x, b.y - a.y, c.x - a.x, c.y - a.y);
}

bool check(){
	for (int i = 0; i < 2 * n; ++ i)
		for (int j = i + 1; j < 2 * n; ++ j){
			if (!cmp(p[i].x, p[j].x) and !cmp(p[i].y, p[j].y)) continue;
			bool flg = 1;
			for (int k = 0; k < n; ++ k)
				if (sign(area(p[k << 1], p[i], p[j])) * sign(area(p[k << 1 | 1], p[i], p[j])) > 0) {
					flg = 0;
					break;
				} 
			if (flg) return 1;
		}
	return 0;
}

signed main(){
	cin.tie(0)->sync_with_stdio(0);
	MULTICASE(){
		cin >> n;
		for (int i = 0, k = 0; i < n; ++ i)
			cin >> p[k].x >> p[k ++ ].y >> p[k].x >> p[k ++ ].y;

		if (check()) cout << "Yes!" << endl;
		else cout << "No!" << endl;

	}	
  return 0;
}
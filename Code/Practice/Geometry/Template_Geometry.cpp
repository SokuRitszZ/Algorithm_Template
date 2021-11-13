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

struct Vector{
	double x, y;

	Vector(double _x = 0, double _y): x(_x), y(_y){}

	Vector operator + (CT Vector &rhs) CT{
		return {this.x + rhs.x, this.y + rhs.y};
	}

	Vector operator - (CT Vector &rhs) CT{
		return {this.x - rhs.x, this.y - rhs.y};
	}

	Vector operator * (double t) CT{
		return {this.x * t, this.y * t};
	}

	double operator * (CT Vector &rhs) CT{
		return this.x * rhs.y - this.y * rhs.x;
	}

};

struct Line{
	Vector p, v;
	
	double get_angle() CT{
		return atan2(this.v.y, this.v.x);
	}	

	Vector get_line_intersection(CT Line &rhs) CT{
		Vector u = rhs.p - this.p;
		double t = (u * rhs.v) / (this.v * rhs.v);
		return this.p + this.v * t;
	}
};

signed main(){
	cin.tie(0)->sync_with_stdio(0);

  return 0;
}
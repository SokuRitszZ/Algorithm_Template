#include <bits/stdc++.h>

#define CT const 
#define IL inline
#define endl '\n'
#define x first
#define y second
#define MULTICASE() for (int _ = read(), kase = 0; kase ++ , _ --;)

using namespace std;

typedef long long i6;
typedef pair<i6, i6> pi6;

inline int read(){
  int x = 0, flg = 1; char ch = getchar();
  if (ch == '-')  flg = -1;
  while (ch < '0' or ch > '9') ch = getchar();
  while ('0' <= ch and ch <= '9') x = (x << 3) + (x << 1) + (ch ^ 48), ch = getchar();
  return x * flg;
}

CT int N = 5e3 + 10;

pi6 a[N], b[N];
int n, m;

i6 cross(i6 x1, i6 y1, i6 x2, i6 y2){
	return x1 * y2 - x2 * y1;
}

i6 area(pi6 a, pi6 b, pi6 c){
	return cross(b.x - a.x, b.y - a.y, c.x - a.x, c.y - a.y);
}

int find(i6 x, i6 y){
	int l = 0, r = n;
	while (l < r){
		int mid = l + r >> 1;
		if (area(b[mid], a[mid], {x, y}) > 0) r = mid;
		else l = mid + 1;
	}
	return r;
}

int ans[N];

signed main(){
	cin.tie(0)->sync_with_stdio(0);
	bool is_first = 1;
	while (cin >> n, n){
		i6 x1, y1, x2, y2; cin >> m >> x1 >> y1 >> x2 >> y2;
		for (int i = 0; i < n; ++ i){
			i6 u, l; cin >> u >> l;
			a[i] = {u, y1}, b[i] = {l, y2};	
			ans[i] = 0;
		}	

		a[n] = {x2, y1}, b[n] = {x2, y2}, ans[n] = 0;

		if (is_first) is_first = 0;
		else cout << endl;

		while (m -- ){
			i6 x, y; cin >> x >> y;
			++ ans[find(x, y)];
		}

		for (int i = 0; i <= n; ++ i)
			cout << i << ": " << ans[i] << endl;
	}	
  return 0;
}
#include <bits/stdc++.h>

using namespace std;
using cint = const int &;
using i64 = long long;

inline int read(){
	int x = 0, flg = 1; char ch = getchar();
	if (ch == '-')  flg = -1;
	while (ch < '0' or ch > '9') ch = getchar();
	while ('0' <= ch and ch <= '9') x = (x << 3) + (x << 1) + (ch ^ 48), ch = getchar();
	return x * flg;
}

signed main(){
#ifdef LOCAL
	freopen("in.in", "r", stdin);
	freopen("out.out", "w", stdout);
#endif 
	// ----
	for (int _ = read(); _ -- ;){
		i64 n = read();
		map<int, int> aa, bb;

		vector<int> sa(n), sb(n);

		for (int i = 0; i < n; i ++ ){
			int a = read(), b = read();
			aa[a] ++ , bb[b] ++ ;
			sa[i] = a, sb[i] = b;
		} 

		i64 ans = 1ll * n * (n - 1) * (n - 2) / 6;

		for (int i = 0; i < n; i ++ )
			ans -= 1ll * (aa[sa[i]] - 1) * (bb[sb[i]] - 1);

		cout << ans << endl;
	} 

	// ---- 
	return 0;
}

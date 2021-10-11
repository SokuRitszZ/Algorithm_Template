#include <bits/stdc++.h>

#define int long long

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
	cin.tie(0)->sync_with_stdio(0);

	int t = read();
	while (t -- ){
		int n = read();
		vector<int> a(n);
		int tot = 0;
		for (auto &it : a) tot += it = read();

		int tot2 = tot * (n - 2);
		tot *= n;

		sort(a.begin(), a.end());
		for (auto &it : a) it *= n;

		int res = 0, sum = tot - tot2;

		for (int i = 0; i < n - 1; i ++ ){
			int pos = lower_bound(a.begin() + i + 1, a.end(), sum - a[i]) - a.begin();
			int pos2 = upper_bound(a.begin() + i + 1, a.end(), sum - a[i]) - a.begin();
			if (a[pos] == sum - a[i]) res += pos2 - pos;
		}

		cout << res << endl;
	} 

	// ---- 
	return 0;
}

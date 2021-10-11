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
	int t = read();

	while (t -- ){
		int n = read();
		string s1, s2;
		cin >> s1 >> s2;

		bool flg = 1;
		for (int i = 0; i < n; i ++ ){
			if (s1[i] == '1' and s2[i] == '1'){
				puts("NO");
				flg = 0;
				break;
			}
		}

		if (flg) puts("YES");
	}

	// ---- 
	return 0;
}

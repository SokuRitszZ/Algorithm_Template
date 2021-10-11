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
		vector<int> st[5];

		for (int i = 0; i < n; i ++ )
			for (int j = 0; j < 5; j ++ )
				if (read()) st[j].push_back(i);

		bool flg = 0;
		for (int i = 0; i < 5; i ++ ){
			if (st[i].size() < n / 2) continue;
			for (int j = i + 1; j < 5; j ++ ){
				if (st[j].size() < n / 2) continue;

				vector<int> pd;
				for (int u : st[i]) pd.push_back(u);
				for (int u : st[j]) pd.push_back(u);

				sort(pd.begin(), pd.end());
				pd.erase(unique(pd.begin(), pd.end()), pd.end());

				if (pd.size() == n) flg = 1;
				if (flg) break;
			}
			if (flg) break;
		}

		if (flg) puts("YES");
		else puts("NO");
	}

	// ---- 
	return 0;
}

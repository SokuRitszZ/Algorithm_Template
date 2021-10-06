#include <bits/stdc++.h>

using namespace std;

inline int read(){
	int x, flg = 1; char ch = getchar();
	if (ch == '-') flg = -1;
	while (ch < '0' or ch > '9') ch = getchar();
	while ('0' <= ch and ch <= '9') x = (x << 3) + (x << 1) + (ch ^ 48), ch = getchar();
	return x * flg;
}

signed main(){
#ifdef LOCAL
	freopen("in.in", "r", stdin);
	freopen("out.out", "w", stdout);
#endif 
	// ---
	
	// --- 
	
	return 0;
}


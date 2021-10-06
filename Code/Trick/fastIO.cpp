#include <iostream>

inline int read(){ 
	int x, flg = 1; char ch = getchar();
	if (ch == '-') flg = -1;
	while (ch < '0' or ch > '9') ch = getchar();
	while ('0' <= ch and ch <= '9') x = (x << 3) + (x << 1) + (ch ^ 48), ch = getchar();
	return x * flg;
}
	

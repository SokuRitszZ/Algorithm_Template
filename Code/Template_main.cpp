#include <iostream>

//      Time: %$Time$% 
//    Author: %$Author$% 

#define all(x) x.begin(), x.end()
#define MULTICASE() int sokuritszz, kase; for (std::cin >> sokuritszz, kase = 0; kase ++ , sokuritszz --;)

typedef long long i6;
struct pii {int x, y; pii(int x = 0, int y = 0): x(x), y(y){}};
bool operator < (const pii &a, const pii &b){return a.x == b.x ? a.y < b.y : a.x < b.x;}

signed main()
{
  std::cin.tie(0)->sync_with_stdio(false);
  return 0;
}
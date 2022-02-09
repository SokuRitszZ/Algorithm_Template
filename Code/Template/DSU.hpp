#include <vector>
#include <numeric>

struct DSU
{
	std::vector<int> p, sz;
	DSU(int n): p(n), sz(n, 1)
	{
		std::iota(p.begin(), p.end(), 0);
	}
	int leader(int x)
	{
		return x == p[x] ? x : p[x] = leader(p[x]);
	}
	bool same(int x, int y)
	{
		return leader(x) == leader(y);
	}
	bool merge(int x, int y)
	{
		x = leader(x);
		y = leader(y);
		if (x == y) return 0;
		sz[x] += sz[y];
		p[y] = x;
		return 1;
	}
	int size(int x)
	{
		return sz[x];
	}
};
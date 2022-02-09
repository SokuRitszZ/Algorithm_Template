template <typename T>
struct Fenwick
{
	const int n;
	std::vector<T> a;
	Fenwick(int n): n(n), a(n){}
	void add(int x, T v)
	{
		for (int i = x + 1; i <= n; i += i & -i)
			a[i - 1] += v;
	}
	T sum(int x)
	{
		T res = 0;
		for (int i = x + 1; i > 0; i -= i & -i)
			res += a[i - 1];
		return res;
	}
	T sum(int l, int r)
	{
		-- l, -- r;
		return sum(r) - sum(l - 1);
	}
};

template<typename T>
struct ST
{
	const int n;
	std::vector<std::vector<T>> f;
	ST(std::vector<T> info): n(info.size()), f(std::__lg(n) + 1)
	{
		for (int i = 0; i < f.size(); ++i)
		{
			f[i].resize(n - i);
			for (int j = 0; j + (1 << i) - 1 < n; ++j)
				if (!i) f[i][j] = info[j];
				else f[i][j] = f[i - 1][j] + f[i - 1][j + (1 << i - 1)];
		}
	}
	T query(int l, int r)
	{
		int len = r - l + 1;
		len = std::__lg(len);
		return f[len][l] + f[len][r - (1 << len) + 1];
	}
};
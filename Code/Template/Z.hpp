const int P;

int norm(int x)
{
	if (x < 0) x += P;
	if (x >= P) x -= P;
	return x;
}

template<class T>
T power(T a, int b)
{
	T res = 1;
	for (; b; b >>= 1, a *= a)
		if (b & 1) res *= a;
	return res;
}

struct Z
{
	int x;
	Z(int x = 0): x(norm(x)){}
	int val() const{ return x; }
	Z operator-() const{ return Z(P - x);}
	Z inv() const { return power(*this, P - 2);}
	Z &operator*=(const Z &rhs)
	{
		x = 1ll * x * rhs.x % P;
		return *this;
	}
	Z &operator+=(const Z &rhs)
	{
		x = norm(x + rhs.x);
		return *this;
	}
	Z &operator-=(const Z &rhs)
	{
		x = norm(x - rhs.x);
		return *this;	
	}
	Z &operator/=(const Z &rhs)
	{
		return *this *= rhs.inv();
	}
	friend Z operator*(const Z &lhs, const Z &rhs)
	{
		Z res = lhs;
		res *= rhs;
		return res;
	}
	friend Z operator+(const Z &lhs, const Z &rhs)
	{
		Z res = lhs;
		res += rhs;
		return res;
	}
	friend Z operator-(const Z &lhs, const Z &rhs)
	{
		Z res = lhs;
		res -= rhs;
		return res;
	}
	friend Z operator/(const Z &lhs, const Z &rhs)
	{
		Z res = lhs;
		res /= rhs;
		return res;
	}
};

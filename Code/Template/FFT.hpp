struct cp
{
  double x, y;
  cp(double x = 0, double y = 0): x(x), y(y){}
  cp operator + (const cp& rhs) {return cp(x + rhs.x, y + rhs.y);}
  cp operator - (const cp& rhs) {return cp(x - rhs.x, y - rhs.y);}
  cp operator * (const cp& rhs) {return cp(x * rhs.x - y * rhs.y, x * rhs.y + y * rhs.x);}
};

void FFT(cp a[], int n, int inv)
{
  static cp t[N];

  if (n == 1) return ;

  int mid = n >> 1;

  for (int i = 0; i < mid; ++ i)
    t[i] = a[i << 1], t[i + mid] = a[i << 1 | 1];
  for (int i = 0; i < n; ++ i) a[i] = t[i];
  FFT(a, mid, inv), FFT(a + mid, mid, inv);

  for (int i = 0, j = mid; i < mid; ++ i, ++ j)
  {
    cp w(cos(2 * pi * i / n), inv * sin(2 * pi * i / n));
    t[i] = a[i] + w * a[j];
    t[j] = a[i] - w * a[j];
  }
  for (int i = 0; i < n; ++ i) a[i] = t[i];
}

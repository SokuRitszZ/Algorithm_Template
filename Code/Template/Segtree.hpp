#include <vector>
#include <functional>

template<typename T, typename T2>
struct Segtree
{
  const int n;
  std::vector<T> tr;
  std::vector<T2> tag;
  Segtree(int n): n(n), tr((n << 2) + 1), tag((n << 2) + 1){}
  Segtree(std::vector<T> info): n(info.size()), tr((n << 2) + 1), tag((n << 2) + 1)
  {
    std::function<void(int, int, int)> build = [&](int l, int r, int u)
    {
      tr[u] = info[l - 1];
      if (l == r) return ;
      int mid = l + r >> 1;
      build(l, mid, u << 1), build(mid + 1, r, u << 1 | 1);
      pushup(u);
    };
    build(1, n, 1);
  }
  void pushup(int u)
  {
    tr[u] = tr[u << 1] + tr[u << 1 | 1];
  }
  void modify(int l, int r, int L, int R, const T2 &c, int u = 1)
  {
    if (L <= l && r <= R) return tag[u] = tag[u] + c, tr[u] = tr[u] + c, void();
    if (R < l || r < L) return ;
    int mid = l + r >> 1;
    tag[u](tr[u << 1], tr[u << 1 | 1], tag[u << 1], tag[u << 1 | 1]);
    modify(l, mid, L, R, c, u << 1), modify(mid + 1, r, L, R, c, u << 1 | 1);
    pushup(u);
  }
  void modify(int L, int R, const T2 &c)
  {
    modify(1, n, L, R, c);
  }
  T query(int l, int r, int L, int R, int u = 1)
  {
    if (L <= l && r <= R) return tr[u];
    if (R < l || r < L) return T();
    tag[u](tr[u << 1], tr[u << 1 | 1], tag[u << 1], tag[u << 1 | 1]);
    int mid = l + r >> 1;
    return query(l, mid, L, R, u << 1) + query(mid + 1, r, L, R, u << 1 | 1);
  }
  T query(int L, int R, int u = 1)
  {
    return query(1, n, L, R);
  }
};

struct Tag;

struct Info
{
  // Node infomation
  friend Info operator+(const Info&, const Info&);
};

struct Tag
{
  // Tag infomation
  void operator()(Info &x, Info &y, Tag &a, Tag &b)
  {
    x = x + *this;
    y = y + *this;
    a = a + *this;
    b = b + *this;
    *this = Tag();
  }
  friend Info operator+(const Info&, const Tag&);
  friend Tag operator+(const Tag&, const Tag&);
};

Info operator+(const Info &x, const Info &y)
{
  // Push up Info + Info
}

Info operator+(const Info &x, const Tag &tag)
{
  // Modify Info + Tag
}

Tag operator+(const Tag &x, const Tag &y)
{
  // Push down Tag + Tag
}
struct line {
  mutable int m, b, p;
  bool operator<(const line &o) const {
    if (m != o.m) return m < o.m;
    return b < o.b;
  }
  bool operator<(const int x) const { return p < x; }
  int eval(int x) const { return m * x + b; }
  int inter(const line &o) const {
    int x = b - o.b, y = o.m - m;
    return (x / y) - ((x ^ y) < 0 && x % y);
  }
};
struct cht {
  int INF = 1e18;
  multiset<line, less<>> l;
  void add(int m, int b) {
    auto y = l.insert({m, b, INF});
    auto z = next(y);
    if (z != l.end() && y->m == z->m) {
      l.erase(y);
      return;
    }
    if (y != l.begin()) {
      auto x = prev(y);
      if (x->m == y->m) x = l.erase(x);
    }
    while (1) {
      if (z == l.end()) {
        y->p = INF;
        break;
      }
      y->p = y->inter(*z);
      if (y->p < z->p)
        break;
      else
        z = l.erase(z);
    }
    if (y == l.begin()) return;
    z = y;
    auto x = --y;
    while (1) {
      int ninter = x->inter(*z);
      if (ninter <= x->p)
        x->p = ninter;
      else {
        l.erase(z);
        break;
      }
      if (x == l.begin()) break;
      y = x;
      x--;
      if (x->p < y->p)
        break;
      else
        l.erase(y);
    }
  }
  int get(int x) {
    if (l.empty()) return 0;
    return l.lower_bound(x)->eval(x);
  }
};
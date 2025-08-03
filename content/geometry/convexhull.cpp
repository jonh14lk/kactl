struct point {
  int x, y, id;
  point(int x, int y, int id) : x(x), y(y), id(id) {}
  point() {}
  point operator-(point const &o) const { return {x - o.x, y - o.y, -1}; }
  bool operator<(point const &o) const {
    if (x == o.x) return y < o.y;
    return x < o.x;
  }
  int operator^(point const &o) const { return x * o.y - y * o.x; }
};
int ccw(point const &a, point const &b, point const &x) {
  auto p = (b - a) ^ (x - a);
  return (p > 0) - (p < 0);
}
vector<point> convex_hull(vector<point> P)  // sem colineares
{
  sort(P.begin(), P.end());
  vector<point> L, U;
  for (auto p : P) {
    while (L.size() >= 2 && ccw(L.end()[-2], L.end()[-1], p) == -1) L.pop_back();
    L.push_back(p);
  }
  reverse(P.begin(), P.end());
  for (auto p : P) {
    while (U.size() >= 2 && ccw(U.end()[-2], U.end()[-1], p) == -1) U.pop_back();
    U.push_back(p);
  }
  L.insert(L.end(), U.begin(), U.end() - 1);
  return L;
}
vector<point> convex_hull_no_collinears(vector<point> P)  // com colineares
{
  sort(P.begin(), P.end());
  vector<point> L, U;
  for (auto p : P) {
    while (L.size() >= 2 && ccw(L.end()[-2], L.end()[-1], p) <= 0) L.pop_back();
    L.push_back(p);
  }
  reverse(P.begin(), P.end());
  for (auto p : P) {
    while (U.size() >= 2 && ccw(U.end()[-2], U.end()[-1], p) <= 0) U.pop_back();
    U.push_back(p);
  }
  L.insert(L.end(), U.begin(), U.end() - 1);
  return L;
}
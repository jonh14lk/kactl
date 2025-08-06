struct pt {
  int x, y, id;
  pt() {}
  pt(int xx, int yy) { x = xx, y = yy; }
  pt operator-(pt p) const { return pt(x - p.x, y - p.y); }
  bool operator<(pt p) const { return x < p.x; }
  int dist() const { return x * x + y * y; }
};
bool on_x(const pt &a, const pt &b) { return a.x < b.x; }
bool on_y(const pt &a, const pt &b) { return a.y < b.y; }
struct node {
  pt pp;
  int id;
  int x0 = inf, x1 = -inf, y0 = inf, y1 = -inf;
  node *first = 0, *second = 0;
  int distance(const pt &p) {
    int x = (p.x < x0 ? x0 : p.x > x1 ? x1 : p.x);
    int y = (p.y < y0 ? y0 : p.y > y1 ? y1 : p.y);
    return (pt(x, y) - p).dist();
  }
  node(vector<pt> &&vp) : pp(vp[0]) {
    for (pt p : vp) {
      x0 = min(x0, p.x);
      x1 = max(x1, p.x);
      y0 = min(y0, p.y);
      y1 = max(y1, p.y);
    }
    if (vp.size() > 1) {
      sort(vp.begin(), vp.end(), x1 - x0 >= y1 - y0 ? on_x : on_y);
      int half = vp.size() / 2;
      first = new node({vp.begin(), vp.begin() + half});
      second = new node({vp.begin() + half, vp.end()});
    }
  }
};
struct kd_tree {
  node *root;
  kd_tree(const vector<pt> &vp) : root(new node({vp.begin(), vp.end()})) {}
  pi search(node *n, const pt &p) {
    if (!n->first) {
      if (n->pp.x == p.x && n->pp.y == p.y) return make_pair(inf, n->pp.id);  // distancia infinita pra pontos iguais
      return make_pair((p - n->pp).dist(), n->pp.id);
    }
    node *f = n->first, *s = n->second;
    int bfirst = f->distance(p), bsec = s->distance(p);
    if (bfirst > bsec) swap(bsec, bfirst), swap(f, s);
    auto best = search(f, p);
    if (bsec < best.first || (!f->first)) best = min(best, search(s, p));
    return best;
  }
  pi nearest(const pt &p) { return search(root, p); }
};
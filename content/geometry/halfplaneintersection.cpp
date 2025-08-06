const long double eps = 1e-9;
const long double inf = 1e9;
struct pt {
  long double x, y;
  pt(long double x = 0, long double y = 0) : x(x), y(y) {}
  friend pt operator+(pt p, pt q) { return pt(p.x + q.x, p.y + q.y); }
  friend pt operator-(pt p, pt q) { return pt(p.x - q.x, p.y - q.y); }
  friend pt operator*(pt p, long double k) { return pt(p.x * k, p.y * k); }
  friend long double dot(pt p, pt q) { return p.x * q.x + p.y * q.y; }
  friend long double cross(pt p, pt q) { return p.x * q.y - p.y * q.x; }
};
struct halfplane {
  pt p, pq;
  long double angle;
  halfplane() {}
  halfplane(pt a, pt b) : p(a), pq(b - a) { angle = atan2l(pq.y, pq.x); }
  bool out(const pt &r) { return cross(pq, r - p) < -eps; }
  bool operator<(halfplane e) const { return angle < e.angle; }
  friend pt inter(halfplane s, halfplane t) {
    long double alpha = cross((t.p - s.p), t.pq) / cross(s.pq, t.pq);
    return s.p + (s.pq * alpha);
  }
};
vector<pt> hp_intersect(vector<halfplane> &h) {
  pt box[4] = {pt(inf, inf), pt(-inf, inf), pt(-inf, -inf), pt(inf, -inf)};  // Bounding box in CCW order
  for (int i = 0; i < 4; i++) {
    halfplane aux(box[i], box[(i + 1) % 4]);
    h.pb(aux);
  }
  sort(h.begin(), h.end());
  deque<halfplane> dq;
  int len = 0;
  for (int i = 0; i < h.size(); i++) {
    while (len > 1 && h[i].out(inter(dq[len - 1], dq[len - 2]))) {
      dq.pop_back();
      --len;
    }
    while (len > 1 && h[i].out(inter(dq[0], dq[1]))) {
      dq.pop_front();
      --len;
    }
    if (len > 0 && fabsl(cross(h[i].pq, dq[len - 1].pq)) < eps) {
      if (dot(h[i].pq, dq[len - 1].pq) < 0.0) {
        return vector<pt>();
      }
      if (h[i].out(dq[len - 1].p)) {
        dq.pop_back();
        --len;
      } else {
        continue;
      }
    }
    dq.push_back(h[i]);
    ++len;
  }
  while (len > 2 && dq[0].out(inter(dq[len - 1], dq[len - 2]))) {
    dq.pop_back();
    --len;
  }
  while (len > 2 && dq[len - 1].out(inter(dq[0], dq[1]))) {
    dq.pop_front();
    --len;
  }
  if (len < 3) {
    return vector<pt>();
  }
  vector<pt> ret(len);
  for (int i = 0; i + 1 < len; i++) {
    ret[i] = inter(dq[i], dq[i + 1]);
  }
  ret.back() = inter(dq[len - 1], dq[0]);
  return ret;
}
// half-plane - regiao planar que consiste de todos os pontos que estao de um lado de uma reta
// e dai pros half-planes, considerando que eh a regiao da esquerda em relacao ao vetor de direcao
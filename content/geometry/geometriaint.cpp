#define sq(x) ((x) * (ll)(x))
struct pt {  // ponto
  int x, y;
  pt(int x_ = 0, int y_ = 0) : x(x_), y(y_) {}
  bool operator<(const pt p) const {
    if (x != p.x) return x < p.x;
    return y < p.y;
  }
  bool operator==(const pt p) const { return x == p.x and y == p.y; }
  pt operator+(const pt p) const { return pt(x + p.x, y + p.y); }
  pt operator-(const pt p) const { return pt(x - p.x, y - p.y); }
  pt operator*(const int c) const { return pt(x * c, y * c); }
  ll operator*(const pt p) const { return x * (ll)p.x + y * (ll)p.y; }
  ll operator^(const pt p) const { return x * (ll)p.y - y * (ll)p.x; }
  friend istream& operator>>(istream& in, pt& p) { return in >> p.x >> p.y; }
};
struct line {  // reta
  pt p, q;
  line() {}
  line(pt p_, pt q_) : p(p_), q(q_) {}
  friend istream& operator>>(istream& in, line& r) { return in >> r.p >> r.q; }
};
// PONTO & VETOR
ll dist2(pt p, pt q) {  // quadrado da distancia
  return sq(p.x - q.x) + sq(p.y - q.y);
}
ll sarea2(pt p, pt q, pt r) {  // 2 * area com sinal
  return (q - p) ^ (r - q);
}
bool col(pt p, pt q, pt r) {  // se p, q e r sao colin.
  return sarea2(p, q, r) == 0;
}
bool ccw(pt p, pt q, pt r) {  // se p, q, r sao ccw
  return sarea2(p, q, r) > 0;
}
int quad(pt p) {  // quadrante de um ponto
  return (p.x < 0) ^ 3 * (p.y < 0);
}
bool compare_angle(pt p, pt q) {  // retorna se ang(p) < ang(q)
  if (quad(p) != quad(q)) return quad(p) < quad(q);
  return ccw(q, pt(0, 0), p);
}
pt rotate90(pt p) {  // rotaciona 90 graus
  return pt(-p.y, p.x);
}
// RETA
bool isinseg(pt p, line r) {  // se p pertence ao seg de r
  pt a = r.p - p, b = r.q - p;
  return (a ^ b) == 0 and (a * b) <= 0;
}
bool interseg(line r, line s) {  // se o seg de r intersecta o seg de s
  if (isinseg(r.p, s) or isinseg(r.q, s) or isinseg(s.p, r) or isinseg(s.q, r)) return 1;

  return ccw(r.p, r.q, s.p) != ccw(r.p, r.q, s.q) and ccw(s.p, s.q, r.p) != ccw(s.p, s.q, r.q);
}
int segpoints(line r) {  // numero de pontos inteiros no segmento
  return 1 + __gcd(abs(r.p.x - r.q.x), abs(r.p.y - r.q.y));
}
double get_t(pt v, line r) {  // retorna t tal que t*v pertence a reta r
  return (r.p ^ r.q) / (double)((r.p - r.q) ^ v);
}
// POLIGONO
// quadrado da distancia entre os retangulos a e b (lados paralelos aos eixos)
// assume que ta representado (inferior esquerdo, superior direito)
ll dist2_rect(pair<pt, pt> a, pair<pt, pt> b) {
  int hor = 0, vert = 0;
  if (a.second.x < b.first.x)
    hor = b.first.x - a.second.x;
  else if (b.second.x < a.first.x)
    hor = a.first.x - b.second.x;
  if (a.second.y < b.first.y)
    vert = b.first.y - a.second.y;
  else if (b.second.y < a.first.y)
    vert = a.first.y - b.second.y;
  return sq(hor) + sq(vert);
}
ll polarea2(vector<pt> v) {  // 2 * area do poligono
  ll ret = 0;
  for (int i = 0; i < v.size(); i++) ret += sarea2(pt(0, 0), v[i], v[(i + 1) % v.size()]);
  return abs(ret);
}
// se o ponto ta dentro do poligono: retorna 0 se ta fora,
// 1 se ta no interior e 2 se ta na borda
int inpol(vector<pt>& v, pt p) {  // O(n)
  int qt = 0;
  for (int i = 0; i < v.size(); i++) {
    if (p == v[i]) return 2;
    int j = (i + 1) % v.size();
    if (p.y == v[i].y and p.y == v[j].y) {
      if ((v[i] - p) * (v[j] - p) <= 0) return 2;
      continue;
    }
    bool baixo = v[i].y < p.y;
    if (baixo == (v[j].y < p.y)) continue;
    auto t = (p - v[i]) ^ (v[j] - v[i]);
    if (!t) return 2;
    if (baixo == (t > 0)) qt += baixo ? 1 : -1;
  }
  return qt != 0;
}
ll interior_points(vector<pt> v) {  // pontos inteiros dentro de um poligono simples
  ll b = 0;
  for (int i = 0; i < v.size(); i++) b += segpoints(line(v[i], v[(i + 1) % v.size()])) - 1;
  return (polarea2(v) - b) / 2 + 1;
}
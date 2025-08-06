namespace dio {
vector<pi> sols;
int gcd(int a, int b, int &x, int &y) {
  if (b == 0) {
    x = 1, y = 0;
    return a;
  }
  int x1, y1, d = gcd(b, a % b, x1, y1);
  x = y1, y = x1 - y1 * (a / b);
  return d;
}
void one_sol(int a, int b, int c) {
  int x0, y0, g;
  g = gcd(abs(a), abs(b), x0, y0);
  if (c % g) return;
  x0 *= (c / g);
  y0 *= (c / g);
  if (a < 0) x0 *= -1;
  if (b < 0) y0 *= -1;
  sols.pb({x0, y0});
}
void more_sols(int a, int b, int c) {
  int g = __gcd(a, b);
  int x0 = sols[0].fir, y0 = sols[0].sec;
  for (int k = -200000; k <= 200000; k++) {
    int x = x0 + k * (b / g);
    int y = y0 - k * (a / g);
    sols.pb({x, y});
  }
}
}  // namespace dio
// equacoes do tipo: ax + by = c
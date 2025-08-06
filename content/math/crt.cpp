namespace crt {
vector<pi> eq;
int gcd(int a, int b, int &x, int &y) {
  if (b == 0) {
    x = 1, y = 0;
    return a;
  }
  int x1, y1, d = gcd(b, a % b, x1, y1);
  x = y1, y = x1 - y1 * (a / b);
  return d;
}
pi crt() {
  int a1 = eq[0].fir, m1 = eq[0].sec;
  a1 %= m1;
  for (int i = 1; i < eq.size(); i++) {
    int a2 = eq[i].fir, m2 = eq[i].sec;
    int g = __gcd(m1, m2);
    if (a1 % g != a2 % g) return {-1, -1};
    int p, q;
    gcd(m1 / g, m2 / g, p, q);
    int mod = m1 / g * m2;
    int x = (a1 * (m2 / g) % mod * q % mod + a2 * (m1 / g) % mod * p % mod) % mod;
    a1 = x;
    if (a1 < 0) a1 += mod;
    m1 = mod;
  }
  return {a1, m1};
}
}  // namespace crt
// o menor inteiro a que satisfaz:
// a mod p1 = x1
// a mod p2 = x2
// a funcao crt retorna um pair {a, mod}
// dai a solucao pode ser descrita como
// x = a % mod
// entao os valores possiveis sao:
// a, (a + mod), a + (2 * mod), a + (3 * mod), ...
// cuidado com overflow!
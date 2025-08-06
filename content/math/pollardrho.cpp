#define int __int128
namespace pollard_rho {
int multiplicate(int x, int y, int m) { return (x * y) % m; }
int modpow(int x, int y, int m) {
  int z = 1;
  while (y) {
    if (y & 1) z = (z * x) % m;
    x = (x * x) % m;
    y >>= 1;
  }
  return z;
}
bool is_composite(int n, int a, int d, int s) {
  int x = modpow(a, d, n);
  if (x == 1 or x == n - 1) return false;
  for (int r = 1; r < s; r++) {
    x = multiplicate(x, x, n);
    if (x == n - 1LL) return false;
  }
  return true;
};
int miller_rabin(int n) {
  if (n < 2) return false;
  int r = 0, d = n - 1LL;
  while ((d & 1LL) == 0) {
    d >>= 1;
    r++;
  }
  for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
    if (n == a) return true;
    if (is_composite(n, a, d, r)) return false;
  }
  return true;
}
int f(int x, int m) { return multiplicate(x, x, m) + 1; }
int rho(int n) {
  int x0 = 1, t = 0, prd = 2;
  int x = 0, y = 0, q;
  while (t % 40 || __gcd(prd, n) == 1) {
    if (x == y) {
      x0++;
      x = x0;
      y = f(x, n);
    }
    q = multiplicate(prd, max(x, y) - min(x, y), n);
    if (q != 0) prd = q;
    x = f(x, n);
    y = f(y, n);
    y = f(y, n);
    t++;
  }
  return __gcd(prd, n);
}
vector<int> fact(int n) {
  if (n == 1) return {};
  if (miller_rabin(n)) return {n};
  int x = rho(n);
  auto l = fact(x), r = fact(n / x);
  l.insert(l.end(), r.begin(), r.end());
  return l;
}
}  // namespace pollard_rho
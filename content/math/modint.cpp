struct modint {
  int val;
  modint(int v = 0) { val = v % mod; }
  int pow(int y) {
    modint x = val;
    modint z = 1;
    while (y) {
      if (y & 1) z *= x;
      x *= x;
      y >>= 1;
    }
    return z.val;
  }
  int inv() { return pow(mod - 2); }
  void operator=(int o) { val = o % mod; }
  void operator=(modint o) { val = o.val % mod; }
  void operator+=(modint o) { *this = *this + o; }
  void operator-=(modint o) { *this = *this - o; }
  void operator*=(modint o) { *this = *this * o; }
  void operator/=(modint o) { *this = *this / o; }
  bool operator==(modint o) { return val == o.val; }
  bool operator!=(modint o) { return val != o.val; }
  int operator*(modint o) { return ((val * o.val) % mod); }
  int operator/(modint o) { return (val * o.inv()) % mod; }
  int operator+(modint o) { return (val + o.val) % mod; }
  int operator-(modint o) { return (val - o.val + mod) % mod; }
};
modint f[MAXN];
modint inv[MAXN];
modint invfat[MAXN];
void calc() {
  f[0] = 1;
  for (int i = 1; i < MAXN; i++) {
    f[i] = f[i - 1] * i;
  }
  inv[1] = 1;
  for (int i = 2; i < MAXN; ++i) {
    int val = mod / i;
    val = (inv[mod % i] * val) % mod;
    val = mod - val;
    inv[i] = val;
  }
  invfat[0] = 1;
  invfat[MAXN - 1] = modint(f[MAXN - 1]).inv();
  for (int i = MAXN - 2; i >= 1; i--) {
    invfat[i] = invfat[i + 1] * (i + 1);
  }
}
modint ncr(int n, int k)  // combinacao
{
  modint ans = f[n] * invfat[k];
  ans *= invfat[n - k];
  return ans;
}
modint arr(int n, int k)  // arranjo
{
  modint ans = f[n] * invfat[n - k];
  return ans;
}
modint ncr(int n, int k) {
  // calcular combinacao para n grande
  // nesse problema n <= 10^12
  // em O(k)
  modint num = 1;
  modint den = 1;
  for (int i = 0; i < k; i++) {
    num = num * modint(n - i);
    den = den * modint(i + 1);
  }
  modint ans = num / den;
  return ans;
}
modint stars_and_bars(int n, int k) {
  // para pares de inteiros n e k
  // enconte a quantidade de k-tuplas com soma == n
  // x1 + x2 + ... + xk = n
  return ncr(n + k - 1, k - 1);
}
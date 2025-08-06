const int MOD = (1ll << 61) - 1;
int P;
int mulmod(int a, int b) {
  const static int LOWER = (1ll << 30) - 1, GET31 = (1ll << 31) - 1;
  int l1 = a & LOWER, h1 = a >> 30, l2 = b & LOWER, h2 = b >> 30;
  int m = l1 * h2 + l2 * h1, h = h1 * h2;
  int ans = l1 * l2 + (h >> 1) + ((h & 1) << 60) + (m >> 31) + ((m & GET31) << 30) + 1;
  ans = (ans & MOD) + (ans >> 61), ans = (ans & MOD) + (ans >> 61);
  return ans - 1;
}
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int uniform(int l, int r) {
  uniform_int_distribution<int> uid(l, r);
  return uid(rng);
}
struct string_hashing {
  vector<int> h, p;
  string_hashing() {}
  string_hashing(string s) : h(s.size()), p(s.size()) {
    p[0] = 1, h[0] = s[0];
    for (int i = 1; i < s.size(); i++) p[i] = mulmod(p[i - 1], P), h[i] = (mulmod(h[i - 1], P) + s[i]) % MOD;
  }
  int get(int l, int r) {
    int hash = h[r] - (l ? mulmod(h[l - 1], p[r - l + 1]) : 0);
    return hash < 0 ? hash + MOD : hash;
  }
  int append(int h, int hb, int blen) { return (hb + mulmod(h, p[blen])) % MOD; }
};
// lembrar do P = uniform(256, MOD - 1);
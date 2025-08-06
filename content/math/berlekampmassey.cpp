// berlekamp massey
// mas precisa que o mod seja primo (para poder achar inverso)
// dado os n primeiros termos de uma recorrencia linear
// a[0], a[1], a[2], ..., a[n - 1]
// ele acha a reccorrencia linear mais curta que da matching com os n primeiros valores
vector<modint> berlekamp_massey(vector<modint> x) {
  vector<modint> ls, cur;
  int lf, ld;
  for (int i = 0; i < x.size(); i++) {
    modint t = 0;
    for (int j = 0; j < cur.size(); j++) {
      t += (x[i - j - 1] * cur[j]);
    }
    if (modint(t - x[i]).val == 0) continue;
    if (cur.empty()) {
      cur.resize(i + 1);
      lf = i;
      ld = (t - x[i]) % mod;
      continue;
    }
    modint k = -(x[i] - t);
    k *= modint(ld).inv();
    vector<modint> c(i - lf - 1);
    c.pb(k);
    for (auto const &j : ls) {
      modint curr = modint(j.val * -1) * k;
      c.pb(curr);
    }
    if (c.size() < cur.size()) c.resize(cur.size());
    for (int j = 0; j < cur.size(); j++) {
      c[j] = c[j] + cur[j];
    }
    if (i - lf + ls.size() >= cur.size()) {
      tie(ls, lf, ld) = make_tuple(cur, i, t - x[i]);
    }
    cur = c;
  }
  return cur;
}
modint get_nth(vector<modint> rec, vector<modint> dp, int n) {
  int m = rec.size();
  vector<modint> s(m), t(m);
  s[0] = 1;
  if (m != 1)
    t[1] = 1;
  else
    t[0] = rec[0];
  auto mul = [&rec](vector<modint> v, vector<modint> w) {
    vector<modint> ans(2 * v.size());
    for (int j = 0; j < v.size(); j++) {
      for (int k = 0; k < v.size(); k++) ans[j + k] += v[j] * w[k];
    }
    for (int j = 2 * v.size() - 1; j >= v.size(); j--) {
      for (int k = 1; k <= v.size(); k++) ans[j - k] += ans[j] * rec[k - 1];
    }
    ans.resize(v.size());
    return ans;
  };
  while (n) {
    if (n & 1) s = mul(s, t);
    t = mul(t, t);
    n >>= 1;
  }
  modint ret = 0;
  for (int i = 0; i < m; i++) ret += s[i] * dp[i];
  return ret;
}
modint guess_nth_term(vector<modint> x, int n) {
  if (n < x.size()) return x[n];
  vector<modint> coef = berlekamp_massey(x);  // coeficientes da recorrencia
  if (coef.empty()) return 0;
  return get_nth(coef, x, n);
}
vector<modint> fwht(char op, vector<modint> f, bool inv = 0) {
  int n = f.size();
  for (int k = 0; (n - 1) >> k; k++) {
    for (int i = 0; i < n; i++) {
      if (i >> k & 1) {
        int j = i ^ (1 << k);
        if (op == '^') f[j] += f[i], f[i] = f[j] - modint(2) * f[i];
        if (op == '|') f[i] += modint(inv ? -1 : 1) * f[j];
        if (op == '&') f[j] += modint(inv ? -1 : 1) * f[i];
      }
    }
  }
  if (op == '^' and inv) {
    for (auto &i : f) i /= n;
  }
  return f;
}
vector<modint> conv(char op, vector<modint> a, vector<modint> b) {
  a = fwht(op, a, 0);
  b = fwht(op, b, 0);
  for (int i = 0; i < a.size(); i++) {
    a[i] *= b[i];
  }
  return fwht(op, a, 1);
}
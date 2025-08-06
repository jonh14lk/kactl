struct lagrange {
  int n;
  vector<modint> den;
  vector<modint> y;
  vector<modint> fat;
  vector<modint> inv_fat;
  lagrange(vector<modint> &v)  // f(i) = v[i], gera um polinomio de grau n - 1
  {
    n = v.size();
    calc(n);
    calc_den(n);
    y = v;
  }
  void calc_den(int n) {
    den.resize(n);
    for (int i = 0; i < n; i++) {
      den[i] = inv_fat[n - i - 1] * inv_fat[i];
      if ((n - i - 1) % 2 == 1) {
        int x = (mod - den[i].val) % mod;
        den[i] = x;
      }
    }
  }
  void calc(int n) {
    fat.resize(n + 1);
    inv_fat.resize(n + 1);
    fat[0] = 1;
    inv_fat[0] = 1;
    for (int i = 1; i <= n; i++) {
      fat[i] = fat[i - 1] * i;
      inv_fat[i] = fat[i].inv();
    }
  }
  modint get_val(int x)  // complexidade: O(n)
  {
    x %= mod;
    vector<modint> l(n);
    vector<modint> r(n);
    l[0] = 1, r[n - 1] = 1;
    for (int i = 1; i < n; i++) {
      modint cof = (x - (i - 1) + mod);
      l[i] = l[i - 1] * cof;
    }
    for (int i = n - 2; i >= 0; i--) {
      modint cof = (x - (i + 1) + mod);
      r[i] = r[i + 1] * cof;
    }
    modint ans = 0;
    for (int i = 0; i < n; i++) {
      modint cof = l[i] * r[i];
      ans += modint(cof * y[i]) * den[i];
    }
    return ans;
  }
  vector<modint> find_coefs()  // encontra os coeficientes do polinomio
  {
    int nn = n;
    int d = nn - 1;
    vector<modint> c(nn, 0);
    for (int i = 0; i < y.size(); i++) {
      c[d] += (y[i] * den[i]);
    }
    for (int p = nn - 2; p >= 0; p--) {
      nn--;
      calc_den(nn);
      for (int i = 0; i <= p; i++) {
        y[i] -= (c[p + 1] * modint(i).pow(d));
        c[p] += (y[i] * den[i]);
      }
      d--;
    }
    return c;
  }
};
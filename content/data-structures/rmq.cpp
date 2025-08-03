struct rmq {
  int n;
  vector<vector<pi>> m;
  vector<int> log;
  rmq() {}
  rmq(vector<pi> &v) {
    n = v.size();
    log.resize(n + 1);
    log[1] = 0;
    for (int i = 2; i <= n; i++) log[i] = log[i / 2] + 1;
    int sz = log[n] + 2;
    m = vector<vector<pi>>(sz, vector<pi>(n + 1));
    for (int i = 0; i < n; i++) {
      m[0][i] = v[i];
    }
    for (int j = 1; j < sz; j++) {
      for (int i = 0; i + (1 << j) <= n; i++) m[j][i] = min(m[j - 1][i], m[j - 1][i + (1 << (j - 1))]);
    }
  }
  int qry(int a, int b) { return min(m[log[b - a + 1]][a], m[log[b - a + 1]][b - (1 << log[b - a + 1]) + 1]).second; }
};
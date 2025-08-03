struct hungarian {  // declarar algo como hungarian h(n), n de cada lado
  int n, inf;
  vector<vector<int>> a;
  vector<int> u, v, p, way;
  hungarian(int n_) : n(n_), u(n + 1), v(n + 1), p(n + 1), way(n + 1) {
    a = vector<vector<int>>(n, vector<int>(n));
    inf = numeric_limits<int>::max();
  }
  void add_edge(int x, int y, int c) { a[x][y] = c; }
  pair<int, vector<int>> run() {
    for (int i = 1; i <= n; i++) {
      p[0] = i;
      int j0 = 0;
      vector<int> minv(n + 1, inf);
      vector<int> used(n + 1, 0);
      do {
        used[j0] = true;
        int i0 = p[j0], j1 = -1;
        int delta = inf;
        for (int j = 1; j <= n; j++) {
          if (!used[j]) {
            int cur = a[i0 - 1][j - 1] - u[i0] - v[j];
            if (cur < minv[j]) minv[j] = cur, way[j] = j0;
            if (minv[j] < delta) delta = minv[j], j1 = j;
          }
        }
        for (int j = 0; j <= n; j++) {
          if (used[j])
            u[p[j]] += delta, v[j] -= delta;
          else
            minv[j] -= delta;
        }
        j0 = j1;
      } while (p[j0] != 0);
      do {
        int j1 = way[j0];
        p[j0] = p[j1];
        j0 = j1;
      } while (j0);
    }
    vector<int> ans(n);
    for (int j = 1; j <= n; j++) ans[p[j] - 1] = j - 1;
    return make_pair(-v[0], ans);
  }
};
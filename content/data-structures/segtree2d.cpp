struct segtree2d {
  int n, m;
  vector<vector<int>> seg;
  int neutral() { return 0; }
  int merge(int a, int b) { return a + b; }
  segtree2d(int nn, int mm) {
    n = nn, m = mm;
    seg = vector<vector<int>>(2 * n, vector<int>(2 * m, neutral()));
  }
  int qry(int x1, int y1, int x2, int y2) {
    int ret = neutral();
    int y3 = y1 + m, y4 = y2 + m;
    for (x1 += n, x2 += n; x1 <= x2; ++x1 /= 2, --x2 /= 2) {
      for (y1 = y3, y2 = y4; y1 <= y2; ++y1 /= 2, --y2 /= 2) {
        if (x1 % 2 == 1 and y1 % 2 == 1) ret = merge(ret, seg[x1][y1]);
        if (x1 % 2 == 1 and y2 % 2 == 0) ret = merge(ret, seg[x1][y2]);
        if (x2 % 2 == 0 and y1 % 2 == 1) ret = merge(ret, seg[x2][y1]);
        if (x2 % 2 == 0 and y2 % 2 == 0) ret = merge(ret, seg[x2][y2]);
      }
    }
    return ret;
  }
  void upd(int x, int y, int val) {
    int y2 = y += m;
    for (x += n; x; x /= 2, y = y2) {
      if (x >= n)
        seg[x][y] = val;
      else
        seg[x][y] = merge(seg[2 * x][y], seg[2 * x + 1][y]);
      while (y /= 2) seg[x][y] = merge(seg[x][2 * y], seg[x][2 * y + 1]);
    }
  }
};
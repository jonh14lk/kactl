struct dsu {
  int tot;
  vector<int> parent;
  vector<int> sz;
  dsu(int n) {
    parent.resize(n);
    sz.resize(n);
    tot = n;
    for (int i = 0; i < n; i++) {
      parent[i] = i;
      sz[i] = 1;
    }
  }
  int find_set(int i) { return parent[i] = (parent[i] == i) ? i : find_set(parent[i]); }
  void make_set(int x, int y) {
    x = find_set(x), y = find_set(y);
    if (x != y) {
      if (sz[x] > sz[y]) swap(x, y);
      parent[x] = y;
      sz[y] += sz[x];
      tot--;
    }
  }
};

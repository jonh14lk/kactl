struct hld {
  int n, cur_pos;
  segtree seg;
  vector<vector<int>> adj;
  vector<int> parent, depth, heavy, head, pos, sz;
  int dfs(int s) {
    int size = 1, max_c_size = 0;
    for (auto const &c : adj[s]) {
      if (c != parent[s]) {
        parent[c] = s;
        depth[c] = depth[s] + 1;
        int c_size = dfs(c);
        size += c_size;
        if (c_size > max_c_size) max_c_size = c_size, heavy[s] = c;
      }
    }
    return sz[s] = size;
  }
  void decompose(int s, int h) {
    head[s] = h;
    pos[s] = cur_pos++;
    if (heavy[s] != -1) decompose(heavy[s], h);
    for (int c : adj[s]) {
      if (c != parent[s] && c != heavy[s]) decompose(c, c);
    }
  }
  hld(vector<vector<int>> &g) {
    n = g.size();
    adj = g;
    seg = segtree(n);
    parent.assign(n, -1);
    depth.assign(n, -1);
    heavy.assign(n, -1);
    head.assign(n, -1);
    pos.assign(n, -1);
    sz.assign(n, 1);
    cur_pos = 0;
    dfs(0);
    decompose(0, 0);
  }
  int query_path(int a, int b) {
    int res = 0;
    for (; head[a] != head[b]; b = parent[head[b]]) {
      if (depth[head[a]] > depth[head[b]]) swap(a, b);
      res += seg.query(0, n - 1, pos[head[b]], pos[b], 1);
    }
    if (depth[a] > depth[b]) swap(a, b);
    res += seg.query(0, n - 1, pos[a], pos[b], 1);
    return res;
  }
  void update_path(int a, int b, int x) {
    for (; head[a] != head[b]; b = parent[head[b]]) {
      if (depth[head[a]] > depth[head[b]]) swap(a, b);
      seg.update(1, 0, n - 1, pos[head[b]], pos[b], x);
    }
    if (depth[a] > depth[b]) swap(a, b);
    seg.update(1, 0, n - 1, pos[a], pos[b], x);
  }
  void update_subtree(int a, int x) { seg.update(1, 0, n - 1, pos[a], pos[a] + sz[a] - 1, x); }
  int query_subtree(int a) { return seg.query(0, n - 1, pos[a], pos[a] + sz[a] - 1, 1); }
  int lca(int a, int b) {
    if (pos[a] < pos[b]) swap(a, b);
    return (head[a] == head[b]) ? b : lca(parent[head[a]], b);
  }
};
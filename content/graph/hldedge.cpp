namespace hld {
int cur_pos;
vector<int> parent, depth, heavy, head, pos, sz, up;
int dfs(int s) {
  int size = 1, max_c_size = 0;
  for (auto const &c : adj[s]) {
    if (c.fir != parent[s]) {
      parent[c.fir] = s;
      depth[c.fir] = depth[s] + 1;
      int c_size = dfs(c.fir);
      size += c_size;
      if (c_size > max_c_size) max_c_size = c_size, heavy[s] = c.fir;
    }
  }
  return sz[s] = size;
}
void decompose(int s, int h) {
  head[s] = h;
  pos[s] = cur_pos++;
  seg::v[pos[s]] = up[s];
  for (auto const &c : adj[s]) {
    if (c.fir != parent[s] && c.fir == heavy[s]) {
      up[c.fir] = c.sec;
      decompose(heavy[s], h);
    }
  }
  for (auto const &c : adj[s]) {
    if (c.fir != parent[s] && c.fir != heavy[s]) {
      up[c.fir] = c.sec;
      decompose(c.fir, c.fir);
    }
  }
}
void init() {
  parent.assign(MAXN, -1);
  depth.assign(MAXN, -1);
  heavy.assign(MAXN, -1);
  head.assign(MAXN, -1);
  pos.assign(MAXN, -1);
  sz.assign(MAXN, 1);
  up.assign(MAXN, 0);
  cur_pos = 0;
  dfs(0);
  decompose(0, 0);
  seg::build(0, n - 1, 1);
}
int query_path(int a, int b) {
  int res = -1;
  for (; head[a] != head[b]; b = parent[head[b]]) {
    if (depth[head[a]] > depth[head[b]]) swap(a, b);
    res = max(res, seg::query(0, n - 1, pos[head[b]], pos[b], 1));
  }
  if (depth[a] > depth[b]) swap(a, b);
  res = max(res, seg::query(0, n - 1, pos[a] + 1, pos[b], 1));
  return res;
}
void update_path(int a, int b, int x) {
  for (; head[a] != head[b]; b = parent[head[b]]) {
    if (depth[head[a]] > depth[head[b]]) swap(a, b);
    seg::update(1, 0, n - 1, pos[head[b]], pos[b], x);
  }
  if (depth[a] > depth[b]) swap(a, b);
  seg::update(1, 0, n - 1, pos[a] + 1, pos[b], x);
}
void update_subtree(int a, int x) { seg::update(1, 0, n - 1, pos[a] + 1, pos[a] + sz[a] - 1, x); }
int query_subtree(int a, int x) { return seg::query(0, n - 1, pos[a] + 1, pos[a] + sz[a] - 1, 1); }
}  // namespace hld
int n;
vector<int> adj[MAXN];
namespace lca {
int l, timer;
vector<int> tin, tout, depth;
vector<vector<int>> up;
void dfs(int v, int p) {
  tin[v] = ++timer;
  up[v][0] = p;
  for (int i = 1; i <= l; i++) up[v][i] = up[up[v][i - 1]][i - 1];
  for (auto const &u : adj[v]) {
    if (p == u) continue;
    depth[u] = depth[v] + 1;
    dfs(u, v);
  }
  tout[v] = ++timer;
}
bool is_ancestor(int u, int v) { return tin[u] <= tin[v] && tout[u] >= tout[v]; }
int binary_lifting(int u, int v) {
  if (is_ancestor(u, v)) return u;
  if (is_ancestor(v, u)) return v;
  for (int i = l; i >= 0; --i)
    if (!is_ancestor(up[u][i], v)) u = up[u][i];
  return up[u][0];
}
void init() {
  tin.resize(n);
  tout.resize(n);
  depth.resize(n);
  timer = 0;
  l = ceil(log2(n));
  up.assign(n, vector<int>(l + 1));
  dfs(0, 0);
}
int dist(int s, int v) {
  int at = binary_lifting(s, v);
  return (depth[s] + depth[v] - 2 * depth[at]);
}
}  // namespace lca
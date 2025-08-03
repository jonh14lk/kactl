
int n, m;
bool vis[MAXN];
int root[MAXN];
vector<int> order;
vector<int> roots;
vector<int> comp;
vector<vector<int>> comps;
vector<int> adj[MAXN];
vector<int> adj_rev[MAXN];
vector<int> adj_scc[MAXN];
void dfs(int v) {
  vis[v] = true;
  for (auto const &u : adj[v])
    if (!vis[u]) dfs(u);
  order.pb(v);
}
void dfs2(int v) {
  comp.pb(v);
  vis[v] = true;
  for (auto const &u : adj_rev[v])
    if (!vis[u]) dfs2(u);
}
//...
cin >> n >> m;
for (int i = 0; i < m; i++) {
  int a, b;
  cin >> a >> b;
  adj[a].pb(b);
  adj_rev[b].pb(a);
}
for (int i = 0; i < n; i++) {
  if (!vis[i]) dfs(i);
}
reverse(order.begin(), order.end());
memset(vis, false, sizeof(vis));
for (auto const &v : order) {
  if (!vis[v]) {
    comp.clear();
    dfs2(v);
    comps.pb(comp);
    // making condensation graph
    int r = comp.back();
    for (auto const &u : comp) root[u] = r;
    roots.push_back(r);
  }
}
// making condensation graph
for (int v = 0; v < n; v++) {
  for (auto const &u : adj[v]) {
    int root_v = roots[v];
    int root_u = roots[u];
    if (root_u != root_v) adj_scc[root_v].pb(root_u);
  }
}
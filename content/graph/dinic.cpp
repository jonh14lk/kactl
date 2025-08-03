#define INF 1e9
struct edge {
  int to, from, flow, capacity, id;
};
struct dinic {
  int n, src, sink;
  vector<vector<edge>> adj;
  vector<int> level;
  vector<int> ptr;

  dinic(int sz) {
    n = sz;
    adj.resize(n);
    level.resize(n);
    ptr.resize(n);
  }
  void add_edge(int a, int b, int c, int id) {
    adj[a].pb({b, (int)adj[b].size(), c, c, id});
    adj[b].pb({a, (int)adj[a].size() - 1, 0, 0, id});
  }
  bool bfs() {
    level.assign(n, -1);
    level[src] = 0;
    queue<int> q;
    q.push(src);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (auto at : adj[u]) {
        if (at.flow && level[at.to] == -1) {
          q.push(at.to);
          level[at.to] = level[u] + 1;
        }
      }
    }
    return level[sink] != -1;
  }
  int dfs(int u, int flow) {
    if (u == sink || flow == 0) return flow;
    for (int &p = ptr[u]; p < adj[u].size(); p++) {
      edge &at = adj[u][p];
      if (at.flow && level[u] == level[at.to] - 1) {
        int kappa = dfs(at.to, min(flow, at.flow));
        at.flow -= kappa;
        adj[at.to][at.from].flow += kappa;
        if (kappa != 0) return kappa;
      }
    }
    return 0;
  }
  int run() {
    int max_flow = 0;
    while (bfs()) {
      ptr.assign(n, 0);
      while (1) {
        int flow = dfs(src, INF);
        if (flow == 0) break;
        max_flow += flow;
      }
    }
    return max_flow;
  }
  vector<pii> cut_edges()  // arestas do corte minimo
  {
    bfs();
    vector<pii> ans;
    for (int i = 0; i < n; i++) {
      for (auto const &j : adj[i]) {
        if (level[i] != -1 && level[j.to] == -1 && j.capacity > 0) ans.pb({j.capacity, {i, j.to}});
      }
    }
    return ans;
  }
  vector<int> flow_edges(int n, int m)  // fluxo em cada aresta, na ordem da entrada
  {
    vector<int> ans(m);
    for (int i = 0; i < n; i++) {
      for (auto const &j : adj[i])
        if (!j.capacity) ans[j.id] = j.flow;
    }
    return ans;
  }
};
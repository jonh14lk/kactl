#define INF 1e9
struct hopcroft_karp {
  vector<int> match;
  vector<int> dist;
  vector<vector<int>> adj;
  int n, m, t;
  hopcroft_karp(int a, int b) {
    n = a, m = b;
    t = n + m + 1;
    match.assign(t, n + m);
    dist.assign(t, 0);
    adj.assign(t, vector<int>{});
  }
  void add_edge(int u, int v) {
    adj[u].pb(v);
    adj[v].pb(u);
  }
  bool bfs() {
    queue<int> q;
    for (int u = 0; u < n; u++) {
      if (match[u] == n + m)
        dist[u] = 0, q.push(u);
      else
        dist[u] = INF;
    }
    dist[n + m] = INF;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      if (dist[u] < dist[n + m]) {
        for (auto const &v : adj[u]) {
          if (dist[match[v]] == INF) {
            dist[match[v]] = dist[u] + 1;
            q.push(match[v]);
          }
        }
      }
    }
    return dist[n + m] < INF;
  }
  bool dfs(int u) {
    if (u < n + m) {
      for (auto const &v : adj[u]) {
        if (dist[match[v]] == dist[u] + 1 && dfs(match[v])) {
          match[v] = u;
          match[u] = v;
          return true;
        }
      }
      dist[u] = INF;
      return false;
    }
    return true;
  }
  vector<pi> run() {
    int cnt = 0;
    while (bfs())
      for (int u = 0; u < n; u++)
        if (match[u] == n + m && dfs(u)) cnt++;
    vector<pi> ans;
    for (int v = n; v < n + m; v++)
      if (match[v] < n + m) ans.pb({match[v], v});
    return ans;
  }
  vector<int> mvc()  // minimum vertex cover
  {
    vector<pi> ans = run();
    vector<bool> vis(n + m, 0);
    for (int i = 0; i < n; i++) {
      if (match[i] == n + m) {
        queue<int> q;
        q.push(i);
        while (!q.empty()) {
          int x = q.front();
          q.pop();
          vis[x] = 1;
          for (auto const &y : adj[x]) {
            if (!vis[y]) {
              vis[y] = 1;
              q.push(match[y]);
            }
          }
        }
      }
    }
    vector<int> vc;
    for (int i = 0; i < n; i++) {
      if (!vis[i]) vc.pb(i);
    }
    for (int i = n; i < n + m; i++) {
      if (vis[i]) vc.pb(i);
    }
    return vc;
  }
  vector<pi> mec()  // minimum edge cover
  {
    vector<pi> ans = run();
    for (int i = 0; i < n + m; i++) {
      if (match[i] == n + m && adj[i].size() > 0) {
        if (i < n)
          ans.pb({i, adj[i][0]});
        else
          ans.pb({adj[i][0], i});
      }
    }
    return ans;
  }
};
// minimum path cover on dag
// minimum set of paths such that each of the vertices belongs to exactly one path
vector<vector<int>> mpc(int n, vector<pi> &e) {
  hopcroft_karp h(n, n);
  for (auto const &i : e) h.add_edge(i.fir, n + i.sec);
  vector<pi> mat = h.run();
  vector<int> prv(n, -1);
  vector<int> nxt(n, -1);
  for (int i = 0; i < mat.size(); i++) {
    nxt[mat[i].fir] = mat[i].sec - n;
    prv[mat[i].sec - n] = mat[i].fir;
  }
  vector<vector<int>> ans;
  for (int i = 0; i < n; i++) {
    if (prv[i] == -1 && nxt[i] == -1) {
      ans.pb({i});
    } else if (prv[i] == -1) {
      vector<int> curr;
      int x = i;
      while (1) {
        curr.pb(x);
        if (nxt[x] == -1) break;
        x = nxt[x];
      }
      ans.pb(curr);
    }
  }
  return ans;
}
int n;
vector<int> adj[MAXN];
int sz[MAXN];
int dp[MAXN];
int dfs(int u, int v) {
  sz[u] = 1;
  for (auto const &i : adj[u])
    if (i != v) sz[u] += dfs(i, u);
  return sz[u];
}
void reroot(int u, int v) {
  for (auto const &i : adj[u]) {
    if (i != v) {
      int a = sz[u], b = sz[i];
      dp[i] = dp[u];
      dp[i] -= sz[u], dp[i] -= sz[i];
      sz[u] -= sz[i], sz[i] = n;
      dp[i] += sz[u], dp[i] += sz[i];
      reroot(i, u);
      sz[u] = a, sz[i] = b;
    }
  }
}
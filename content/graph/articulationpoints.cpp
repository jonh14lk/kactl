int n, m, timer;
vector<int> adj[MAXN];
bool is_cutpoint[MAXN];
int tin[MAXN];  // memset -1
int low[MAXN];  // memset -1
bool vis[MAXN];
void dfs(int v, int p) {  // chama pros nao vis
  vis[v] = true;
  tin[v] = timer, low[v] = timer++;
  int childs = 0;
  for (auto const &u : adj[v]) {
    if (u == p) continue;
    if (vis[u]) {
      low[v] = min(low[v], tin[u]);
    } else {
      dfs(u, v);
      low[v] = min(low[v], low[u]);
      if (low[u] >= tin[v] && p != -1) is_cutpoint[v] = true;
      childs++;
    }
  }
  if (p == -1 && childs > 1) is_cutpoint[v] = true;
}
nt n, m, timer;
vector<pi> edges;
vector<bool> is_bridge;
vector<pi> adj[MAXN];
int tin[MAXN];
int low[MAXN];            // memset -1
bool vis[MAXN];           // memset -1
void dfs(int v, int p) {  // chama de quem nao foi vis ainda
  vis[v] = true;
  tin[v] = timer, low[v] = timer++;
  for (auto const &u : adj[v]) {
    if (u.fir == p) continue;
    if (vis[u.fir]) {
      low[v] = min(low[v], tin[u.fir]);
      continue;
    }
    dfs(u.fir, v);
    low[v] = min(low[v], low[u.fir]);
    if (low[u.fir] > tin[v]) is_bridge[u.sec] = 1;
  }
}
// encontrar uma orientacao para as arestas tal que o numero
// minimo de scc eh o menor possivel
// numero minimo de scc = numero de componentes conexas + numero de pontes
int n, m, timer, comps, bridges;
vector<pi> edges;
vector<pi> adj[MAXN];
int tin[MAXN];  // memset -1
int low[MAXN];  // memset -1
bool vis[MAXN];
char orient[MAXN];
void find_bridges(int v) {  // chama se tem tin == -1
  low[v] = timer, tin[v] = timer++;
  for (auto const &p : adj[v]) {
    if (vis[p.sec]) continue;
    vis[p.sec] = true;
    orient[p.sec] = (v == edges[p.sec].first) ? '>' : '<';
    if (tin[p.fir] == -1) {
      find_bridges(p.fir);
      low[v] = min(low[v], low[p.fir]);
      if (low[p.fir] > tin[v]) bridges++;
    } else {
      low[v] = min(low[v], low[p.fir]);
    }
  }
}
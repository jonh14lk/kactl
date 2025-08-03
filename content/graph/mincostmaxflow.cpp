namespace mcf {
struct edge {
  int to, capacity, cost, res;
};
int source, destiny;
vector<edge> adj[MAXN];
vector<int> dist;
vector<int> parent;
vector<int> edge_index;
vector<bool> in_queue;
void add_edge(int a, int b, int c, int d) {
  adj[a].pb({b, c, d, (int)adj[b].size()});
  adj[b].pb({a, 0, -d, (int)adj[a].size() - 1});
}
bool dijkstra(int s) {
  dist.assign(MAXN, INF);
  parent.assign(MAXN, -1);
  edge_index.assign(MAXN, -1);
  in_queue.assign(MAXN, false);
  dist[s] = 0;
  queue<int> q;
  q.push(s);
  while (!q.empty()) {
    int u = q.front(), idx = 0;
    q.pop();
    in_queue[u] = false;
    for (auto const &v : adj[u]) {
      if (v.capacity && dist[v.to] > dist[u] + v.cost) {
        dist[v.to] = dist[u] + v.cost;
        parent[v.to] = u;
        edge_index[v.to] = idx;
        if (!in_queue[v.to]) {
          in_queue[v.to] = true;
          q.push(v.to);
        }
      }
      idx++;
    }
  }
  return dist[destiny] != INF;
}
int get_cost() {
  int flow = 0, cost = 0;
  while (dijkstra(source)) {
    int curr_flow = INF, curr = destiny;
    while (curr != source) {
      int p = parent[curr];
      curr_flow = min(curr_flow, adj[p][edge_index[curr]].capacity);
      curr = p;
    }
    flow += curr_flow;
    cost += curr_flow * dist[destiny];
    curr = destiny;
    while (curr != source) {
      int p = parent[curr];
      int res_idx = adj[p][edge_index[curr]].res;
      adj[p][edge_index[curr]].capacity -= curr_flow;
      adj[curr][res_idx].capacity += curr_flow;
      curr = p;
    }
  }
  return cost;
}
}  // namespace mcf
struct dsu {
  vector<pi> parent;
  vector<int> rank;
  vector<int> bipartite;
  dsu(int n) {
    parent.resize(n);
    rank.resize(n);
    bipartite.resize(n);
    for (int v = 0; v < n; v++) {
      parent[v] = {v, 0};
      rank[v] = 0;
      bipartite[v] = 1;
    }
  }
  dsu() {}
  pi find_set(int v) {
    if (v != parent[v].fir) {
      int parity = parent[v].sec;
      parent[v] = find_set(parent[v].fir);
      parent[v].sec ^= parity;
    }
    return parent[v];
  }
  void add_edge(int a, int b) {
    pi pa = find_set(a);
    a = pa.fir;
    int x = pa.sec;
    pi pb = find_set(b);
    b = pb.fir;
    int y = pb.sec;
    if (a == b) {
      if (x == y) bipartite[a] = 0;
    } else {
      if (rank[a] < rank[b]) swap(a, b);
      parent[b] = {a, x ^ y ^ 1};
      bipartite[a] &= bipartite[b];
      if (rank[a] == rank[b]) rank[a]++;
    }
  }
  bool is_bipartite(int v) { return bipartite[find_set(v).fir]; }
};
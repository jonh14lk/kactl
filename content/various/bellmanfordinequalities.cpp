struct solver {
  const int inf = 1e18;
  int n, src;
  vector<int> d;
  vector<pii> edges;
  solver(int _n)  // recebe o numero de variaveis, indexadas de 0 ate _n - 1
  {
    src = _n;  // aqui denotaremos _n como o source
    n = _n + 1;
    for (int i = 0; i < _n; i++)  // arestas de source para cada um dos vertices com custo 0
    {
      edges.pb({{src, i}, 0});
    }
  }
  bool solve()  // bellman ford
  {
    d.assign(n, inf);
    d[src] = 0;
    int x;
    for (int i = 0; i < n; i++) {
      x = -1;
      for (auto const &e : edges) {
        auto [a, b] = e.fir;
        int cost = e.sec;
        if (d[a] < inf) {
          if (d[b] > d[a] + cost) {
            d[b] = max(-inf, d[a] + cost);
            x = b;
          }
        }
      }
    }
    return (x == -1);  // false se tem ciclo negativo
  }
  void add_constraint_leq(int i, int j, int c)  // value_i - value_j <= c
  {
    edges.pb({{j, i}, c});
  };
  void add_constraint_geq(int i, int j, int c)  // value_i - value_j >= c
  {
    edges.pb({{i, j}, -c});
  };
  void add_constraint_eq(int i, int j, int c)  // value_i - value_j = c
  {
    add_constraint_leq(i, j, c);
    add_constraint_geq(i, j, c);
  };
};
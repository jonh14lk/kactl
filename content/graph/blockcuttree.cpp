struct block_cut_tree {
  // Se art[i] >= 1, i eh ponto de articulacao
  // tree - eh a propia block-cut tree
  // pos[i] responde a qual vertice da arvore vertice i pertence
  vector<vector<int>> g, blocks, tree;
  vector<vector<pi>> edgblocks;  // sao as arestas do bloco i
  stack<int> s;
  stack<pi> s2;
  vector<int> id, art, pos;

  block_cut_tree(vector<vector<int>> g_) : g(g_) {
    int n = g.size();
    id.resize(n, -1), art.resize(n), pos.resize(n);
    build();
  }
  int dfs(int i, int &t, int p = -1) {
    int lo = id[i] = t++;
    s.push(i);
    if (p != -1) {
      s2.emplace(i, p);
    }
    for (int j : g[i]) {
      if (j != p and id[j] != -1) s2.emplace(i, j);
    }
    for (int j : g[i]) {
      if (j != p) {
        if (id[j] == -1) {
          int val = dfs(j, t, i);
          lo = min(lo, val);
          if (val >= id[i]) {
            art[i]++;
            blocks.emplace_back(1, i);
            while (blocks.back().back() != j) {
              blocks.back().pb(s.top());
              s.pop();
            }
            edgblocks.emplace_back(1, s2.top());
            s2.pop();
            pi aux = {j, i};
            while (edgblocks.back().back() != aux) {
              edgblocks.back().pb(s2.top());
              s2.pop();
            }
          }
          // if (val > id[i]) aresta i-j eh ponte
        } else {
          lo = min(lo, id[j]);
        }
      }
    }
    if (p == -1 and art[i]) {
      art[i]--;
    }
    return lo;
  }
  void build() {
    int t = 0;
    for (int i = 0; i < g.size(); i++) {
      if (id[i] == -1) dfs(i, t, -1);
    }
    tree.resize(blocks.size());
    for (int i = 0; i < g.size(); i++) {
      if (art[i]) pos[i] = tree.size(), tree.emplace_back();
    }
    for (int i = 0; i < blocks.size(); i++) {
      for (int j : blocks[i]) {
        if (!art[j])
          pos[j] = i;
        else
          tree[i].pb(pos[j]), tree[pos[j]].pb(i);
      }
    }
  }
};
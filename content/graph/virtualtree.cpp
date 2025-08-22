// virtual tree
// dado um conjunto de vertices v
// montar uma arvore comprimida
// tal que escolhendo dois vertices do conjunto v[i] e v[j]
// lca(v[i], v[j]) tambem ta na arvore
// se o conjunto v tem k vertices
// entao a arvore comprimida tem menos do que 2k vertices
// O(k log(k)), sem considerar a complexidade de achar lca
int build_virt(vector<int> v) {
  auto cmp = [&](int i, int j) { return lca::tin[i] < lca::tin[j]; };
  sort(v.begin(), v.end(), cmp);
  for (int i = v.size() - 1; i > 0; i--) {
    v.pb(lca::find_lca(v[i], v[i - 1]));
  }
  sort(v.begin(), v.end(), cmp);
  v.erase(unique(v.begin(), v.end()), v.end());
  for (int i = 0; i < v.size(); i++) {
    virt[v[i]].clear();
  }
  for (int i = 1; i < v.size(); i++) {
    virt[lca::find_lca(v[i - 1], v[i])].clear();
  }
  for (int i = 1; i < v.size(); i++) {
    int parent = lca::find_lca(v[i - 1], v[i]);
    int d = lca::dist(parent, v[i]);
    virt[parent].pb({v[i], d});
  }
  return v[0];
}
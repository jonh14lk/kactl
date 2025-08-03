vector<int> adj[MAXN];
vector<int> v[MAXN];
int c[MAXN];
int cnt[MAXN];
int sz[MAXN];
void dfs_sz(int x, int p) {
  sz[x] = 1;
  for (auto const &i : adj[x]) {
    if (i != p) {
      dfs_sz(i, x);
      sz[x] += sz[i];
    }
  }
}
void modify(int c, int val) { cnt[c] += val; }
void dfs(int x, int p, bool keep) {
  int best = -1, big_child = -1;
  for (auto const &i : adj[x]) {
    if (i != p && sz[i] > best) {
      best = sz[i];
      big_child = i;
    }
  }
  for (auto const &i : adj[x]) {
    if (i != p && i != big_child) dfs(i, x, 0);
  }
  if (big_child != -1) {
    dfs(big_child, x, 1);
    swap(v[x], v[big_child]);  // O(1)
  }
  v[x].pb(x);
  modify(c[x], 1);  // adiciona
  for (auto const &i : adj[x]) {
    if (i != p && i != big_child) {
      for (auto const &j : v[i]) {
        v[x].pb(j);
        modify(c[j], 1);  // adiciona
      }
    }
  }
  // a cor c aparece cnt[c] vezes na subtree de x
  // dai vc pode fazer algo tendo essa informacao
  // seja responser queries ou algo do tipo aqui
  if (!keep) {
    for (auto const &i : v[x]) modify(c[i], -1);  // remove
  }
}
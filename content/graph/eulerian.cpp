void dfs2(int s) {  // caminho euleriano
  while (a[s].size() > 0) {
    auto v = a[s].back();
    a[s].pop_back();
    if (!vis[v.sec]) {
      vis[v.sec] = 1;
      dfs2(v.fir);
    }
  }
  path.pb(s);
}
void dfs(int i) {  // ajeitar para que todo mundo tenha grau par
  vis[i] = 1;
  for (auto const &j : adj[i]) {
    if (!vis[j.fir]) {
      dfs(j.fir);
      if (deg[j.fir]) {
        ans.pb(edges[j.sec]);
        deg[j.fir] ^= 1;
        deg[i] ^= 1;
      }
    }
  }
}
// se eu cham dfs(0) no final checar se o deg[0] ta safe
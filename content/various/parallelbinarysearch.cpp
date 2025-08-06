vector<pii> qry(q);
for (int i = 0; i < q; i++) {
  cin >> qry[i].sec.fir >> qry[i].sec.sec >> qry[i].fir;
  qry[i].sec.fir--, qry[i].sec.sec--;
}
vector<int> l(n);
vector<int> r(n);
vector<vector<int>> on(q);
for (int i = 0; i < n; i++) {
  l[i] = 0;
  r[i] = q;
}
while (1) {
  bool ok = 1;
  for (int i = 0; i < n; i++) {
    if (l[i] < r[i]) {
      ok = 0;
      int mid = (l[i] + r[i]) >> 1;
      on[mid].pb(i);
    }
  }
  if (ok) break;
  reset();
  for (int mid = 0; mid < q; mid++) {
    upd(qry[mid].sec.fir, qry[mid].sec.sec, qry[mid].fir);
    for (auto const &j : on[mid]) {
      int val = 0;
      for (auto const &k : adj[j]) {
        val += sum(k);
        if (val >= need[j]) break;
      }
      (val >= need[j]) ? r[j] = mid : l[j] = mid + 1;
    }
    on[mid].clear();
  }
}
// a resposta eh o l[i] para cada busca
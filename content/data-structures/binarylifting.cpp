item st[MAXN][21];
for (int i = 0; i < n; i++) {
  st[i][0].nxt = min(i + 1, n - 1);
  st[i][0].sum = v[st[i][0].nxt];
}
for (int i = 1; i < 21; i++) {
  for (int v = 0; v < n; v++) {
    st[v][i].nxt = st[st[v][i - 1].nxt][i - 1].nxt;
    st[v][i].sum = st[v][i - 1].sum + st[st[v][i - 1].nxt][i - 1].sum;
  }
}
while (q--) {
  int l, r;
  cin >> l >> r;
  int ans = v[l], len = r - l;
  for (int i = 20; i >= 0; i--) {
    if (len & (1 << i)) {
      ans += st[l][i].sum;
      l = st[l][i].nxt;
    }
  }
  cout << ans << endl;
}
bitset<MAXN> ans;
int gauss(vector<bitset<MAXN>>& a) {
  ans.reset();
  int n = a.size(), m = a[0].size() - 1, ret = 1;
  vector<int> where(m, -1);
  for (int col = 0, row = 0; col < m && row < n; col++) {
    for (int i = row; i < n; i++) {
      if (a[i][col]) {
        swap(a[i], a[row]);
        break;
      }
    }
    if (!a[row][col]) continue;
    where[col] = row;
    for (int i = 0; i < n; i++)
      if (i != row && a[i][col]) a[i] ^= a[row];
    ++row;
  }
  for (int i = 0; i < m; i++) {
    if (where[i] != -1)
      ans[i] = (a[where[i]][m] / a[where[i]][i]);
    else
      ret = 2;
  }
  for (int i = 0; i < n; i++) {
    double sum = 0;
    for (int j = 0; j < m; j++) sum += (ans[j] * a[i][j]);
    if (abs(sum - a[i][m]) > EPS) ret = 0;
  }
  return ret;
}
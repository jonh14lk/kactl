#define EPS 1e-9
vector<double> ans;
int gauss(vector<vector<double>> a) {
  int n = a.size(), m = a[0].size() - 1, ret = 1;
  ans.assign(m, 0);
  vector<int> where(m, -1);
  for (int col = 0, row = 0; col < m && row < n; col++, row++) {
    int sel = row;
    for (int i = row; i < n; i++)
      if (abs(a[i][col]) > abs(a[sel][col])) sel = i;
    if (abs(a[sel][col]) < EPS) continue;
    for (int i = col; i <= m; i++) swap(a[sel][i], a[row][i]);
    where[col] = row;
    for (int i = 0; i < n; i++) {
      if (i != row) {
        double c = a[i][col] / a[row][col];
        for (int j = col; j <= m; j++) a[i][j] -= a[row][j] * c;
      }
    }
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
  return ret;  // 0 = nao existe solucao, 1 = existe uma solucao, 2 = existem multiplas solucoes
}
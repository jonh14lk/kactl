namespace matrix {
vector<vector<int>> ans;
int multi(int x, int y) { return (x * y) % mod; }
int sum(int a, int b) { return (a + b >= mod) ? a + b - mod : a + b; }
vector<vector<int>> multiply(vector<vector<int>> a, vector<vector<int>> b) {
  vector<vector<int>> res(a[0].size(), vector<int>(b[0].size()));
  for (int i = 0; i < a.size(); i++) {
    for (int j = 0; j < b[0].size(); j++) {
      res[i][j] = 0;
      for (int k = 0; k < a[0].size(); k++) res[i][j] = sum(res[i][j], multi(a[i][k], b[k][j]));
    }
  }
  return res;
}
vector<vector<int>> expo(vector<vector<int>> mat, int m) {
  ans = vector<vector<int>>(mat.size(), vector<int>(mat[0].size()));
  for (int i = 0; i < mat.size(); i++)
    for (int j = 0; j < mat[0].size(); j++) ans[i][j] = (i == j);
  while (m > 0) {
    if (m & 1) ans = multiply(ans, mat);
    m = m / 2;
    mat = multiply(mat, mat);
  }
  return ans;
}
}  // namespace matrix
int v[1001][1001];
int p[1001][1001];
int qry(int x1, int y1, int x2, int y2) { return p[x2 + 1][y2 + 1] - p[x2 + 1][y1] - p[x1][y2 + 1] + p[x1][y1]; }
for (int i = 0; i < n; i++) {
  for (int j = 0; j < n; j++) {
    p[i + 1][j + 1] = p[i][j + 1] + p[i + 1][j] - p[i][j];
    p[i + 1][j + 1] += v[i][j];
  }
}
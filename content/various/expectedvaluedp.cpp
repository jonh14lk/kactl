double dp[MAXN][MAXN][MAXN];
// sushi problem
double solve(int i, int j, int k) {
  if (!i && !j && !k) return dp[i][j][k] = 0;
  if (dp[i][j][k] != -1) return dp[i][j][k];
  /*
  It is well-known from statistics that for the geometric distribution
  (counting number of trials before a success, where each independent trial is probability p)
  the expected value is i / p
  */
  double p = ((double)(i + j + k) / n);
  double ret = 1 / p;  // expected number of trials before a success
  if (i) {
    double prob = (double)i / (i + j + k);  // probabilidade de ser um prato com um sushi
    ret += (solve(i - 1, j, k) * prob);
  }
  if (j) {
    double prob = (double)j / (i + j + k);  // probabilidade de ser um prato com dois sushis
    ret += (solve(i + 1, j - 1, k) * prob);
  }
  if (k) {
    double prob = (double)k / (i + j + k);  // probabilidade de ser um prato com tres sushis
    ret += (solve(i, j + 1, k - 1) * prob);
  }
  return dp[i][j][k] = ret;
}
void compute(int l, int r, int optl, int optr, int i) {
  if (l > r) return;
  int mid = (l + r) >> 1;
  pair<int, int> ans = {1e18, -1};  // dp, k
  for (int q = optl; q <= min(mid, optr); q++) {
    if (q > 0)
      ans = min(ans, {dp[i - 1][q - 1] + cost(q, mid), q});
    else
      ans = min(ans, {cost(q, mid), q});
  }
  dp[i][mid] = ans.fir;
  compute(l, mid - 1, optl, ans.sec, i);
  compute(mid + 1, r, ans.sec, optr, i);
}
// dp[i][j] = min(dp[i - 1][k] + c(k, j)), para algum k <= j
// O(k * n * log(n))
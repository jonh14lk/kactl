pi solve(vector<int> &v, int lambda) {
  // associar um custo lambda para ser subtraido quando realizamos uma operacao
  // dp[i] - melhor profit que tivemos considerando as i primeiras posicoes
  // cnt[i] - quantas operacoes utilizamos para chegar no valor de dp[i]
  vector<int> dp(n + 1);
  vector<int> cnt(n + 1);
  dp[0] = 0;
  cnt[0] = 0;
  for (int i = 1; i <= n; i++) {
    dp[i] = dp[i - 1];
    cnt[i] = cnt[i - 1];
    int id = i - 1;
    dp[i] += v[id];
    int lo = max(0ll, id - l + 1);
    int s = dp[lo] + (id - lo + 1) - lambda;
    if (s > dp[i]) {
      dp[i] = s;
      cnt[i] = cnt[lo] + 1;
    }
  }
  return {dp[n], cnt[n]};
}
int aliens_trick(vector<int> &v) {
  int l = 0, r = n;
  while (l < r) {
    int mid = (l + r) >> 1;
    pi ans = solve(v, mid);
    (ans.sec > k) ? l = mid + 1 : r = mid;
  }
  pi ans = solve(v, l);
  return ans.fir + (l * k);
}
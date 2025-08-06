int ans = 0;
for (int i = 0; i < n; i++) {
  for (int j = 0; j < n; j++) {
    dp[i][j] = v[i][j];
    if (i && j && dp[i][j]) dp[i][j] = min({dp[i][j - 1], dp[i - 1][j], dp[i - 1][j - 1]}) + 1;
    ans = max(ans, dp[i][j]);
  }
}
cout << ans * ans << endl;
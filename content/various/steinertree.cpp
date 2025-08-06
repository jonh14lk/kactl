for (int i = 0; i <= 100; i++)
  for (int j = 0; j < (1 << 9); j++) dp[i][j] = 1e9;
for (int i = 0; i < k; i++)
  for (int j = 0; j < v.size(); j++) dp[j][1 << i] = d(cap[i], v[j]);
for (int mask = 2; mask < (1 << k); mask++) {
  for (int i = 0; i < v.size(); i++) {
    for (int mask2 = 1; mask2 < mask; mask2++) {
      if (!((mask & mask2) == mask2)) continue;
      int mask3 = mask ^ mask2;
      dp[i][mask] = min(dp[i][mask], dp[i][mask2] + dp[i][mask3]);
    }
    for (int j = 0; j < v.size(); j++) dp[j][mask] = min(dp[j][mask], dp[i][mask] + d(v[i], v[j]));
  }
}
double ans = 1e9;
for (int i = 0; i <= 100; i++) ans = min(ans, dp[i][(1 << k) - 1]);
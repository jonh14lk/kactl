vector<int> v = {2, 3, 4, 5, 6};
unordered_map<int, bool> vis;
unordered_map<int, int> dp;
int g(int x)  // achar o grundy number na marra
{
  if (x == 0) return 0;
  vector<bool> ok(4, 0);
  int mex = 0;
  for (auto const &i : v) {
    int curr = g(x / i);
    if (curr < 4) ok[curr] = 1;
    while (ok[mex]) mex++;
  }
  vis[x] = 1;
  return dp[x] = mex;
}
int n;
cin >> n;
int x = 0;
for (int i = 0; i < n; i++) {
  int k;
  cin >> k;
  x ^= solve(k);
}
(x > 0) ? cout << "Henry\n" : cout << "Derek\n";
// nim classico -> o jogador que comeca ganha se o xor dos tamanhos das pilhas for != 0
// teorema sprague-grundy (transformar um jogo qualquer em nim)
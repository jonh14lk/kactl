bitset<MAXN> prime;
vector<int> nxt(MAXN);
vector<int> factors;
void crivo() {
  prime.set();
  prime[0] = false, prime[1] = false;
  for (int i = 2; i < MAXN; i++) {
    if (prime[i]) {
      nxt[i] = i;
      for (int j = 2; j * i < MAXN; j++) {
        prime[j * i] = false;
        nxt[j * i] = i;
      }
    }
  }
}
void fact(int n) {
  factors.clear();
  while (n > 1) {
    factors.pb(nxt[n]);
    n = n / nxt[n];
  }
}
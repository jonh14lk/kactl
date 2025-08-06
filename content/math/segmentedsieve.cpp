vector<int> prime;
void segmentedsieve(int l, int r) {
  int lim = sqrt(r);
  vector<bool> mark(lim + 1, false);
  vector<int> primes;
  for (int i = 2; i <= lim; ++i) {
    if (!mark[i]) {
      primes.pb(i);
      for (int j = i * i; j <= lim; j += i) mark[j] = true;
    }
  }
  vector<bool> isprime(r - l + 1, true);
  for (int i : primes)
    for (int j = max(i * i, (l + i - 1) / i * i); j <= r; j += i) isprime[j - l] = false;
  if (l == 1) isprime[0] = false;
  for (int i = 0; i < isprime.size(); i++)
    if (isprime[i]) prime.pb(i + l);
}
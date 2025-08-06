vector<int> facts;
void primefactors(int n) {
  while (n % 2 == 0) {
    facts.pb(2);
    n = n / 2;
  }
  for (int i = 3; i <= sqrt(n); i += 2) {
    while (n % i == 0) {
      facts.pb(i);
      n = n / i;
    }
  }
  if (n > 2) facts.pb(n);
}
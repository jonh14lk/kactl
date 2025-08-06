vector<pi> eq;
map<int, int> by_mod;
// quero checar se existe solucao para o sistema das equacoes que ja adicionei
// junto da equacao curr
// geralmente da pra fazer algo como if (check(curr)) { add(curr); }
bool check(pi curr) {
  if (by_mod.find(curr.sec) != by_mod.end()) {
    return by_mod[curr.sec] == curr.fir;
  }
  for (auto [x, mod] : eq) {
    if ((curr.fir - x) % __gcd(curr.sec, mod)) return 0;
  }
  return 1;
}
void add(pi curr) {  // [valor, mod]
  eq.pb(curr);
  by_mod[curr.sec] = curr.fir;
}
// quando tem algo de sqrt mods distintos ou algo do tipo
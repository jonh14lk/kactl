vector<pair<char, char>> ans;
void solve(int n, char a, char b, char c) {
  if (n == 0) return;
  solve(n - 1, a, c, b);
  ans.pb({a, b});
  solve(n - 1, c, b, a);
}
// chamar pra sol
solve(n, 'A', 'C', 'B');
// 3 pilhas, sendo a pilha A com n discos e as outras duas pilhas vazias
// quero mover todo mundo da pilha A para a pilha C
// em cada movimento, vc tira o disco do topo de uma pilha e poe no topo de outra pilha
// desde que o raio do disco seja menor do que o raio do disco que ta no topo da outra pilha
// os n discos tem raios distintos aos pares
// e printar os movimentos em um par [to, from]
// numero minimo pra resolver pros primeiros n
// 1, 3, 7, 15, 31, 63, 127, 255
// f(n) = 2^n - 1
for (int l = 1, r; l <= n; l = r + 1) {
  // todos os numeros i no intervalo [l, r] possuem (n / i) == x
  r = n / (n / l);
  int x = (n / l);
}
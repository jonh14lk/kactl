// nesse caso, f[x] eh a funcaoo que soma:
// todos os a[i], tal que, (x & i) == i)
for (int mask = 0; mask < (1 << m); mask++) {
  f[mask] = a[mask];
}
for (int i = 0; i < m; ++i) {
  for (int mask = 0; mask < (1 << m); mask++) {
    if (mask & (1 << i)) f[mask] += f[mask ^ (1 << i)];
  }
}
// nesse caso, f[x] eh a funcao que soma:
// todos os a[i], tal que, (x & i) == x)
for (int mask = 0; mask < (1 << m); mask++) {
  f[mask] = a[mask];
}
for (int i = 0; i < m; ++i) {
  for (int mask = 0; mask < (1 << m); mask++) {
    if (!(mask & (1 << i))) f[mask] += f[mask ^ (1 << i)];
  }
}
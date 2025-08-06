// quantidade de bits setados na mask
cout << __builtin_popcount(mask) << endl;
// quando eh necessario percorrer todas as submasks ate (1 << n)
// e fazer algo com todas as submasks dessa mask O(3^n)
for (int m = 0; m < (1 << n); m++) {
  for (int s = m; s; s = (s - 1) & m) {
    // alguma coisa aqui sabendo que mask s eh uma submask de m
  }
}
// comprimindo as masks de um vector baseada em uma mask qualquer
for (int i = 0; i < masks.size(); i++) {
  int compressed = 0, curr_bit = 0;
  for (int j = 0; j < n; j++) {
    if (!(mask & (1LL << j))) continue;
    if (masks[i] & (1LL << j)) compressed |= (1LL << curr_bit);
    curr_bit++;
  }
  // alguma coisa sabendo que a mask compressed eh a mask comprimida da mask atual
}
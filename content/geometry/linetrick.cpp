pi get_line(pi x, pi y) {  // um jeito normalizado de representar a reta entre 2 pontos
  int xx = x.fir - y.fir;
  int yy = x.sec - y.sec;
  int g = __gcd(abs(xx), abs(yy));
  if (g != 0) {
    xx /= g, yy /= g;
  }
  if (xx < 0) {
    xx *= -1;
    yy *= -1;
  }
  return {xx, yy};
}
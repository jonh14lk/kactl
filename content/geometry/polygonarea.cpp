double area(vector<pi> fig) {
  double res = 0;
  for (unsigned i = 0; i < fig.size(); i++) {
    pi p = i ? fig[i - 1] : fig.back();
    pi q = fig[i];
    res += (p.fir - q.fir) * (p.sec + q.sec);
  }
  return fabs(res) / 2;
}
int cross(pi a, pi b) { return a.fir * b.sec - a.sec * b.fir; }
double area2(vector<pi> fig) {
  double res = 0;
  for (unsigned i = 0; i < fig.size(); i++) {
    pi p = i ? fig[i - 1] : fig.back();
    pi q = fig[i];
    res += cross(p, q);
  }
  return fabs(res) / 2;
}
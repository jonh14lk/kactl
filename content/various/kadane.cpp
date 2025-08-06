int kadane(vector<int> v) {
  int n = v.size(), ans = 0, max_here = 0;
  for (int i = 0; i < n; i++) {
    max_here += v[i];
    if (ans < max_here) ans = max_here;
    if (max_here < 0) max_here = 0;
  }
  return ans;
}
int kadane_circular(vector<int> v) {
  int n = v.size(), max_kadane = kadane(v);
  int max_wrap = 0, i;
  for (i = 0; i < n; i++) {
    max_wrap += v[i];
    v[i] = -v[i];
  }
  max_wrap += kadane(v);
  return max(max_wrap, max_kadane);
}
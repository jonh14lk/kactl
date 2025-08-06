stack<pi> s;
for (int i = n - 1; i >= 0; i--) {
  while (!s.empty() && s.top().fir <= v[i]) s.pop();
  (!s.empty()) ? ans[i] = s.top().sec : ans[i] = -1;
  s.push({v[i], i});
}
// for each index (0 <= i < n), find another index (0 <= j < n)
// which v[j] > v[i] and j > i and j is as close as possible to i
// if this index does not exist, print -1
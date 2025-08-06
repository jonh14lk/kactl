namespace min_queue {
deque<pi> q;
int l, r;

void init() {
  l = r = 1;
  q.clear();
}
void push(int v) {
  while (!q.empty() && v < q.back().fir) q.pop_back();
  q.pb({v, r});
  r++;
}
void pop() {
  if (!q.empty() && q.front().sec == l) q.pop_front();
  l++;
}
int getmin() { return q.front().fir; }
}  // namespace min_queue
struct segtree {
  int n;
  vector<int> seg;
  int neutral() { return 0; }
  int merge(int a, int b) { return a + b; }
  void build(vector<int> &v) {
    n = 1;
    while (n < v.size()) n <<= 1;
    seg.assign(n << 1, neutral());
    for (int i = 0; i < v.size(); i++) seg[i + n] = v[i];
    for (int i = n - 1; i; i--) seg[i] = merge(seg[i << 1], seg[(i << 1) | 1]);
  }
  void upd(int i, int value) {
    seg[i += n] += value;
    for (i >>= 1; i; i >>= 1) seg[i] = merge(seg[i << 1], seg[(i << 1) | 1]);
  }
  int qry(int l, int r) {
    int ansl = neutral(), ansr = neutral();
    for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
      if (l & 1) ansl = merge(ansl, seg[l++]);
      if (r & 1) ansr = merge(seg[--r], ansr);
    }
    return merge(ansl, ansr);
  }
};
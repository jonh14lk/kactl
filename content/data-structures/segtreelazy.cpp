struct segtree {
  int n;
  vector<int> v;
  vector<int> seg;
  vector<int> lazy;
  segtree(int sz) {
    n = sz;
    seg.assign(4 * n, 0);
    lazy.assign(4 * n, 0);
  }
  int single(int x) { return x; }
  int neutral() { return 0; }
  int merge(int a, int b) { return a + b; }
  void add(int i, int l, int r, int diff) {
    seg[i] += (r - l + 1) * diff;
    if (l != r) {
      lazy[i << 1] += diff;
      lazy[(i << 1) | 1] += diff;
    }
    lazy[i] = 0;
  }
  void update(int i, int l, int r, int ql, int qr, int diff) {
    if (lazy[i]) add(i, l, r, lazy[i]);
    if (l > r || l > qr || r < ql) return;
    if (l >= ql && r <= qr) {
      add(i, l, r, diff);
      return;
    }
    int mid = (l + r) >> 1;
    update(i << 1, l, mid, ql, qr, diff);
    update((i << 1) | 1, mid + 1, r, ql, qr, diff);
    seg[i] = merge(seg[i << 1], seg[(i << 1) | 1]);
  }
  int query(int l, int r, int ql, int qr, int i) {
    if (lazy[i]) add(i, l, r, lazy[i]);
    if (l > r || l > qr || r < ql) return neutral();
    if (l >= ql && r <= qr) return seg[i];
    int mid = (l + r) >> 1;
    return merge(query(l, mid, ql, qr, i << 1), query(mid + 1, r, ql, qr, (i << 1) | 1));
  }
  void build(int l, int r, int i) {
    if (l == r) {
      seg[i] = single(v[l]);
      return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, i << 1);
    build(mid + 1, r, (i << 1) | 1);
    seg[i] = merge(seg[i << 1], seg[(i << 1) | 1]);
  }
  int qry(int l, int r) { return query(0, n - 1, l, r, 1); }
  void upd(int l, int r, int x) { update(1, 0, n - 1, l, r, x); }
};
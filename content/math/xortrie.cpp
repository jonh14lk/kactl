struct node {
  int me, cnt, id;
  int down[2];
  node(int c = 0) : me(c) {
    cnt = 0;
    id = -1;
    fill(begin(down), end(down), -1);
  }
};
struct trie_xor {
  vector<node> t;
  trie_xor() { t.resize(1); }
  void add(int n, int id) {
    int v = 0;
    t[v].cnt++;
    for (int i = 30; i >= 0; i--) {
      int bit = (n & (1 << i)) ? 1 : 0;
      if (t[v].down[bit] == -1) {
        t[v].down[bit] = t.size();
        t.emplace_back(bit);
      }
      v = t[v].down[bit];
      t[v].cnt++;
    }
    t[v].id = id;
  }
  void rem(int n, int id) {
    int v = 0;
    t[v].cnt--;
    for (int i = 30; i >= 0; i--) {
      int bit = (n & (1 << i)) ? 1 : 0;
      v = t[v].down[bit];
      t[v].cnt--;
    }
  }
  int qry(int n)  // maximum xor with n
  {
    if (t[0].cnt == 0)  // no element
      return -1;
    int v = 0;
    for (int i = 30; i >= 0; i--) {
      int bit = (n & (1 << i)) ? 0 : 1;
      int nxt = t[v].down[bit];
      if (nxt != -1 && t[nxt].cnt > 0)
        v = nxt;
      else
        v = t[v].down[bit ^ 1];
    }
    return t[v].id;
  }
};
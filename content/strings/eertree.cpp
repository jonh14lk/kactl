struct eertree {
  vector<vector<int>> t;
  int n, last, sz;
  vector<int> s, len, link, qt;
  eertree(int N) {
    t = vector(N + 2, vector<int>(26, 0));
    s = len = link = qt = vector<int>(N + 2);
    s[0] = -1;
    link[0] = 1, len[0] = 0, link[1] = 1, len[1] = -1;
    sz = 2, last = 0, n = 1;
  }
  int add(char c) {
    int ret = -1;
    s[n++] = c -= 'a';
    while (s[n - len[last] - 2] != c) last = link[last];
    if (!t[last][c]) {
      int prev = link[last];
      while (s[n - len[prev] - 2] != c) prev = link[prev];
      link[sz] = t[prev][c];
      len[sz] = len[last] + 2;
      ret = len[sz];
      t[last][c] = sz++;
    }
    qt[last = t[last][c]]++;
    return ret;
  }
  int size() { return sz - 2; }
  int propagate() {
    int ret = 0;
    for (int i = n; i > 1; i--) {
      qt[link[i]] += qt[i];
      ret += qt[i];
    }
    return ret;
  }
  vector<pi> get_palindromes(string &s) {
    vector<pi> ans;
    for (int i = 0; i < s.size(); i++) {
      int len = add(s[i]);
      if (len != -1) ans.pb({i - len + 1, i});
    }
    return ans;
  }
};
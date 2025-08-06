namespace sa {
struct state {
  int len, suf_link;
  map<char, int> nxt;
};
vector<int> term;
state st[2 * MAXN];
int dp[2 * MAXN];
int sz, last;
void init() {
  memset(dp, -1, sizeof(dp));
  st[0].len = 0;
  st[0].suf_link = -1;
  sz++;
  last = 0;
}
void get_link(int curr, int p, char c) {
  while (p != -1 && !st[p].nxt.count(c)) {
    st[p].nxt[c] = curr;
    p = st[p].suf_link;
  }
  if (p == -1) {
    st[curr].suf_link = 0;
    return;
  }
  int q = st[p].nxt[c];
  if (st[p].len + 1 == st[q].len) {
    st[curr].suf_link = q;
    return;
  }
  int clone = sz;
  sz++;
  st[clone].len = st[p].len + 1;
  st[clone].nxt = st[q].nxt;
  st[clone].suf_link = st[q].suf_link;
  while (p != -1 && st[p].nxt[c] == q) {
    st[p].nxt[c] = clone;
    p = st[p].suf_link;
  }
  st[q].suf_link = clone;
  st[curr].suf_link = clone;
}
void build(string &s) {
  for (auto const &c : s) {
    int curr = sz;
    sz++;
    st[curr].len = st[last].len + 1;
    get_link(curr, last, c);
    last = curr;
  }
  // achar os estados terminais
  // um estado terminal eh aquele que representa um sufixo da string s
  int p = last;
  while (p != -1) {
    term.pb(p);
    p = st[p].suf_link;
  }
}
void dfs2(int v) {
  if (dp[v] != -1) return;
  dp[v] = 1;
  for (auto const &u : st[v].nxt) {
    if (!u.sec) continue;
    dfs2(u.sec);
    dp[v] += dp[u.sec];
  }
}
void dfs(int v, int k, int &at, string &curr) {
  if (at == k) return;
  for (auto const &u : st[v].nxt) {
    if (!u.sec) continue;
    if (at + dp[u.sec] < k) {
      at += dp[u.sec];
      continue;
    }
    curr.pb(u.fir);
    at++;
    dfs(u.sec, k, at, curr);
    if (at == k) return;
    curr.pop_back();
  }
}
void find_kth(int k) {
  int at = 0;
  string curr = "";
  dfs(0, k, at, curr);
  cout << curr << endl;
}
}  // namespace sa
// chamar sa::init(); e sa::build(s);
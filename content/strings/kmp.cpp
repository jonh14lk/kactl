string s;
int n, m;
string a, b;
int c[MAXN][26];
vector<int> kmp(string &s) {
  int n = s.size();
  vector<int> p(n);
  for (int i = 1; i < n; i++) {
    int j = p[i - 1];
    while (j > 0 && s[i] != s[j]) j = p[j - 1];
    if (s[i] == s[j]) j++;
    p[i] = j;
  }
  return p;
}
void compute(string s) {
  s.pb('*');
  vector<int> p = kmp(s);
  for (int i = 0; i < s.size(); i++) {
    for (int cc = 0; cc < 26; cc++) {
      int j = i;
      while (j > 0 && 'a' + cc != s[j]) j = p[j - 1];
      if ('a' + cc == s[j]) j++;
      c[i][cc] = j;
    }
  }
}
const int inf = 1e15;
struct color_upd {
#define left fir
#define right sec.fir
#define color sec.sec
  set<pii> ranges;
  vector<pii> erased;
  color_upd(int n)  // inicialmente, todo mundo pintado com a cor inf
  {
    // nao usar cores negativas!!!!!!!!!
    ranges.insert({0, {n - 1, inf}});
  }
  int get(int i) {
    auto it = ranges.upper_bound({i, {1e18, 1e18}});
    if (it == ranges.begin()) return -1;
    it--;
    return (*(it)).color;
  }
  void del(int l, int r)  // apaga o intervalo [l, r]
  {
    erased.clear();
    auto it = ranges.upper_bound({l, {0, 0}});
    if (it != ranges.begin()) {
      it--;
    }
    while (it != ranges.end()) {
      if ((*(it)).left > r)
        break;
      else if ((*(it)).right >= l)
        erased.push_back(*it);
      it++;
    }
    if (erased.size() > 0) {
      int sz = erased.size();
      auto it = ranges.lower_bound({erased[0].left, {0, 0}});
      auto it2 = ranges.lower_bound({erased[sz - 1].left, {0, 0}});
      pii ini = *it, fim = *it2;
      it2++;
      ranges.erase(it, it2);
      pii upd1 = {ini.left, {l - 1, ini.color}};
      pii upd2 = {r + 1, {fim.right, fim.color}};
      erased[0].left = max(erased[0].left, l);
      erased[sz - 1].right = min(erased[sz - 1].right, r);
      if (upd1.left <= upd1.right) ranges.insert(upd1);
      if (upd2.left <= upd2.right) ranges.insert(upd2);
    }
  }
  void add(int a, int b, int c) {
    auto it = ranges.lower_bound({a, {b, 0}});
    pii aa = {-1, {-1, -1}};
    pii bb = {-1, {-1, -1}};
    if (it != ranges.end()) {
      if ((*it).color == c && (*it).left == b + 1) {
        aa = *it;
        b = (*it).right;
      }
    }
    if (it != ranges.begin()) {
      it--;
      if ((*it).color == c && (*it).right == a - 1) {
        bb = *it;
        a = (*it).left;
      }
    }
    ranges.erase(aa);
    ranges.erase(bb);
    ranges.insert({a, {b, c}});
  }
  void upd(int a, int b, int c)  // pinta o intervalo [a, b] com a cor c
  {
    del(a, b);
    add(a, b, c);
  }
};
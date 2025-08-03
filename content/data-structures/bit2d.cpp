struct bit2d {
  vector<int> ord;
  vector<vector<int>> t;
  vector<vector<int>> coord;
  bit2d(vector<pi> &pts)  // recebe todos os pontos que vao ser inseridos pra construir, mas nao insere eles
  {
    sort(pts.begin(), pts.end());
    for (auto const &a : pts) {
      if (ord.empty() || a.fir != ord.back()) ord.pb(a.fir);
    }
    t.resize(ord.size() + 1);
    coord.resize(t.size());
    for (auto &a : pts) {
      swap(a.fir, a.sec);
    }
    sort(pts.begin(), pts.end());
    for (auto &a : pts) {
      swap(a.fir, a.sec);
      for (int on = upper_bound(ord.begin(), ord.end(), a.fir) - ord.begin(); on < t.size(); on += on & -on) {
        if (coord[on].empty() || coord[on].back() != a.sec) coord[on].push_back(a.sec);
      }
    }
    for (int i = 0; i < t.size(); i++) t[i].assign(coord[i].size() + 1, 0);
  }
  void add(int x, int y, int v)  // v[a][b] += v
  {
    for (int xx = upper_bound(ord.begin(), ord.end(), x) - ord.begin(); xx < t.size(); xx += xx & -xx) {
      for (int yy = upper_bound(coord[xx].begin(), coord[xx].end(), y) - coord[xx].begin(); yy < t[xx].size();
           yy += yy & -yy)
        t[xx][yy] += v;
    }
  }
  int qry(int x, int y)  // soma de todos os v[a][b] com (a <= x && b <= y)
  {
    int ans = 0;
    for (int xx = upper_bound(ord.begin(), ord.end(), x) - ord.begin(); xx > 0; xx -= xx & -xx) {
      for (int yy = upper_bound(coord[xx].begin(), coord[xx].end(), y) - coord[xx].begin(); yy > 0; yy -= yy & -yy)
        ans += t[xx][yy];
    }
    return ans;
  }
  int qry2(int x1, int y1, int x2, int y2) {
    return qry(x2, y2) - qry(x2, y1 - 1) - qry(x1 - 1, y2) + qry(x1 - 1, y1 - 1);
  }
  void add2(int x1, int y1, int x2, int y2, int v) {
    add(x1, y1, v);
    add(x1, y2 + 1, -v);
    add(x2 + 1, y1, -v);
    add(x2 + 1, y2 + 1, v);
  }
};
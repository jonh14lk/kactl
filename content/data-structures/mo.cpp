namespace mo {
struct query {
  int idx, l, r;
};
int block;
vector<query> queries;
vector<int> ans;
// bool cmp(query &x, query &y){  essa funcao de ordenacao pode funcionar em caso de TLE
//   int ablock = x.l / MAGIC, bblock = y.l / MAGIC;
//   if (ablock != bblock) return ablock < bblock;
//   if (ablock & 1) return x.r < y.r;
//   return x.r > y.r;
// }
bool cmp(query &x, query &y) {
  if (x.l / block != y.l / block) return x.l / block < y.l / block;
  return x.r < y.r;
}
void run() {
  block = (int)sqrt(n);
  sort(queries.begin(), queries.end(), cmp);
  ans.resize(queries.size());
  int cl = 0, cr = -1, sum = 0;
  auto add = [&](int x) { sum += x; };
  auto rem = [&](int x) { sum -= x; };
  for (int i = 0; i < queries.size(); i++) {
    while (cl > queries[i].l) {
      cl--;
      add(v[cl]);
    }
    while (cr < queries[i].r) {
      cr++;
      add(v[cr]);
    }
    while (cl < queries[i].l) {
      rem(v[cl]);
      cl++;
    }
    while (cr > queries[i].r) {
      rem(v[cr]);
      cr--;
    }
    ans[queries[i].idx] = sum;
  }
}
}  // namespace mo
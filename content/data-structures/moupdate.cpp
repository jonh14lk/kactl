int n, q;
int v[MAXN];
int vv[MAXN];
namespace mo {
struct query {
  int idx, l, r, t;
};
struct update {
  int i, prevx, x;
};
int block;
vector<query> queries;
vector<update> updates;
vector<int> ans;
bool cmp(query x, query y) {
  if (x.l / block != y.l / block) return x.l / block < y.l / block;
  if (x.r / block != y.r / block) return x.r / block < y.r / block;
  return x.t < y.t;
}
void run() {
  block = 3153;  // (2 * n) ^ 0.666
  sort(queries.begin(), queries.end(), cmp);
  ans.resize(queries.size());
  int cl = 0, cr = -1, sum = 0, t = 0;
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
    while (t > queries[i].t) {
      t--;
      if (queries[i].l <= updates[t].i && queries[i].r >= updates[t].i) {
        rem(updates[t].x);
        add(updates[t].prevx);
      }
      v[updates[t].i] = updates[t].prevx;
    }
    while (t < queries[i].t) {
      if (queries[i].l <= updates[t].i && queries[i].r >= updates[t].i) {
        rem(updates[t].prevx);
        add(updates[t].x);
      }
      v[updates[t].i] = updates[t].x;
      t++;
    }
    ans[queries[i].idx] = sum;
  }
}
}  // namespace mo
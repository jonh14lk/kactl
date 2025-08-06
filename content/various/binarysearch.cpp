// busca ternaria para int, usando busca binaria:
int l = 0, r = 1e9;
while (l < r) {
  int mid = (l + r) >> 1;
  (calc(mid) < calc(mid + 1)) ? r = mid : l = mid + 1;
}
return calc(l);
// first element >= x
int lower(int l, int r, int x)  // first element >= x
{
  while (l < r) {
    //  int mid = l + (r - l) / 2; se tiver numero negativo
    int mid = (l + r) >> 1;
    (x <= k[mid]) ? r = mid : l = mid + 1;
  }
  return k[l];
}
// last element <= x
vector<int> k(MAXN);
int upper(int l, int r, int x) {
  while (l < r) {
    int mid = (l + r + 1) >> 1;
    (k[mid] <= x) ? l = mid : r = mid - 1;
  }
  return k[l];
}
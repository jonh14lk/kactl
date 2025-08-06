int lis() {
  vector<int> q;
  for (int i = 0; i < v.size(); i++) {
    vector<int>::iterator it = lower_bound(q.begin(), q.end(), v[i]);
    if (it == q.end())
      q.pb(v[i]);
    else
      *it = v[i];
  }
  for (int i = 0; i < q.size(); i++) cout << q[i] << " ";
  cout << endl;
  return q.size();
}
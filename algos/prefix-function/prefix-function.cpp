vector<int> prefix_function(string s) {
  vector<int> p(s.size());
  for (int i = 1; i < s.size(); ++i) {
    p[i] = p[i - 1];
    while (p[i] && s[p[i]] != s[i]) p[i] = p[p[i] - 1];
    p[i] += s[i] == s[p[i]];
  }
  return p;
}
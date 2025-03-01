struct palindromic{
  int n;
  vector<int> p, suf{0, 0}, len{-1, 0};
  vector<array<int, alpha>> to{{}, {}};
  int sz = 2;

  palindromic(const string &s) : n(s.size()), p(n + 1, 1) {
    suf.reserve(n);
    len.reserve(n);
    for (int i = 0; i < n; ++i) {
      auto check = [&](int l) { return i > l && s[i] == s[i - l - 1]; };
      int par = p[i];
      while (!check(len[par])) par = suf[par];
      if (to[par][s[i] - a]) {
        p[i + 1] = to[par][s[i] - a];
        continue;
      }
      p[i + 1] = sz++;
      to[par][s[i] - a] = p[i + 1];
      to.emplace_back();
      len.emplace_back(len[par] + 2);
      do {
        par = suf[par];
      } while (!check(len[par]));
      int link = to[par][s[i] - a];
      if (link == p[i + 1]) link = 1;
      suf.emplace_back(link);
    }
  }
};
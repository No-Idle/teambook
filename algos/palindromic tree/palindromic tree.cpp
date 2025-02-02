struct palindromic{
  int n;
  vector<int> p, suf{0, 0}, len{-1, 0}, d{0, 1}, jump{0, 1}; 
  //d[u] is a difference of lengths of u and suf[u], go is jump by chain constant d
  vector<array<int, alpha>> to{{}, {}};
  int sz = 2;
  palindromic(const string &s) : n(s.size()), p(n + 1, 1) {
    suf.reserve(n);
    len.reserve(n);
    d.reserve(n);
    jump.reserve(n);
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
      d.emplace_back(len[p[i + 1]] - len[link]);
      if (link != 0 && d[link] == d.back()) {
        jump.emplace_back(jump[link]);
      }
      else {
        jump.emplace_back(link);
      }
    }
  }
  int partition() {
    vector <int> dp(n + 1, n), last(sz);
    dp[0] = 0;
    for (int i = 1; i <= n; ++i) {
      int u = p[i];
      while (len[u] > 0) {
        if (jump[u] == suf[u]) {
          dp[i] = min(dp[i], dp[i - len[u]] + 1);
          last[u] = dp[i - len[u]];
        }
        else {
          int j = i - d[u];
          int x = min(last[suf[u]], dp[j - len[jump[u]]]);
          dp[i] = min(dp[i], x + 1);
          last[u] = x;
        }
        u = jump[u];
      }
    }
    return dp.back();
  }
};

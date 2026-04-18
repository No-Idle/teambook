pair<int, vector<int>> solve(int n, vector<edge> ed, int s, bool recover) {
  auto cmp = [&](int i, int j) { return ed[i][2] > ed[j][2]; };
  vector r(n, pq<int, decltype(cmp)>(cmp));
  for (auto [u, v, w, i] : ed) r[v].push(i);
  vector<int> mod(n), p(n), color(n), take;
  iota(all(p), 0);
  auto get = [&](int u) {
    while (u != p[u]) u = p[u] = p[p[u]];
    return u;
  };
  auto unite = [&](int x, int y) {
    x = get(x), y = get(y);
    if (x == y) return;
    if (r[x].size() > r[y].size()) swap(x, y);
    p[x] = y;
    while (r[x].size()) {
      auto e = r[x].top();
      r[x].pop();
      ed[e][2] += mod[x] - mod[y];
      r[y].push(e);
    }
  };
  vector<vector<pair<int, int>>> g(n);
  int ans = 0;
  color[s] = 2;
  auto go = [&](int cur) {
    vector<pair<int, int>> stack;
    int time = 0;
    while (color[cur] < 2) {
      color[cur] = 1;
      edge e;
      do {
        e = ed[r[cur].top()];
        r[cur].pop();
      } while (get(e[0]) == cur);
      e[2] += mod[cur];
      ans += e[2];
      mod[cur] -= e[2];
      stack.push_back({cur, e[3]});
      int a = get(e[0]);
      if (color[a] == 1) {
        while (true) {
          auto [nxt, i] = stack.back();
          stack.pop_back();
          g[ed[i][0]].push_back({time++, i});
          unite(nxt, cur);
          if (nxt == a) break;
        }
      }
      cur = get(e[0]);
    }
    for (auto [x, i] : stack) {
      color[x] = 2;
    }
    if (recover) {
      pq<pair<int, int>, greater<>> d;
      for (auto [x, i] : stack) {
        d.emplace(-1, i);
      }
      while (!d.empty()) {
        auto [t, i] = d.top();
        d.pop();
        if (color[ed[i][1]] == 3) {
          continue;
        }
        color[ed[i][1]] = 3;
        take.push_back(i);
        for (auto [t2, i2] : g[ed[i][1]]) {
          d.emplace(t2, i2);
        }
      }
    }
  };
  for (int i = 0; i < n; ++i) go(get(i));
  return {ans, take};
}
//534b4e

vector<int> euler(vector<vector<pair<int, int>>> g) {  // pair{nxt, idx}
  int n = g.size();
  vector<pair<int, int>> e(p.size());
  // build graph
  vector<int> in(n), out(n);
  for (auto [u, v] : e) in[v]++, out[u]++;
  vector<int> used(m), it(n), cycle;
  auto dfs = [&](auto dfs, int cur) -> void {
    while (true) {
      while (it[cur] < g[cur].size() && used[g[cur][it[cur]].second]) it[cur]++;
      if (it[cur] == g[cur].size()) return;
      auto [nxt, idx] = g[cur][it[cur]];
      used[idx] = true;
      dfs(dfs, nxt);
      cycle.push_back(idx);
    }
  };
  int cnt = 0, odd = -1;
  for (int i = 0; i < n; ++i){
    if (out[i] && odd == -1) odd = i;
    if (in[i] != out[i]) {
      if (in[i] + 1 == out[i]) odd = i;
      if (abs(in[i] - out[i]) > 1) return {}; // must hold
      cnt++;
    }
  }
  if (cnt != 0 && cnt != 2) return {}; // must hold
  // for undirected find odd vertex (and count that # of odd is 0 or 2)
  dfs(dfs, odd);
  reverse(cycle.begin(), cycle.end());
  if (cycle.size() != m) return {};
  return cycle;
}
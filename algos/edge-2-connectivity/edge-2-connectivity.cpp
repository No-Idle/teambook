int n, m;
cin >> n >> m;
vector <vector <int> > g(n + 1);
map <pair <int, int>, int> comp, col;
for (int i = 0; i < m; ++i) {
  int u, v, c; cin >> u >> v >> c;c--;
  col[{u,v}]=col[{v,u}]=c;
  g[u].push_back(v);
  g[v].push_back(u);
}
vector <int> used(n + 1);
vector <int> newCompWithoutParent(n + 1), h(n + 1), up(n + 1);
auto findCutPoints = [&] (auto self, int u, int p) -> void {
  used[u] = 1;
  up[u] = h[u];
  for (int v : g[u]) {
    if (!used[v]) {
      h[v] = h[u] + 1;
      self(self, v, u);
      up[u] = min(up[u], up[v]);
      if (up[v] >= h[u]) {
        newCompWithoutParent[v] = 1;
      }
    }
    else {
      up[u] = min(up[u], h[v]);
    }
  }
};
for (int u = 1; u <= n; ++u) {
  if (!used[u]) {
    findCutPoints(findCutPoints, u, u);
  }
}
int ptr = 0;
vector <map <int, int> > colors(m);
auto markComponents = [&] (auto self, int u, int cur) -> void {
  used[u] = 1;
  for (int v : g[u]) {
    if (!used[v]) {
      if (newCompWithoutParent[v]) {
        ptr++;
        self(self, v, ptr - 1);
      }
      else {
        self(self, v, cur);
      }
    }
    else if (h[v] < h[u]) {
      comp[{u,v}]=comp[{v,u}]=cur;
      int c = col[{u,v}];
      colors[cur][u] |= 1 << c;
      colors[cur][v] |= 1 << c;
    }
  }
};
used.assign(n + 1, 0);
for (int u = 1; u <= n; ++u) {
  if (!used[u]) {
    markComponents(markComponents, u, -1);
  }
}
for (int comp = 0; comp < m; ++comp) {
  vector <int> cnt(4);
  int tot = 0;
  for (auto [u, mask] : colors[comp]) {
    tot |= mask;
    cnt[bp(mask)]++;
  }
  if (bp(tot)<3) {
    continue;
  }
  if (cnt[2] || cnt[3]>2) {
    cout << "Yes" << endl;
    return;
  }
}
cout << "No" << endl;
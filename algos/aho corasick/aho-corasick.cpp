const int alpha = 26;
const char a = 'a';

struct node{
  int next[alpha] = {}, link[alpha] = {};
  int suf = 0;
  int visited = 0, ans = 0;
  int bad = 0; // any term is reachable by suf links
  vector<int> term;
  node() {
    fill(next, next + alpha, -1);
  }
};

vector<node> mem;

int get_next_or_create(int nd, char c) {
  if (mem[nd].next[c - a] == -1) { mem[nd].next[c - a] = mem.size(); mem.emplace_back(); }
  return mem[nd].next[c - a];
}

void build(vector<string> t) {
  mem.reserve(1e6 + 100);mem.clear();
  mem.emplace_back();
  // -1st element is nullptr, 0th is the root
  for (int j = 0; j < t.size(); ++j) {
    int cur = 0;
    for (char c : t[j]) cur = get_next_or_create(cur, c);
    mem[cur].term.push_back(j);
  }
  vector<int> bfs_order;
  queue<int> bfs;
  {
    node &root = mem[0];
    root.suf = 0;
    for (char c = a; c < a + alpha; ++c) {
      root.link[c - a] = (root.next[c - a] == -1 ? 0 : root.next[c - a]);
    }
    bfs.push(0);
  }
  while (!bfs.empty()) {
    int cur_idx = bfs.front();
    bfs.pop();
    node &cur = mem[cur_idx];
    cur.bad = cur.term.size() > 0 || mem[cur.suf].bad;
    bfs_order.push_back(cur_idx);
    for (char c = a; c < a + alpha; ++c) {
      int nxt_idx = cur.next[c - a];
      if (nxt_idx == -1) continue;
      node &nxt = mem[nxt_idx];
      nxt.suf = (cur_idx ? mem[cur.suf].link[c - a] : 0);
      for (char c = a; c < a + alpha; ++c) {
        nxt.link[c - a] = (nxt.next[c - a] == -1 ? mem[nxt.suf].link[c - a] : nxt.next[c - a]);
      }
      bfs.push(nxt_idx);
    }
  }
  // do something
}
//be16ed

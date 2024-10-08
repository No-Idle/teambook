template<typename T, typename U>
struct SegmentTree {
  int h, n;
  T neutral;
  U unite;
  vector<T> data;

  template<typename I>
  SegmentTree(int sz, T neutral, U unite, I init) : h(__lg(sz) + 1), n(1 << h), neutral(neutral), unite(unite), data(2 * n) {
    for (int i = 0; i < sz; ++i) data[i + n] = init(i);
    for (int i = n - 1; i > 0; --i) data[i] = unite(data[2 * i], data[2 * i + 1]);
  }

  SegmentTree(int sz, T neutral, U unite) : h(__lg(sz) + 1), n(1 << h), neutral(neutral), unite(unite), data(2 * n, neutral) {}

  void set(int i, T x) {
    data[i += n] = x;
    for (i /= 2; i > 0; i /= 2) data[i] = unite(data[2 * i], data[2 * i + 1]);
  }

  T get(int l, int r) {
    T leftRes = neutral, rightRes = neutral;
    for (l += n, r += n; l < r; l /= 2, r /= 2) {
      if (l & 1) leftRes = unite(leftRes, data[l++]);
      if (r & 1) rightRes = unite(data[--r], rightRes);
    }
    return unite(leftRes, rightRes);
  }
  int left(int i) {
    int lvl = __lg(i);
    return (i & ((1 << lvl) - 1)) * (1 << (h - lvl));
  }
  int right(int i) {
    int lvl = __lg(i);
    return ((i & ((1 << lvl) - 1)) + 1) * (1 << (h - lvl));
  }

  // l \in [0; n) && ok(get(l, l), l);
  // returns last r: ok(get(l, r), r)
  template<typename C>
  int lastTrue(int l, C ok) {
    T cur = neutral;
    l += n;
    do {
      l >>= __builtin_ctz(l);
      T with1 = unite(cur, data[l]);
      if (ok(with1, right(l))) {
        cur = with1;
        ++l;
      } else {
        while (l < n) {
          T with2 = unite(cur, data[2 * l]);
          if (ok(with2, right(2 * l))) {
            cur = with2;
            l = 2 * l + 1;
          } else {
            l = 2 * l;
          }
        }
        return l - n;
      }
    } while (l & (l - 1));
    return n;
  }

  // r \in [0; n) && ok(get(r, r), r);
  // returns first l: ok(get(l, r), l)
  template<typename C>
  int firstTrue(int r, C ok) {
    T cur = neutral;
    r += n;
    while (r & (r - 1)) {
      r >>= __builtin_ctz(r);
      T with1 = unite(data[--r], cur);
      if (ok(with1, left(r))) {
        cur = with1;
      } else {
        while (r < n) {
          T with2 = unite(data[2 * r + 1], cur);
          if (ok(with2, left(2 * r + 1))) {
            cur = with2;
            r = 2 * r;
          } else {
            r = 2 * r + 1;
          }
        }
        return r - n + 1;
      }
    }
    return 0;
  }
};

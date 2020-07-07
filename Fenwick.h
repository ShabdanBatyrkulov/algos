struct fen {
  int tree[N];
  fen() {
    memset(tree, 0, sizeof tree);
  }
  void upd(int pos, int val) {
    while (pos < N) {
      tree[pos] += val;
      pos = pos | pos + 1;
    }
  }
  int get(int r) {
    int res = 0;
    while (r >= 0) {
      res += tree[r];
      r = (r & r + 1) - 1;
    }
    return res;
  }
  int get(int l, int r) {
    return get(r) - get(l - 1);
  }
};

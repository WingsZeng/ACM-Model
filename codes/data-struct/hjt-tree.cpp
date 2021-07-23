int nn, b[MAXN];	// nn 为不重复个数, b[]是离散化用的数组
/* 先将数组离散化, 返回的是不重复的数字个数 */
int discretize(int _n, int data[]) {
	for (int i = 1; i <= _n; i++) b[i] = data[i];
	sort(b + 1, b + 1 + _n);
	return nn = unique(b + 1, b + 1 + _n) - b - 1;
}
/* 返回x离散化以后的id值 */
int id(int x) { return lower_bound(b + 1, b + 1 + nn, x) - b; }
struct Node {	// val 保存的是前缀和, 区间要差分一下
	int l, r, mid, lch, rch, val;
} t[MAXM];	// 点一般开 $4n + mlogn$ 稍大一点, 如 $4n + m(logn + 1)$
int n, root[MAXN], idx = 0;
/* 递归建一棵空树, 返回值为节点编号 */
int build(int l, int r) {
	int u = ++idx;
	t[u] = Node{l, r, (l+r)>>1, 0, 0, 0};
	if (l < r) {
		t[u].lch = build(l, t[u].mid);
		t[u].rch = build(t[u].mid + 1, r);
	}
	return u;
}
/* 从上一棵树的对应节点拉边过来建树, 返回值为节点编号 */
int update(int pre, int pos, int x) {
	int u = ++idx;
	t[u] = t[pre];  // 复制上一棵树对应节点的所有信息
	if (t[u].l == t[u].r) t[u].val += x;
	else {
		if (pos <= t[u].mid)
			t[u].lch = update(t[pre].lch, pos, x);
		else t[u].rch = update(t[pre].rch, pos, x);
		t[u].val = t[t[u].lch].val + t[t[u].rch].val;
	}
	return u;
}
/* 递归找[l, r]对应区间的值 */
int qry(int lu, int ru, int k) {
	if (t[lu].l == t[lu].r) return t[lu].l;
	int x = t[t[ru].lch].val - t[t[lu].lch].val; // 差分
	if (k <= x) return qry(t[lu].lch, t[ru].lch, k);
	else return qry(t[lu].rch, t[ru].rch, k - x);
}
/* 查询[l, r]中第k小, 注意返回值x是离散化以后的, 需要b[x]得到原数 */
int query(int l, int r, int k) { return qry(root[l-1], root[r], k); }
/* 离散化, 并根据权值建树 */
void init(int _n, int data[]) {
	nn = discretize(_n, data);
	root[0] = build(1, n);
	for (int i = 1; i <= _n; i++) // 根据权值建立主席树
		root[i] = update(root[i-1], id(data[i]), 1);
}

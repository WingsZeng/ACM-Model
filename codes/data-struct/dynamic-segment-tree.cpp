struct Node {
	int l, r, mid, len;  // 不再利用完全二叉树的下标性质
	int lch, rch;        // 而是直接分配下标, 从而动态开点
	LL val, tag;         // 初始值需要满足可以在开点时赋值, 如全0
} t[MAXM]; // 预先估计一下点的个数
int n, idx = 0, root = -1;
/* 动态开点, 左右儿子没开, 为0; 返回新建节点标号 */
int newNode(int l, int r) {
	t[++idx] = Node{l, r, (l+r)>>1, r-l+1};
	return idx;
}
/* 初始化线段树, 建立一个 [1, n] 区间的节点 */
void init(int _n) {
	root = newNode(1, _n);
}
/* 更新一条完整的线段 */
void updateNode(int u, LL d) {
	t[u].val += d * t[u].len;
	t[u].tag += d;   //打上标记, 不再往下
}
/* 将标记下放 */
void pushDown(int u) {
	if (!t[u].lch)	// 第一次访问, 开点
		t[u].lch = newNode(t[u].l, t[u].mid);
	updateNode(t[u].lch, t[u].tag);
	if (!t[u].rch)
		t[u].rch = newNode(t[u].mid+1, t[u].r);
	updateNode(t[u].rch, t[u].tag);
	t[u].tag = 0;
}
/* 由左右儿子线段合并更新当前线段 */
void pushUp(int u) {
	t[u].val = t[t[u].lch].val + t[t[u].rch].val;
}
/* 区间修改 */
void update(int l, int r, LL d, int u = -1) {
	if (u == -1) u = root;
	if (t[u].l == l && t[u].r == r)
		updateNode(u, d); // 找到对应线段更新
	else {
		pushDown(u);  // 访问u的儿子线段, 需要先下放标记更新
		if (l > t[u].mid)
			update(l, r, d, t[u].rch); //更新的线段全在该区间右边
		else if (r <= t[u].mid)
			update(l, r, d, t[u].lch); // 全在左边
		else { // 跨越了左右两边
			update(l, t[u].mid, d, t[u].lch);
			update(t[u].mid+1, r, d, t[u].rch);
		}
		pushUp(u);  // 由儿子线段的更新后的值计算当前线段值
	}
}
/* 区间查询 */
LL query(int l, int r, int u = -1) {
	if (u == -1) u = root;
	if (t[u].l == l && t[u].r == r) return t[u].val;
	pushDown(u);
	if (l > t[u].mid) return query(l, r, t[u].rch);
	if (r <= t[u].mid) return query(l, r, t[u].lch);
	else return query(l, t[u].mid, t[u].lch) +
				query(t[u].mid+1, r, t[u].rch);
}

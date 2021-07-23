struct Node {			// 线段节点
	int l, r, mid, len;
	LL val, tag;		// val为线段和的值, tag为标记值
} t[MAXN << 2]; // 线段节点要开4倍数据点的大小
int n;
void init(int _n, LL data[]) {
	build(data, 1, _n, 1);
}
/* 更新一条完整的线段 */
void updateNode(int u, LL d) {
	t[u].val += d * t[u].len;
	t[u].tag += d;   //打上标记, 不再往下
}
/* 将标记下放 */
void pushDown(int u) {
	updateNode(LCH(u), t[u].tag);
	updateNode(RCH(u), t[u].tag);
	t[u].tag = 0;    //取消标记
}
/* 由左右儿子线段合并更新当前线段 */
void pushUp(int u) {
	t[u].val = t[LCH(u)].val + t[RCH(u)].val;
}
/* 递归建树 */
void build(LL data[], int l, int r, int u) {
	t[u] = Node{l, r, (l+r)>>1, r-l+1};
	if (l == r) t[u].val = data[l]; //该线段只有一个点
	else {                             //分成左右两边递归求和
		build(data, l, t[u].mid, LCH(u));
		build(data, t[u].mid+1, t[u].r, RCH(u));
		pushUp(u);
	}
}
/* 区间修改 */
void update(int l, int r, LL d, int u = 1) {
	if (t[u].l == l && t[u].r == r)
		updateNode(u, d); // 找到对应线段更新
	else {
		pushDown(u);  // 访问u的儿子线段, 需要先下放标记更新
		if (l > t[u].mid)
			update(l, r, d, RCH(u)); //更新的线段全在该区间右边
		else if (r <= t[u].mid)
			update(l, r, d, LCH(u)); // 全在左边
		else { // 跨越了左右两边
			update(l, t[u].mid, d, LCH(u));
			update(t[u].mid+1, r, d, RCH(u));
		}
		pushUp(u);  // 由儿子线段的更新后的值计算当前线段值
	}
}
/* 区间查询 */
LL query(int l, int r, int u = 1) {
	if (t[u].l == l && t[u].r == r) return t[u].val;
	pushDown(u);
	if (l > t[u].mid) return query(l, r, RCH(u));
	if (r <= t[u].mid) return query(l, r, LCH(u));
	else return query(l, t[u].mid, LCH(u)) +
				query(t[u].mid+1, r, RCH(u));
}

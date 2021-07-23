struct Node {	//key为排序用的随机键, size为子树大小
	int val, key, size, lch, rch, tag;
} t[MAXN];
int idx = 0, root;
/* 初始化, 输入种子 */
void init(int seed) {
	idx = root = 0; // 如果多个树, 则删去idx = 0
	srand(seed);
}
/* 向上更新子树大小 */
void pushUp(int u) {
	t[u].size = t[t[u].lch].size + 1 + t[t[u].rch].size;
}
/* 标记下放; 这里写的是反转标记, 根据题目修改 */
void pushDown(int u) {
	if (t[u].tag) swap(t[u].lch, t[u].rch);
	t[t[u].lch].tag ^= t[u].tag;
	t[t[u].rch].tag ^= t[u].tag;
	t[u].tag = 0;
}
/* 合并两棵树l, r */
int merge(int l, int r) {
	if (!l || !r) return l | r; // 有一个为空, 返回另一个
	int u;
	if (t[l].key < t[r].key) {
		pushDown(u = l); t[l].rch = merge(t[l].rch, r);
	}
	else { pushDown(u = r); t[r].lch = merge(l, t[r].lch); }
	pushUp(u);
	return u;
}
/* 根据点的值的排名分割树u, 前k小的在l里, 其他在r里 */
void splitByRank(int k, int &l, int &r, int u = -1) {
	if (u == -1) u = root;
	if (!u) { l = r = 0; return; }
	pushDown(u);
	if (k <= t[t[u].lch].size) {
		r = u;
		splitByRank(k, l, t[u].lch, t[u].lch);
	}
	else {
		l = u;
		splitByRank(k-t[t[u].lch].size-1, t[u].rch, r, t[u].rch);
	}
	pushUp(u);
}
/* 根据点的值分割树u, 小于k的在l里, 其他的在r里 */
void splitByValue(int k, int &l, int &r, int u = -1) {
	if (u == -1) u = root;
	if (!u) { l = r = 0; return; }
	pushDown(u);
	if (t[u].val <= k) {
		l = u;
		splitByValue(k, t[u].rch, r, t[u].rch);
	}
	else {
		r = u;
		splitByValue(k, l, t[u].lch, t[u].lch);
	}
	pushUp(u);
}
/* 插入一个点 */
void insert(int x) {
	int u, l, r;
	t[u = ++idx] = Node{x, rand(), 1, 0, 0, 0};
	splitByValue(x, l, r);
	root = merge(merge(l, u), r);
}
/* 删除值为x的一个点 */
int erase(int x) {
	int l, r, ll, rr;
	splitByValue(x - 1, l, r);
	splitByRank(1, ll, rr, r);
	t[ll] = Node{0, 0, 0, 0, 0};
	root = merge(l, rr);
	return x;
}
/* 找树u中值为x的排名 */
int getRankByValue(int x, int &u) {
	int l, r, rk;
	splitByValue(x-1, l, r, u);
	rk = t[l].size + 1;
	u = merge(l, r);
	return rk;
}
/* 找树u中排名为k的值 */
int getValueByRank(int k, int &u) {
	int l, r, v, ll, rr;
	splitByRank(k-1, l, r, u);
	splitByRank(1, ll, rr, r);
	v = t[ll].val;
	u = merge(l, merge(ll, rr));
	return v;
}
/* 找到子树u中x的前驱 */
int getPre(int x, int &u) {
	int l, r, pre;
	splitByValue(x-1, l, r, u);
	pre = getValueByRank(t[l].size, l);
	u = merge(l, r);
	return pre;
}
/* 找到子树u中x的后继 */
int getSuc(int x, int &u) {
	int l, r, suc;
	splitByValue(x, l, r, u);
	suc = getValueByRank(1, r);
	u = merge(l, r);
	return suc;
}
/* 遍历u */
void iterate(int u) {
	if (u) {
		pushDown(u);
		iterate(t[u].lch);
		printf("%d ", t[u].val);
		iterate(t[u].rch);
	}
}

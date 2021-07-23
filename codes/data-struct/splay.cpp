struct Node {
	int val, ch[2], fa, size, cnt;
} t[MAXN];
int idx = 0, root = 0;
/* 判断是否为右儿子 */
int connect(int u) { return t[t[u].fa].ch[1] == u; }
/* 向上更新节点 */
void pushUp(int u) {
	t[u].size = t[u].cnt + t[t[u].ch[0]].size + t[t[u].ch[1]].size;
}
/* 旋转, 把 zig 和 zag 写在了一起 */
void rotate(int u) {
	int f = t[u].fa, gf = t[f].fa, k = connect(u), s = t[u].ch[k^1];
	t[gf].ch[connect(f)] = u, t[u].fa = gf;
	t[f].ch[k] = s, t[s].fa = f;
	t[u].ch[k^1] = f, t[f].fa = u;
	pushUp(f), pushUp(u);
}
/* 将 u splay 为 goal 的儿子, goal=0 时 splay 到根 */
void splay(int u, int goal = 0) {
	while (t[u].fa != goal) {
		int f = t[u].fa, gf = t[f].fa;
		if (gf != goal) {
			if (connect(u) == connect(f)) rotate(f);
			else rotate(u);
		}
		rotate(u);
	}
	if (!goal) root = u;
}
/* 将值为x的点splay到根, x不存在时会找到前驱或者后继 */
int find(int x) {
	int cur = root;
	while (t[cur].val != x && t[cur].ch[x > t[cur].val])
		cur = t[cur].ch[x > t[cur].val];
	splay(cur);
	return root;
}
/* 插入节点, 存在则cnt++, 不存在则新建, 并根据之前找到的f连边 */
void insert(int x) {
	int cur = root, f = 0;
	while (x != t[cur].val && cur)
		f = cur, cur = t[cur].ch[x > t[cur].val];
	if (cur) t[cur].cnt++;
	else {
		cur = ++idx;
		if (f) t[f].ch[x > t[f].val] = cur;
		t[cur].ch[0] = t[cur].ch[1] = 0, t[cur].fa = f;
		t[cur].cnt = t[cur].size = 1, t[cur].val = x;
	}
	splay(cur);
}
/* 查找排名为k的值 */
int getValueByRank(int k) {
	int cur = root;
	while(1) {
		if (t[cur].ch[0] && k <= t[t[cur].ch[0]].size)
			cur = t[cur].ch[0];
		else if (k > t[cur].cnt + t[t[cur].ch[0]].size) {
			//注意更改k
			k -= t[cur].cnt + t[t[cur].ch[0]].size;
			cur = t[cur].ch[1];
		}
		else return t[cur].val;
	}
}
/* 查找x的排名 */
int getRankByValue(int x) { return t[t[find(x)].ch[0]].size + 1; }
/* 查找x的前驱 */
int getPre(int x) {
	find(x);
	if (x > t[root].val) return root;
	int cur = t[root].ch[0];
	while (t[cur].ch[1]) cur = t[cur].ch[1];
	return cur;
}
/* 查找x的后继 */
int getSuc(int x) {
	find(x);
	if (x < t[root].val) return root;
	int cur = t[root].ch[1];
	while (t[cur].ch[0]) cur = t[cur].ch[0];
	return cur;
}
/* 删除x */
void erase(int x) {
	//把前驱splay到根, 后继splay到根的右儿子, 那么右儿子的左儿子就是值为x的点
	//由于pre和suc返回的是严格比x大/小的数
	//所以如果不加入±∞会找到0点,splay(0)出错
	int pre = getPre(x), suc = getSuc(x);
	splay(pre), splay(suc, pre);
	int u = t[suc].ch[0];
	if (t[u].cnt > 1) t[u].cnt--, splay(u);
	else t[suc].ch[0] = t[u].fa = 0;
}
/* 建spaly, 加入 $\pm \infty$ 的哨兵节点 */
void init() {
	root = idx = 0;
	insert(-INTINF), insert(INTINF);
	t[1].size = t[2].size = t[1].cnt = t[2].cnt = 0;
}

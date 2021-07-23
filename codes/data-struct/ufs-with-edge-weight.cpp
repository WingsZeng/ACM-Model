int n, fa[MAXN], d[MAXN]; // d[x]表示x到fa[x]的距离
/* 初始化并查集 */
void init(int n) {
	for (int i = 1; i <= n; i++) fa[i] = i, d[i] = 0;
}
int find(int x) {
	if (x == fa[x])
		return x;
	int fx = fa[x]; //先记录一下x当前的 fa
	fa[x] = find(fa[x]);
	d[x] += d[fx]; //x到现在的 fa (即代表元)的路径为两段之和
	return fa[x];
}
/* 把x所在的集合连接到y所在的集合上, 且x到y的距离为dis */
/* 返回合并前是否在不同集合中 */
bool uni(int x, int y, int dis) {
	int fx = find(x), fy = find(y);
	if (fx == fy)
		return false;
	d[fx] = dis + d[y] - d[x];
	fa[fx] = fy;
	return true;
}
/* 查询是否x, y是否在同一集合中 */
bool query(int x, int y) {
	return find(x) == find(y);
}

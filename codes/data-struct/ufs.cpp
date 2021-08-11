// 可以维护其他数据, 如集合大小, 集合最值. 注意仅代表元的值有效
int n, fa[MAXN];
/* 初始化并查集 */
void init(int n) {
	for (int i = 1; i <= n; i++) fa[i] = i;
}
/* 查询并返回x所在集合的代表元; 路径压缩 */
int find(int x) {
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}
/* 合并x, y所在集合(x$\to$y); 返回合并前是否在不同集合中; 无按秩合并 */
bool uni(int x, int y) {
	if (find(x) == find(y))
		return false;
	fa[find(x)] = find(y);
	return true;
}
/* 查询是否x, y是否在同一集合中 */
bool query(int x, int y) {
	return find(x) == find(y);
}

// n 个点 m 条边的简单图, 修改点权, 询问邻居点权和
int n, m, deg[MAXN], S, a[MAXN], sum[MAXN];
VI G[MAXN], E[MAXN];	// G 是原图, E 是指向重点的有向边
/* 根据度数确定轻重点, 向重点连的边存在 E 里 */
void build() {
	S = sqrt(2 * m);	// 度数大于 $/sqrt m$ 的为重点
	for (int i = 1; i <= n; i++)
		for (int v : G[i]) if (deg[v] > S)
			E[i].push_back(v);
}
/* 询问点 u 的邻居的点权和 */
int query(int u) {
	if (deg[u] > S) return sum[u]; // 如果是重点, 返回维护的邻居和
	int res = 0;
	for (int v : G[u]) res += a[v]; // 如果是轻点, 直接暴力
	return res;
}
/* 修改点 u 的权值 */
void update(int u, int d) {
	a[u] += d;
	for (int v : E[u]) sum[v] += d; // 维护重点的邻居和
}

int sz[MAXN], vis[MAXN]; // sz[u] 为每次dfs计算以u为根的子树的大小
// descendant 保存第一次调用dfs的点u到包含u的树中的所有的点v及他们之间的距离
vector<PII> descendant;
/* 遍历, 同时计算sz和descentant
/* 如果第一次调用dis参数为0, dis表示根(第一次调用dfs的点)到当前点u的距离
/* 不为0的话会在所有距离上加上这个第一次调用传入的的参数 $dist_0$) */
void dfs(int u, int f, int dis) {
	sz[u] = 1;
	descendant.emplace_back(u, dis);
	for (int i = head[u]; i; i = edges[i].next) {
		Edge &e = edges[i];
		if (e.to != f && !vis[e.to]) {
			dfs(e.to, u, dis + e.w);
			sz[u] += sz[e.to];
		}
	}
}
/* 求包含u的树的重心 */
int center(int u) {
	// 每一次调用dfs前都要清空descendant
	descendant.clear(); dfs(u, 0, 0);
	int tot_sz = descendant.size();
	for (auto des : descendant) {
		int is_center = 1;
		int x = des.first;
		for (int i = head[x]; i; i = edges[i].next) {
			Edge &e = edges[i];
			if (vis[e.to]) continue; // e.to 已删除, 不考虑
			// sz[x] > sz[v] $\Rightarrow$ v是x的儿子, sz[v] > $\frac{n}{2}$, v不是重心
			if (sz[x] > sz[e.to] && (sz[e.to] << 1) > tot_sz) {
				is_center = 0; break;
			}
			// sz[x] < sz[v] $\Rightarrow$ v是x的父亲, tot\_sz - sz[x] 是v向上的大小
			if (sz[x] < sz[e.to] && ((tot_sz - sz[x]) << 1) > tot_sz) {
				is_center = 0; break;
			}
		}
		if (is_center) {
			// 找到重心, 需要以重心为根, 求一下树中所有点到重心的距离
			// 这样调用完center后就可以保存所有点到重心的距离了
			descendant.clear(); dfs(x, 0, 0); return x;
		}
	}
	return -1;
}

void divide(int u) {
	int c = center(u); vis[c] = 1;	// 标记重心, 删去
	work(); // 已经在center函数中处理了 "经过重心的'半路径'"
			// 在work函数中考虑如何把两条半路径组合成一条路径
			// 并考虑如何处理数据, 回答问题
	for (int i = head[c]; i; i = edges[i].next) {
		Edge &e = edges[i];
		if (vis[e.to]) continue; // e.to 已经删除, 不考虑
		iework();	// 考虑把"假的路径"容斥掉. 如果是路径, 那么求一次
					// dfs(e.to, c, e.w)得到的descentant就是所有
					// "假的路径", 这时候虽然第一次调用dfs的是e.to,
					// 但由于加上的e.w, 也可以认为是点到c的距离
		divide(e.to);	// 找到剩余的点(所在的子树), 继续处理
	}
}

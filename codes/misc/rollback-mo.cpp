// 求区间重要度, 重要度: 某数出现的次数乘以他本身, 这个值的最大值
int n, q, block_size, id[MAXN], ID = 0, a[MAXN], cnt[MAXN], tmpcnt[MAXN];
LL num[MAXN], ans[MAXN];
unordered_map<int, int> mp;		// 原题数据需要离散化
/* 获得块左端点 */
int getBlockR(int block_id) { return min(block_id * block_size, n); }
/* 获得块右端点*/
int getBlockL(int block_id) { return getBlockR(block_id-1) + 1; }
struct Query {
	int idx, l, r;
	bool operator < (const Query &Q) const {
		// 排序规则: l在同一块, 按r递增排序; 不在同一块按块编号递增排序
		return id[l] == id[Q.l] ? r < Q.r : id[l] < id[Q.l];
	}
} query[MAXN];
/* 初始化, 计算块大小和块编号, 并离线询问排序 */
void init() {
	block_size = sqrt(n);
	for (int i = 1; i <= n; i++)
		id[i] = (i-1) / block_size + 1;
	sort(query+1, query+1+q);
}
void solve() {
	init();
	int l = 1, r = l-1; LL mx = -1;
	for (int i = 1; i <= q; i++) {
		// l和上一个不在同一块中, 回滚永久信息
		if (id[query[i].l] != id[query[i-1].l]) {
			mx = -1;
			while (r >= l) --cnt[a[r--]];
			l = getBlockL(id[query[i].l]+1);
			r = l-1;
		}
		// 维护永久信息
		while (r < query[i].r) {
			cnt[a[++r]]++;
			mx = max(mx, cnt[a[r]] * num[a[r]]);
		}
		// 暴力维护临时信息
		LL tmpmx = -1;
		for (int j = query[i].l; j <= min(query[i].r, getBlockR(id[query[i].l])); j++)
			// 注意统计临时信息要合并永久信息的部分
			tmpmx = max(tmpmx, (++tmpcnt[a[j]] + cnt[a[j]]) * num[a[j]]);
		// 回滚临时信息
		for (int j = query[i].l; j <= min(query[i].r, getBlockR(id[query[i].l])); j++)
			tmpcnt[a[j]]--;
		ans[query[i].idx] = max(tmpmx, mx);	// 更新答案
	}
}

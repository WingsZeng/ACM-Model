int n, q, id[MAXN], block_size, a[MAXN];
struct Query {
	int idx, l, r;
	bool operator < (const Query &Q) const {
		// 排序规则: l在同一块, 按r递增排序; 不在同一块按块编号递增排序
		return id[l] == id[Q.l] ? r < Q.r : l < Q.l;
	}
} query[MAXN];
/* 增加值, 更新维护信息 */
void add(int c) {}
/* 删除值, 更新维护信息 */
void del(int c) {}
/* 通过当前维护的信息计算当前询问的答案 */
void getAns(int idx) {}
/* 初始化, 计算块大小和块编号, 并离线询问排序 */
void init() {
	block_size = sqrt(n);
	for (int i = 1; i <= n; i++)
		id[i] = (i-1) / block_size + 1;
	sort(query + 1, query + q + 1);
}
void solve() {
	init();
	int l = query[1].l, r = l-1;
	for (int i = 1; i <= q; i++) {
		while (l > query[i].l) add(a[--l]);
		while (r < query[i].r) add(a[++r]);
		while (l < query[i].l) del(a[l++]);
		while (r > query[i].r) del(a[r--]);
		getAns(query[i].idx);
	}
}

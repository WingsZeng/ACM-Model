// q是询问个数, T是修改总时间(个数), qc是询问和修改的总数(读入)
int T = 0, n, q = 0, qc, block_size, id[MAXN], a[MAXN];
struct Query {
	int idx, t, l, r;
	bool operator < (const Query &Q) const {
		// 排序规则: l在同一块, r在同一块, 按t递增排序;
		// r不在同一块按r所在块编号递增排序;
		// l不在同一块按l所在块编号递增排序
		return id[l] == id[Q.l] ? id[r] == id[Q.r] ? t < Q.t :
				id[r] < id[Q.r] : id[l] < id[Q.l];
	}
} query[MAXQ];
struct Modify { int pos, a; } modify[MAXQ];
/* 增加值, 更新维护信息 */
void add(int c) {}
/* 删除值, 更新维护信息 */
void del(int c) {}
/* 通过当前维护的信息计算当前询问的答案 */
void getAns(int idx) {}
/* 应用时间为t的修改, 如果修改的点在当前维护的区间, 则需要统计维护 */
void change(int l, int r, int t) {
	int &pos = modify[t].pos, &c = modify[t].a;
	if (l <= pos && pos <= r)
		del(a[pos]), add(c);
	swap(c, a[pos]);
}
/* 初始化, 计算块大小和块编号, 并离线询问排序 */
void init() {
	block_size = pow(n, 2./3.);
	for (int i = 1; i <= n; i++)
		id[i] = (i-1) / block_size + 1;
	sort(query+1, query+q+1);
}
void solve() {
	init();
	int l = query[1].l, r = l-1, t = 0;
	for (int i = 1; i <= q; i++) {
		while (l > query[i].l) add(a[--l]);
		while (r < query[i].r) add(a[++r]);
		while (l < query[i].l) del(a[l++]);
		while (r > query[i].r) del(a[r--]);
		while (t < query[i].t) change(l, r, ++t);
		while (t > query[i].t) change(l, r, t--);
		getAns(query[i].idx);
	}
}

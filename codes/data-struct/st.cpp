int n, lg[MAXN], pw[MAXN], st[MAXN][30];  // st[i][j] 表示 $[i, i + 2^j)$ 的最值
/* 预处理出$log_2x$ 和 $2^k$ */
void init() {
	lg[0] = -1, pw[0] = 1;
	for (int i = 1; i <= n; i++) lg[i] = lg[i>>1] + 1;
	for (int i = 1; i <= lg[n]; i++) pw[i] = pw[i-1] << 1;
}
/* 建立ST表 */
void build(int data[]) {
	//st[i][0] 存数据 st[i][0] = [i, i + 2^0) = data[i]
	for (int i = 1; i <= n; i++) st[i][0] = data[i];
	for (int j = 1; j <= lg[n]; j++)                // 注意先枚举j
		for (int i = 1; i + pw[j] <= n + 1; i++) // 左闭右开, 到n+1
			//把 $[i, i + 2^j)$ 分成$[i, i + 2^{j-1})$ 和 $[i + 2^{j-1}, i + 2^j)$ 两段
			st[i][j] = min(st[i][j-1], st[i+pw[j-1]][j-1]);
}
/* 查询 [l, r] 中的的最值 */
int query(int l, int r) {
	int k = lg[r - l + 1];
	// 由于 $2^{\lfloor \log{2}{x} \rfloor} > \frac{x}{2}$, 故前后两个长度为 $2^{\lfloor \log{2}{x} \rfloor}$ 区间就可以取完所有的元素
	return min(st[l][k], st[r+1-pw[k]][k]); //设 $r' = r + 1$, 查询 $[l, r')$
}

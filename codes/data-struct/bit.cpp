int n, t[MAXN];
/* 单点修改(加) */
void update(int pos, int x) {
	for (int i = pos; i <= n; i += lowbit(i))
		t[i] += x;
}
/* 查询前缀和 */
int presum(int pos) {
	int res = 0;
	for (int i = pos; i; i -= lowbit(i))
		res += t[i];
	return res;
}
/* 查询区间[l, r]的和 */
int query(int l, int r) {
	return presum(r) - presum(l-1);
}

/* 求 n 个点值确定的 n 次数界多项式拉格朗日插值在 m 处的函数值 */
/* 点 (x, y) 从下标 0 开始 */
int Lagrange(int *x, int *y, int n, int m) {
	int L = 0;
	for (int i = 0; i < n; i++) {
		int p = 1, q = 1;
		for (int j = 0; j < n; j++) if (j != i)
			p = mult(p, m - x[j]), q = mult(q, x[i] - x[j]);
		L = pls(L, mult(y[i], mult(p, power(q))));
	}
	return L;
}

// finv[x] 表示 $(x!)^{-1}$, inv_neg_1 表示 $(-1)^{-1}$
// l[i] 是第 i 项拉格朗日基本多项式
int pre[MAXA], suf[MAXA], finv[MAXN], inv_neg_1, l[MAXN];
/* 预处理阶乘逆元, 注意要处理到最高次数界 */
void init(int n) {
	int facn = 1;
	for (int i = 2; i <= n; i++) facn = mult(facn, i);
	finv[n] = power(facn);
	for (int i = n-1; ~i; i--) finv[i] = mult(i+1, finv[i+1]);
	inv_neg_1 = power(-1);
}
/* 求 n 个点值确定的 n 次数界多项式拉格朗日插值在 x 处的函数值 */
/* 其中点的横坐标为 $s, s+1, s+2 \dots, s+n-1$, (i, y) 从下标 s 开始 */
int Lagrange(int s, int *y, int n, int x) {
	pre[0] = x - s;
	for (int i = 1; i < n; i++) pre[i] = mult(pre[i-1], x - i - s);
	suf[n] = 1;
	for (int i = n-1; ~i; i--) suf[i] = mult(suf[i+1], x - i - s);
	l[0] = mult(suf[1], finv[n-1]);
	if ((n-1)&1) l[0] = mult(l[0], inv_neg_1);
	for (int i = 1; i < n; i++) {
		l[i] = mult(mult(pre[i-1], suf[i+1]), mult(finv[i], finv[n-1-i]));
		if ((n-1-i)&1) l[i] = mult(l[i], inv_neg_1);
	}
	int L = 0;
	for (int i = 0; i < n; i++) L = pls(L, mult(y[i], l[i]));
	return L;
}

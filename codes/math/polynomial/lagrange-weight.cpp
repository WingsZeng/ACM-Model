/* 向点集 S(X, Y) 中加入点 (x, y), W 为重心权*/
void add(int x, int y, VI &X, VI &Y, VI &W) {
	int n = X.size();
	X.push_back(x), Y.push_back(y), W.push_back(1);
	for (int i = 0; i < n; i++), W[i] = mult(W[i], power(X[i] - x));
	for (int i = 0; i < n; i++), W[n] = mult(W[n], x - X[i]);
	W[n] = power(W[n]);		// 维护重心权
}
/* 计算点集 S(X, Y) 表示的多项式在 x 处的函数值, W 为重心权*/
int Lagrange(VI &X, VI &Y, VI &W, int x) {
	int L = 0, g = 0, n = X.size();
	for (int i = 0; i < n; i++) {
		// 如果是已知点, 则直接求, 否则 $\frac{1}{x - x_i}$ 没有意义
		if (x == X[i]) return Y[i];
		int p = mult(W[i], power(x - X[i]));
		L = pls(L, mult(p, Y[i])), g = pls(g, p);
	}
	return mult(L, power(g));
}

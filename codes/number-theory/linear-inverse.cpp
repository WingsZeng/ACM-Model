void init_liner_inverse() {
	inv[0] = inv[1] = 1;
	for (int i = 2; i <= n; i++) inv[i] = mult(P - P / i, inv[P % i]);
}
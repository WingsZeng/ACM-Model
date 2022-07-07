void init_liner_inverse(int _n) {
	inv[0] = inv[1] = 1;
	for (int i = 2; i <= _n; i++) inv[i] = mult(P - P / i, inv[P % i]);
}
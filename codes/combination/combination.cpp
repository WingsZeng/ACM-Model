void init(int _n) {
	fac[0] = inv[0] = 1;
	for (int i = 1; i <= _n; i++) fac[i] = mult(fac[i - 1], i);
	inv[_n] = power(fac[_n], P-2);
	for (int i = _n - 1; i; i--) inv[i] = mult(inv[i + 1], i + 1);
}
int C(int _n, int _m) {
	return mult(mult(fac[_n], inv[_m]), inv[_n - _m]);
}
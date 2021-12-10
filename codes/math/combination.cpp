int frac[MAXN], inv[MAXN];
void init() {
	frac[0] = inv[0] = 1;
	for (int i = 1; i <= n; i++) frac[i] = mult(frac[i - 1], i);
	inv[n] = power(frac[n]);
	for (int i = n-1; i; i--) inv[i] = mult(inv[i + 1], i + 1);
}
int C(int n, int m) {
	return mult(mult(frac[n], inv[m]), inv[n - m]);
}

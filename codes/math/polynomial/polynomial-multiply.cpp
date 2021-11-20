cpx a[MAXN << 2], b[MAXN << 2], ab[MAXN << 2];
/* 输入多项式系数和其界次数, 返回乘积系数和其界次数 */
int polymult(double *A, int n_A, double *B, int n_B, double *AB) {
	for (int i = 0; i < n_A; i++) a[i] = cpx(A[i], 0);
	for (int i = 0; i < n_B; i++) b[i] = cpx(B[i], 0);
	int n = n_A + n_B - 1, expand = 1;  // AB 的界次数, 即需要计算的点值个数
	while (expand < n) expand <<= 1;    // FFT 需要界次数为 $2^k$
	FFT(a, expand), FFT(b, expand);     // 转换为点值并计算
	for (int i = 0; i < expand; i++) ab[i] = a[i] * b[i];
	IFFT(ab, expand);                   // 再转换为系数
	for (int i = 0; i < n; i++) AB[i] = a[i].real();
	return n;
}

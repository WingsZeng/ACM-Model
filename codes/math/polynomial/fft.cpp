const double PI = 2 * acos(0);
typedef complex<double> cpx;
/* $a_i$ 的实部为系数, 虚部为 0, n (= $2^k$) 为界次数, 返回值为复数 $a_i = A(\omega_n^i)$ */
void FFT(cpx *a, int n, int flag_inv = 1) {
	for (int i = 1, j = 0; i < n - 1;i++) {
		for (int k = n; j ^= k >>= 1, (~j) & k;);
		if (i < j) swap(a[i], a[j]);
	}
	for (int len = 2; len <= n; len <<= 1) {
		cpx wn(cos(2 * PI / len), flag_inv * sin(2 * PI / len));
		for (int start = 0; start < n; start += len) {
			cpx w(1, 0);
			for (int i = start; i < start + len / 2; i++, w *= wn) {
				cpx l = a[i], r = w * a[i + len / 2];
				a[i] = l + r, a[i + len / 2] = l - r;
			}
		}
	}
	if (flag_inv == -1) for (int i = 0; i < n; i++) a[i] /= n;
}
/* $a_i$ 为复数 $A(\omega_n^i)$, n (= $2^k$) 为点个数, 返回值 $a_i$ 的实部为系数, 虚部为 0*/
void IFFT(cpx *a, int n) { DFT(a, n, -1); }

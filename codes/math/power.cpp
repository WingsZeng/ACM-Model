/* power(x) 为 x 在模 P 意义下的的逆元, P 必须为质数 */
int power(int a, int b = P-2) {
	int res = 1;
	while (b) {
		if (b&1) res = mult(res, a);
		a = mult(a, a);
		b >>= 1;
	}
	return res;
}

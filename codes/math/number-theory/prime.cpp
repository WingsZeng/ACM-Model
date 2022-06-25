int isnotprime[MAXN], prime[MAXN], p_cnt;
void init_prime(int _n) {
	isnotprime[0] = isnotprime[1] = 1; p_cnt = 0;
	for (int i = 2; i <= _n; i++) {
		if (!isnotprime[i]) prime[p_cnt++] = i;
		for (int j = 0; j < p_cnt && i * prime[j] <= _n; j++) {
			isnotprime[i * prime[j]] = 1;
			if (!(i % prime[j])) break;
		}
	}
}
void init_prime(int _n) {
	isnotprime[0] = isnotprime[1] = 1; cnt = 0;
	for (int i = 2; i <= _n; i++) {
		if (!isnotprime[i]) prime[cnt++] = i;
		for (int j = 0; j < cnt && i * prime[j] <= _n; j++) {
			isnotprime[i * prime[j]] = 1;
			if (!(i % prime[j])) break;
		}
	}
}
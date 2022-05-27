void init_phi(int _n) {
	phi[1] = isnotprime[0] = isnotprime[1] = 1, cnt = 0;
	for (int i = 2; i <= _n; i++) {
		if (!isnotprime[i]) { prime[cnt++] = i, phi[i] = i-1; }
		for (int j = 0; j < cnt && i * prime[j] <= _n; j++) {
			isnotprime[i * prime[j]] = 1;
			if (i % prime[j]) phi[i * prime[j]] = phi[i] * (prime[j] - 1);
			else { phi[i*prime[j]] = phi[i] * prime[j]; break; }
		}
	}
}
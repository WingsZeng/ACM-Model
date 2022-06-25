vector<PII> prime_dec(int x) {
	vector<PII> v;
	for (int i = 0; i < p_cnt && x > 1; i++) {
		int p = prime[i], e = 0;
		while (x % p == 0) { e++, x /= p; }
		if (e) v.emplace_back(p, e);
	}
	return v;
}
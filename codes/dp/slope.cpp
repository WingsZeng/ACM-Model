LL x(int i) {}
LL y(int i) {}
LL k(int i) {}
LD slope(int i, int j) {
	return 1. * (y(i) - y(j)) / (x(i) - x(j));
}
void solve() {
	deque<int> q; q.push_back(0);
	for (int i = 1; i <= n; i++) {
		while (q.size() > 1) {
			int j = q.front(); q.pop_front();
			int jj = q.front(); q.push_front(j);
			// 斜率递增
			if (k(i) > slope(j, jj)) q.pop_front();
			else break;
		}
		int j = q.front();
		dp[i] = dp[j] + W;	// dp 方程
		while (q.size() > 1) {
			int j = q.back(); q.pop_back();
			int jj = q.back(); q.push_back(j);
			// 维护下凸包
			if (slope(i, jj) > slope(i, j)) q.pop_back();
			else break;
		}
		q.push_back(i);
	}
}

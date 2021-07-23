for (int i = 1; i <= n; i++) for (int j = v; j >= c[i]; j--)
	if (dp[j] < dp[j-c[i]] + w[i]) {
		dp[j] = dp[j-c[i]] + w[i];
		paht[i][j] = true;
	}
int i = n, j = v;
while (i && j) {
	if (path[i][j]) {
		items.push(i);	// 方案
		j -= c[i];
	}
	i--;
}

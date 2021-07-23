for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
	int ans = 0;
	if (a[i] == b[j]) ans = dp[i-1][j-1] + 1;
	else ans = max(dp[i-1][j], dp[i][j-1]);
	dp[i][j] = ans;
}

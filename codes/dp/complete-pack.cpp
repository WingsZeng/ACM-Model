for (int i = 1; i <= n; i++) for (int j = c[i]; j <= v; j++)
	dp[j] = max(dp[j], dp[j-c[i]] + w[i]);

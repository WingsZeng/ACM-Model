// TODO 二进制
for (int i = 0; i < n; i++)
	for (int k = 0; k < t[i]; k++)
		for (int j = v; j >= c[i]; j--)
			dp[j] = max(dp[j], dp[j-c[i]] + w[i]);

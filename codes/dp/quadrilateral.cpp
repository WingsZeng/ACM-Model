// TODO
for(int i = n; i; i--) {
	for(int j = i + 1; j <= n; j++) {
		int mn=INTINF, p = -1;
		for(int k = s[i][j-1]; k <= s[i+1][j]; k++)
			if(dp[i][k] + dp[k+1][j] + w[i][j] < mn)
				mn = dp[i][k] + dp[k+1][j] + w[i][j], p = k;
		dp[i][j] = mn, s[i][j] = p;
	}
}

void dfs(int u) {
	sz[u] = 1;
	dp[u][1] = a[u];
	for (int v : G[u]) {
		dfs(v);
		for (int k = sz[u]; k; k--)
			for (int x = 1; x <= sz[v]; x++)
				dp[u][x+k] = max(dp[u][x+k], dp[u][k] + dp[v][x]);
		sz[u] += sz[v];
	}
}

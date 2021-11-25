void dfs(int u, int f) {
	sz[u] = 1;
	dp[u][1] = a[u], dp[u][0] = 0;	// 初值
	for (int v : G[u]) if (v != f){
		dfs(v, u);
		for (int i = 0; i <= sz[u] + sz[v]; i++) tmp[i] = 0;
		for (int i = sz[u]; i >= 0; i--)    // 是否必选一个决定枚举到1还是0
			for (int j = 0; j <= sz[v]; j++)// 同上
				tmp[i+j] = max(tmp[i+j] dp[u][i] + dp[v][j]);
		sz[u] += sz[v];		// 合并
		for (int i = 0; i <= sz[u]; i++) dp[u][i] = tmp[i];
	}
}

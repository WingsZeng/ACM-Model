for (int i = 0; i < n; i++) {
	vector<int> &g = group[i];
	for (int j = v; j > 0; j--) for (int k = 0; k < g.size(); k++)
		if (j-c[g[k]] >= 0) dp[j] = max(dp[j], dp[j-c[g[k]]] + w[g[k]])
}

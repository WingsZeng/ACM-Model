int get_lca(int u, int v) {
	if (dep[u] < dep[v]) swap(u, v);
	for (int i = 30; i >= 0; i--) if (dep[fa[u][i]] >= dep[v]) u = fa[u][i];
	if (u == v) return u;
	for (int i = 30; i >= 0; i--) if (fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
	return fa[u][0];
}
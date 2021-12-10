struct Node {
	int u, d;
	bool operator < (const Node &n) const { return d > n.d; }
};
priority_queue<Node> Q;
void dij() {
	memset(vis, 0, sizeof(vis));
	for (int i = 1; i <= n; i++) Q.push({i, d[i]});
	while (!Q.empty()) {
		Node x = Q.top(); Q.pop();
		int u = x.u;
		if (!vis[u]) {
			vis[u] = 1;
			for (int i = head[u]; ~i; i = edges[i].next) {
				Edge &e = edges[i];
				if (d[e.to] > d[u] + e.w) {
					d[e.to] = d[u] + e.w;
					Q.push(Node{e.to, d[e.to]});
				}
			}
		}
	}
}

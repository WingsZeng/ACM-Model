struct Node {
	int u, d;
	bool operator < (const Node &n) const { return d > n.d; }
};
priority_queue<Node> Q;
int d[MAXV];
void dij(int s) {
	memset(vis, 0, sizeof(vis));
	memset(d, INTINF, sizeof(d));
	Q.push({s, d[s] = 0});
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

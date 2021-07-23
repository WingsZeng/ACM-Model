int d[MAXV], a[MAXV], inq[MAXV], p[MAXV];
bool spfa(int s, int t, int &flow, int &cost) {
	memset(d, INTINF, sizeof(d)); memset(a, 0, sizeof(a));
	queue<int> Q;
	Q.push(s), inq[s] = 1;
	d[s] = 0, a[s] = INTINF, p[s] = -1;
	while (!Q.empty()) {
		int u = Q.front();
		Q.pop(), inq[u] = 0;
		for (int i = head[u]; ~i; i = edges[i].next) {
			Edge &e = edges[i];
			if (d[e.to] > d[u] + e.cost && e.cap > e.flow) {
				d[e.to] = d[u] + e.cost;
				a[e.to] = min(a[u], e.cap - e.flow);
				p[e.to] = i;
				if (!inq[e.to]) Q.push(e.to), inq[e.to] = 1;
			}
		}
	}
	if (d[t] >= INTINF) return false;
	flow += a[t];
	cost += d[t] * a[t];
	for (int i = p[t]; ~i; i = p[edges[i^1].to])
		edges[i].flow += a[t], edges[i^1].flow -= a[t];
	return true;
}
void mcmf(int s, int t, int &flow, int &cost) {
	while (spfa(s, t, flow, cost));
}

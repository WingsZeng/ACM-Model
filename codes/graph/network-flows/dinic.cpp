int d[MAXV], cur[MAXV];
//bfs找可前进边, 即d[v] = d[u] + 1 且可以流的 (u, v)
bool bfs(int s, int t) {
	memset(d, INTINF, sizeof(d));
	queue<int> Q;
	Q.push(s); d[s] = 0;
	while (!Q.empty()) {
		int u = Q.front(); Q.pop();
		for (int i = head[u]; ~i; i = edges[i].next) {
			Edge &e = edges[i];
			//找还可以流的边
			if (d[e.to] >= INTINF && e.cap > e.flow) {
				d[e.to] = d[u] + 1; Q.push(e.to);
			}
		}
	}
	return d[t] < INTINF;
}
//当前点u, flow已经流过的流量, a还可以继续流的流量
//dfs找多条增广路
int dfs(int u, int a, int t) {
	//流到终点或者流不下去了
	//流到终点返回可流量, 在下面的a -= f时a=0, 然后结束这个点的搜索
	if (u == t || a == 0)
		return a;
	int f = 0, flow = 0;
	//当前弧优化 &i = cur 搜完了这条路, 就不会再搜这条路了, 所以从后面开始搜
	for (int &i = cur[u]; ~i; i = edges[i].next) {
		Edge &e = edges[i];
		if (d[e.to] == d[u] + 1) {
			f = dfs(e.to, min(a, e.cap - e.flow));
			if (f > 0) {
				e.flow += f; flow += f;
				edges[i^1].flow -= f; a -= f;
				if (!a) break; //没有可以供其他路流的流量(或者流完了)
			}
		}
	}
	if (a) //GAP优化 如果后面的都流完了, 这个点还有流量剩余, 那么不用再搜这个点了
		d[u] = -1;
	return flow;
}
int dinic(int s, int t) {
	int flow = 0;
	while (bfs(s, t)) {
		for (int i = 1; i <= v; i++) cur[i] = head[i];
		flow += dfs(s, INTINF);
	}
	return flow;
}

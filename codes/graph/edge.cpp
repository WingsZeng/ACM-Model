struct Edge { int to, next, w;} edges[MAXN<<1];
int mm = 0, head[MAXN];
void addEdge(int u, int v, int w) {
	edges[mm] = {v, head[u], w};
	head[u] = mm++;
}

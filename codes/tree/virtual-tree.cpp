// TODO
int n, m, k, que[MAXN];
int f[MAXN][19], dfn[MAXN], idx = 0, dep[MAXN];
LL g[MAXN];
void dfs(int u, int fa) {
    f[u][0] = fa;
    dep[u] = dep[fa] + 1;
    dfn[u] = ++idx;
    for (int i = head[u]; i; i = edges[i].next) {
        Edge &e = edges[i];
        if (e.to != fa) {
            g[e.to] = min((LL)e.w, g[u]);
            dfs(e.to, u);
        }
    }
}
void Init() {
	for (int i = 1; i <= n; i++) g[i] = INTINF;
    dfs(1, 0);
    for (int j = 1; j <= 18; j++) for (int i = 1; i <= n; i++)
        f[i][j] = f[f[i][j-1]][j-1];
}
int get_lca(int x, int y) {
    if (dep[x] < dep[y])
        swap(x, y);
    for (int i = 18; i; i--) if (dep[f[x][i]] >= dep[y])
            x = f[x][i];
    if (x == y)
        return x;
    for (int i = 18; i; i--) if (f[x][i] != f[y][i])
        x = f[x][i], y = f[y][i];
    return f[x][0];
}
bool cmp(int i, int j) { return dfn[i] < dfn[j]; }
VI G[MAXN];
int stk[MAXN], top = 0;
void build() {
    stk[top = 1] = 1;
    for (int i = 1; i <= k; i++) {
        int &x = que[i];
        if (top == 1) stk[++top] = x;
        int lca = get_lca(stk[top], x);
        if (lca != stk[top]) {
            while (dfn[lca] < dfn[stk[top-1]])
            	G[stk[top-1]].PB(stk[top]), top--;
            G[lca].PB(stk[top--]);
            if (lca != stk[top]) stk[++top] = lca;
            stk[++top] = x;
        }
    }
    while (top > 1) G[stk[top-1]].PB(stk[top]), top--;
}
LL DP(int u) {
    if (!G[u].size()) return g[u];
    LL res = 0;
    for (auto v : G[u]) res += DP(v);
    G[u].clear();
    return min(res, g[u]);
}
int main() {
    n = read();
    for (int i = 2; i <= n; i++) {
        int u = read(), v = read(), w = read();
        add_net(u, v, w);
    }
    Init();
    m = read();
    while (m--) {
        k = read();
        for (int i = 1; i <= k; i++) que[i] = read();
        sort(que+1, que+1+k, cmp);
        build();
        printf("%lld\n", DP(1));
    }
    return 0;
}

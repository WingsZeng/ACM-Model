/* 寻找左边点u的匹配, 存图只需要左边点连向右边点的有向边即可 */
bool match(int u) {
	for (int v : G[u]) if (!vis[v]) {
		vis[v] = 1;	// 右边点v访问标记
		// 如果右边点没有被左边点匹配到, 让u和v匹配
		// 或者被匹配的左边点my[v]可以找到其他右边点的匹配
		// 那么让my[v]和其他右边点匹配, 让u和v匹配
		if (!my[v] || match(my[v])) {
			mx[u] = v, my[v] = u;	// 记录匹配点
			return true;
		}
	}
	return false;
}
/* 匈牙利算法, 左边点个数nx, 右边点个数ny */
int hungarian(int nx, int ny) {
	int cnt = 0;
	for (int u = 1; u <= nx; u++) {	// 每个左边点都尝试匹配
		for (int v = 1; v <= ny; v++) vis[v] = 0;
		if (match(u)) cnt++;
	}
	return cnt;
}

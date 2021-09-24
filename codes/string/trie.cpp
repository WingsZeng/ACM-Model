int trie[MAXM][30], tot = 1, ed[MAXM];	// $MAXM = MAXN \log MAXN$
void insert(char str[], int id) {
	int cur = 1;	// 当前点, 一步步向下走
	for (int k = 0; str[k]; k++) {
		int ch = str[k] - 'a';
		if (trie[cur][ch] == 0)	// 没有点则新建
			trie[cur][ch] = ++tot;
		cur = trie[cur][ch];
	}
	ed[cur] = id;	// 字符串终点, 记录
}
int search(char str[]) {
	int cur = 1;	// 当前点, 一步步向下走
	for (int k = 0; str[k]; k++) {
		cur = trie[cur][str[k] - 'a'];
		if (!cur) return -1;	// 没有点则找不到
	}
	return ed[cur];	// 找到并返回
}

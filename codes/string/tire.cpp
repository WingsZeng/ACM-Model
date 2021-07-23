// TODO
struct TireNode {
	int sons[30], id, app;
	void clear() {
		id = app = 0;
		memset(sons, 0, sizeof(sons));
	}
} nodes[MAXN];
struct Tire {
	int root = 0, nd = 0, idx = 0;
	void init() {
		root = 0, nd = 0, idx = 0;
		nodes[0].clear();
	}
	/* 找对应字符串的ID, 不存在就分配一个新的ID */
	/* 注意无论是否存在, 该函数都会在Tire上建点 */
	int get_id(char *str) {
		int k = root;
		char c;
		for (int i = 0; str[i]; i++) {
			c = str[i] - 'a';
			if (!nodes[k].sons[c])
				nodes[k].sons[c] = ++nd;
			k = nodes[k].sons[c];
		}
		if (!nodes[k].id)
			nodes[k].id = ++idx;
		return nodes[k].id;
	}
};

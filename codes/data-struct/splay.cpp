int data[MAXN];
struct node *NIL;
struct node {
	int key, siz;
	bool rev;
	node *ch[2], *fa;
	int dir() { return fa -> ch[1] == this; }
	void setchild(node *x,int d) {
		ch[d] = x;
		x->fa = (x == NIL) ? NIL : this;
	}
	void PushUp() { siz = ch[0] -> siz + ch[1] -> siz + 1; }
	void PushDown() {
		if (!rev) return ;
		swap(ch[0],ch[1]);
		ch[0] -> rev ^= 1; ch[1] -> rev ^= 1;
		rev=0;
	}
} tree[MAXN], *ncnt, *root;
bool ok=0;
void Init() {
	ok = 0;
	root = NIL = ncnt = &tree[0];
	NIL -> key = -INF;
	NIL -> siz = NIL -> rev = 0;
	NIL -> fa = NIL -> ch[0] = NIL -> ch[1] = NIL;
}
node *Newnode(int val) {
	node *p = ++ncnt;
	p -> key = val, p -> siz = 1, p -> rev = 0;
	p -> fa = p -> ch[0] = p -> ch[1] = NIL;
	return p;
}
void Rotate(node *x) {
	node *y = x -> fa;
	int d = x -> dir();
	if (y == root) root = x;
	else y -> fa -> setchild(x, y -> dir());
	x -> fa = y -> fa;
	y -> setchild(x -> ch[!d], d);
	x -> setchild(y, !d);
	y -> PushUp();
}
void Splay(node *x, node *rt) {
	node *y, *z;
	x -> PushDown();
	while (x -> fa != rt) {
		y = x->fa; z = y -> fa;
		if (z == rt) Rotate(x);
		else {
			if (x -> dir() == y->dir()) Rotate(y);
			else Rotate(x);
			Rotate(x);
		}
	}
	x -> PushUp();
}
void Insert(node*rt, int val) {
	if (rt == NIL) { rt = Newnode(val); return; }
	node *x = rt;
	int d = 0;
	while (1) {
		d = (val > x -> key);
		if (x -> ch[d] == NIL) break;
		x = x -> ch[d];
	}
	node *y = Newnode(val);
	x -> setchild(y, d);
	x -> PushUp();
	Splay(y, NIL);
}
node *Select(int k, node *f) {
	node *p = root;
	int lsz;
	while (1) {
		p -> PushDown();
		lsz = p -> ch[0] -> siz;
		if (k == lsz + 1) break;
		if (k <= lsz) p = p -> ch[0];
		else p = p -> ch[1], k = k - lsz - 1;
	}
	Splay(p, f);
	return p;
}
node *Maketree(node *fa, int l, int r) {
	if (l > r) return NIL;
	int mid = (l + r) >> 1;
	node *p = Newnode(data[mid]);
	p -> ch[0] = Maketree(p, l, mid - 1);
	p -> ch[1] = Maketree(p, mid + 1, r);
	p -> fa = fa;
	p -> PushUp();
	return p;
}
void dfs(node *rt) {
	if (rt == NIL) return;
	rt -> PushDown();
	dfs(rt -> ch[0]);
	if (rt -> key != INF && rt -> key != -INF) {
		if(ok) printf(" ");
		ok = 1;
		printf("%d",rt -> key);
	}
	dfs(rt -> ch[1]);
}

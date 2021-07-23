
/***** 用堆顶(根)代表整个堆, 如果需要任意点, 可用并查集使点指向他们的根 *****/
int idx, val[MAXN], lch[MAXN], rch[MAXN], d[MAXN];// d是往右儿子最多走的步数
/* 合并x, y所代表的堆 */
int merge(int x, int y){
    if (!x) return y;
    if (!y) return x;
    if (val[x] < val[y]) swap(x, y);
    rch[x] = merge(rch[x], y);
    if (d[lch[x]] < d[rch[x]])	// 维护左偏性质
        swap(lch[x], rch[x]);
    d[x] = d[rch[x]] + 1;
    return x;
}
/* 新建单节点左偏树, 返回编号 */
int init_node(int v) {
	val[++idx] = v;
	lch[idx] = rch[idx] = d[idx] = 0;
	return idx;
}
/* 在树t中插入权值为v的点 */
int insert(int t, int v){ return merge(t, init_node(v)); }
/* 取顶, 由于顶就是代表元, 所以直接返回他的权值即可 */
int top(int t) { return val[t]; }
/* 删除堆顶, 直接合并左右儿子即可 */
int pop(int t){ return merge(lch[t], rch[t]); }

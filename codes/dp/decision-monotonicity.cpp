struct Node { int l, r, p; } que[MAXN];
int dp[MAXN];
int w(int l, int r) {};	//dp[r] = dp[l] + w(l, r);
void DP() {
	int tail = 0;
	que[tail++] = Node{1, n, 0};
	for (int i = 1; i <= n; i++) {
		int cur = -1, L = 0, R = tail-1;
		while (L <= R) {
			int mid = (L+R)>>1;
			if (que[mid].l <= i) cur = mid, L = mid + 1;
			else R = mid - 1;
		}
		int p = que[cur].p, cur = -1;
		dp[i] = dp[p] + w(p, i);
		while (tail && dp[i] + w(i, que[tail-1].l) <= dp[que[tail-1].p] + w(que[tail-1].p, que[tail-1].l))
			cur = que[--tail].l;
		L = que[tail-1].l, R = que[tail-1].r;
		while (L <= R) {
			int mid = (L+R) >> 1;
			if (dp[i] + w(i, mid) <= dp[que[tail-1].p] + w(que[tail-1].p, mid))
				que[tail-1].r = mid - 1, R = mid - 1, cur = mid;
			else L = mid + 1;
		}
		if (cur != -1) que[tail++] = Node{cur, n, i};
	}
}

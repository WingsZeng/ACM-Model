// TODO
LL dp[maxn], s[maxn];
int n, q[maxn], head, tail;
LD a, b, c;
inline LD K(int i) { return 2*a*s[i]; }
inline LD X(int i) { return s[i]; }
inline LD Y(int i) { return dp[i] + a*s[i]*s[i] - b*s[i] + c; }
inline LD Slope(int i, int j) {
	return (Y(i) - Y(j)) / (X(i) - X(j));
}
int main() {
	scanf("%d%Lf%Lf%Lf", &n, &a, &b, &c);
	for (int i = 1; i <= n; i++) {
		int x;
		scanf("%d", &x);
		s[i] = s[i-1] + x;
	}
	q[head = tail = 1] = 0;
	for (int i = 1; i <= n; i++) {
		while (head < tail && K(i) < Slope(q[head], q[head+1]))
			head++;			// 因为斜率单调, 所以可以直接把队头pop
		int j = q[head];	// 并且队头就是最决策点
		dp[i] = dp[j] + a*(s[i]-s[j])*(s[i]-s[j]) + b*(s[i]-s[j]) + c;
		while (head < tail && Slope(i, q[tail]) > Slope(q[tail], q[tail-1]))
			tail--;			//维护凸包
		q[++tail] = i;
	}
	printf("%lld", dp[n]);
	return 0;
}

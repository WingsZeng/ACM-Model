int len = 1;
b[0] = a[0];
for (int i = 1; i < n; i++) {
	if (a[i] >= b[len-1]) b[len++] = a[i];
	else {
		int p = lower_bound(b, b + len, a[i]);
		b[p] = a[i];
	}
}

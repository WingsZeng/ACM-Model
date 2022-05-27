void exgcd(int a, int b, int &x, int &y) {
	if (b) { exgcd(b, a % b, y, x); y -= x * (a / b); }
	else { x = 1, y = 0; }
}
int pls(LL a, LL b) {
	a += a < 0 ? P : 0, b += b < 0 ? P : 0;
	return a + b >= P ? a + b - P : a + b;
}
int mult(LL a, LL b) {
	a += a < 0 ? P : 0, b += b < 0 ? P : 0;
	return a * b >= P ? a * b % P : a * b;
}

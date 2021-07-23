double eps = 1e-8;
int sgn(double x) {
	if (fabs(x) < eps) return 0;
	return x > 0 ? 1 : -1;
}

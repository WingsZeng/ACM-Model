typedef vector<pair<LL, LL>> VPLL;
VPLL block_div(LL x) {
	VPLL v; 		// $\forall i \in [l, r], \left\lfloor\frac{x}{i} \right\rfloor = \left\lfloor\frac{x}{l} \right\rfloor$
	for (LL l = 1, r; l <= x; l = r + 1)
		r = x / (x / l), v.emplace_back(r, x / l);
	return v;
}

Circle minCircleCover(Point p[], int n) {
	random_shuffle(p + 1, p + n + 1);	// 打乱保证随机
	Circle C = {p[1], 0};	// 初始随便一点
	for (int i = 2; i <= n; i++)
		if (C.pointRelation(p[i]) == 1) {	// 点 $p_i$ 在圆外
			C = {p[i], 0};
			for (int j = 1; j < i; j++)
				if (C.pointRelation(p[j]) == 1) {	// 点 $p_j$ 在圆外
					C = {(p[i] + p[j]) / 2, pointDistance(p[i], p[j]) / 2};
					for (int k = 1; k < j; k++)
						if (C.pointRelation(p[k]) == 1)	// 点 $p_k$ 在圆外
							C = getOuterCircle(p[i], p[j], p[k]);
				}
		}
	return C;
}

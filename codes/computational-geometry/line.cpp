struct Line {
	Point P; Vec v; // 点向式, 注意两点需要转化再存储
	/* 获取直线上某一点 (线段起点) */
	Point point(double t = 0) { return P + (v * t); }
	/* 获取线段终点 */
	Point endpoint() { return point(1); }
	/* 点相对直线的位置, 1为右边, -1为左边, 0在直线上 */
	int pointRelative(Point Q) { return sgn((Q - P) ^ v); }
	/* 点到直线的有向距离, 正为右边, 负为左边, 0在直线上 */
	double pointDistance(Point Q) { return ((Q - P) ^ v) / v.length(); }
	/* 点在直线上的投影 */
	Point pointProjection(Point Q) {
		return point(((Q - P) * v) / v.length() / v.length());
	}
	/* 点是否在线段上(不包括端点) 如需包括端点, 改 < 为 <= */
	bool isContainPoint(Point Q) {
		return !pointRelative(Q) && sgn((Q-point()) * (Q-endpoint())) < 0;
	}
	/* 线段长度 */
	double length() { return v.length(); }
	/* 求点 P 关于直线的对称点 */
	Point pointSymmetry(Point P){
		Point Q = pointProjection(P);
		return Point{2 * Q.x - P.x, 2 * Q.y - P.y};
	}
};
typedef Line Segment; // 线段也用点向式存, 注意两点转化
/* 直线是否相交 */
bool isLineIntersection(Line l1, Line l2) { return sgn(l1.v ^ l2.v); }
/* 直线是否平行 */
bool isLineParallel(Line l1, Line l2) {
	return !isLineIntersection(l1, l2);
}
/* 直线是否重合 */
bool isLineCoincident(Line l1, Line l2) {
	return isLineParallel(l1, l2) && !l1.pointRelative(l2.point()) && !l1.pointRelative(l2.endpoint());
}
/* 求两直线的交点, 调用前需保证相交 */
Point getLineIntersection(Line l1, Line l2) {
	Vec u = l1.point() - l2.point();
	double t = (l2.v ^ u) / (l1.v ^ l2.v);
	return l1.point(t);
}
/* 线段是否与直线相交(不包括端点) 包括端点该 < 为 <= */
bool isSegmentIntersectLine(Segment s, Line l) {
	return l.pointRelative(s.point()) * l.pointRelative(s.endpoint()) < 0;
}
/* 线段是否相交(是否包括端点取决于上一个函数) */
bool isSegmentIntersecting(Segment s1, Segment s2) {
	return isSegmentIntersectLine(s1, s2) && isSegmentIntersectLine(s2, s1);
}

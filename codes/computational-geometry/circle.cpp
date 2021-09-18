const double PI = 3.14159265358;
struct Circle {
	Point O; double r;  //圆心和半径
	/* 面积 */
	double area() { return PI * r * r; }
	/* 周长 */
	double circumFerence() { return 2 * PI * r; }
	/* 点和圆的关系; 0 圆上, -1 圆内, 1 圆外 */
	int pointRelation(Point P){
		return sgn(pointDistance(O, P) - r);
	}
	/* 直线和圆的关系; 返回交点个数 */
	int lineRelation(Line l){
		double dst = fabs(l.pointDistance(O));
		if (sgn(dst - r) < 0) return 2;
		else if (!sgn(dst - r)) return 1;
		return 0;
	}
	/* 两圆的关系; 5 相离, 4 外切, 3 相交, 2 内切, 1 内含 */
	int circleRelation(Circle v) {
		double d = pointDistance(O, v.O);
		if (sgn(d - r - v.r) > 0) return 5;
		if (sgn(d - r - v.r) == 0) return 4;
		double l = fabs(r - v.r);
		if (sgn(d - r - v.r) < 0 && sgn(d - l) > 0) return 3;
		if (sgn(d - l) == 0) return 2;
		return 1;
	}
	/* 求两个圆的交点; 返回交点个数 */
	int getCircleIntersection(Circle v, Point &p1, Point &p2) {
		int rel = circleRelation(v);
		if (rel == 1 || rel == 5) return 0;
		double d = pointDistance(O, v.O);
		double l = (d * d + r * r - v.r * v.r) / (2 * d);
		double h = sqrt(r * r - l * l);
		Point tmp = O + (v.O - O).trunc(l);
		p1 = tmp + ((v.O - O).rotleft().trunc(h));
		p2 = tmp + ((v.O - O).rotright().trunc(h));
		if(rel == 2 || rel == 4) return 1;
		return 2;
	}
	/* 求直线和圆的交点; 返回交点个数 */
	int getLineIntersection(Line l, Point &p1, Point &p2){
		if(!(*this).lineRelation(l)) return 0;
		Point A = l.pointProjection(O);
		double d = l.pointDistance(O);
		d = sqrt(r * r - d * d);
		if (!sgn(d)) {
			p1 = p2 = A;
			return 1;
		}
		p1 = A + l.v.trunc(d), p2 = A - l.v.trunc(d);
		return 2;
	}
	/* 求过某点的切线; 返回切线条数 */
	int getTangentLine(Point q, Line &u, Line &v) {
		int x = pointRelation(q);
		if(x == 2) return 0;
		if(x == 1) {
			v = u = Line{q, q - O.rotleft()};
			return 1;
		}
		double d = pointDistance(O, q), l = r * r / d, h = sqrt(r * r - l * l);
		u = Line{q, O + ((q-O).trunc(l) + (q-O).rotleft().trunc(h)) - q};
		v = Line{q, O + ((q-O).trunc(l) + (q-O).rotright().trunc(h)) - q};
		return 2;
	}
	/* 求三角形OAB与圆相交的面积 */
	double triangIntersectingArea(Point A, Point B) {
		if(!sgn((O - A) ^ (O - B))) return 0.0;
		Point q[5];
		int len = 0;
		q[len++] = A;
		Line l = {A, B - A};
		Point p1,p2;
		if (getLineIntersection(l, q[1], q[2]) == 2) {
			if(sgn((A - q[1]) * (B - q[1])) < 0) q[len++] = q[1];
			if(sgn((A - q[2]) * (B - q[2])) < 0) q[len++] = q[2];
		}
		q[len++] = B;
		if (len == 4 && sgn((q[0] - q[1]) * (q[2] - q[1])) > 0)
			swap(q[1], q[2]);
		double res = 0;
		for (int i = 0; i < len - 1; i++) {
			if (!pointRelation(q[i]) || !pointRelation(q[i + 1])) {
				double arg = angle(q[i] - O, q[i + 1] - O);
				res += r * r * arg / 2.0;
			}
			else res += fabs((q[i] - O) ^ (q[i + 1] - O)) / 2.0;
		}
		return res;
	}
};
/* 三角形外接圆 */
Circle getOuterCircle(Point A, Point B, Point C) {
	Line u = {(A + B) / 2, (B - A).rotleft()};
	Line v = {(B + C) / 2, (C - B).rotleft()};
	Point O = getLineIntersection(u, v);
	double r = pointDistance(A, O);
	return Circle{O, r};
}
/* 三角形内切圆 */
Circle getInnerCircle(Point A, Point B, Point C) {
	double m = atan2(B.y - A.y, B.x - A.x);
	double n = atan2(C.y - A.y, C.x - A.x);
	Line u = {A, Point{cos((n + m) / 2), sin((n + m) / 2)}};
	m = atan2(A.y - B.y, A.x - B.x), n = atan2(C.y - B.y, C.x - B.x);
	Line v = {B, Point{cos((n+m)/2),sin((n+m)/2)}};
	Point O = getLineIntersection(u, v);
	Line AB = {A, B - A};
	double r = fabs(AB.pointDistance(O));
	return Circle{C, r};
}
/* 两圆相交面积 */
double circleIntersectingArea(Circle c1, Circle c2){
	int rel = c1.circleRelation(c2);
	if(rel >= 4) return 0.0;
	if(rel <= 2) return min(c1.area(),c2.area());
	double d = pointDistance(c1.O, c2.O);
	double hf = (c1.r + c2.r + d) / 2.0;
	double ss = 2 * sqrt(hf * (hf - c1.r) * (hf - c2.r) * (hf - d));
	double a1 = acos((c1.r*c1.r + d*d - c2.r*c2.r) / (2.0 * c1.r * d));
	a1 *= c1.r * c1.r;
	double a2 = acos((c2.r*c2.r + d*d - c1.r*c1.r) / (2.0 * c2.r * d));
	a2 *= c2.r * c2.r;
	return a1 + a2 - ss;
}

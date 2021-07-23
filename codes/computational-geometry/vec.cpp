struct Vec {
	double x, y;
	Vec operator + (const Vec &B) const { return Vec{x + B.x, y + B.y}; }
	Vec operator - (const Vec &B) const { return Vec{x - B.x, y - B.y}; }
	Vec operator * (const double k) const { return Vec{x * k, y * k}; }
	Vec operator / (const double k) const { return Vec{x / k, y / k}; }
	double operator * (const Vec &B) const { return x * B.x + y * B.y; }
	double operator ^ (const Vec &B) const { return x * B.y - y * B.x; }
	bool operator == (const Vec &B) const {
		return !sgn(x - B.x) && !sgn(y - B.y);
	}
	bool operator < (const Vec &V) const {
		return x == V.x ? y < V.y : x < V.x;
	}
	double length() {
		Vec A = *this;
		return sqrt(A * A);
	}
	/* 化为长度为r的向量 */
	Vec trunc(double r){
		double l = length();
		if(!sgn(l)) return (*this);
		r /= l;
		return Vec{x * r, y * r};
	}
	/* 逆时针旋转90度 */
	Vec rotleft(){ return Vec{-y, x}; }
	/* 顺时针旋转90度*/
	Vec rotright(){ return Vec{y, -x}; }
	/* 绕着点P逆时针旋转angle */
	Vec rotate(Vec p, double angle) {
		Vec v = (*this) - p;
		double c = cos(angle), s = sin(angle);
		return Vec{p.x + v.x * c - v.y * s, p.y + v.x * s + v.y * c};
	}
};
typedef Vec Point;	// 点的记录方式和向量相同
/* 求两向量的夹角 (无向, 且夹角在[0, PI]之间, 弧度制) */
double angle(Vec &A, Vec &B) {
	return acos((A * B) / A.length() / B.length());
}
/* 两点距离 */
double pointDistance(Point A, Point B) { return (A-B).length(); }
/* 三角形面积 */
double triangle_area(Point A, Point B, Point C) {
	Vec v = B - A, u = C - A;
	return fabs(v ^ u) / 2;
}

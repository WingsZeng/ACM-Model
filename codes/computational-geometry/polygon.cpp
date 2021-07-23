struct Polygon {
	int n;		// 数据大可能需要不使用结构体
	Point points[MAXN];  // 逆时针排序
	Line lines[MAXN];    // 边
	void init(int _n, Point _ps[]) {
		n = _n;
		for (int i = 1; i <= n; i++)
			points[i] = _ps[i];
		points[0] = _ps[n];
	}
	/* 获取边 */
	void getLines() {
		for (int i = 0; i < n; i++)
			lines[i+1] = Line{points[i], points[i+1] - points[i]};
	}
	/* 以点p0为基点, 进行极角排序的比较函数*/
	struct cmp{
		Point p;
		cmp(const Point &p0) { p = p0; }
		bool operator() (const Point &aa, const Point &bb) {
			Point a = aa, b = bb;
			int d = sgn((a - p) ^ ( b - p ));
			if (d == 0)
				return sgn(pointDistance(p, a) - pointDistance(p, b)) < 0;
			return d > 0;
		}
	};
	/* 极角排序 */
	void norm() {
		Point mi = points[1];
		for (int i = 2; i <= n; i++) mi = min(mi, points[i]);
		sort(points + 1, points + 1 + n, cmp(mi));
	}
	/* 求多边形有向面积 */
	double area() {
		double res = 0;
		for (int i = 0; i < n; i++)
			res += points[i] ^ points[i + 1];
		return res / 2.0;
	}
	/* 求多边形周长 */
	double circumFerence() {
		double sum = 0;
		for(int i = 0; i < n; i++)
			sum += pointDistance(points[i], points[i + 1]);
		return sum;
	}
	/* Graham求凸包; 注意如果有影响, 要特判下所有点共点, 或者共线的特殊情况 */
	void graham(Polygon &convex, bool is_norm) {
		if (!is_norm) norm();
		int &top = convex.n;
		top = 0;
		if (n == 1) {
			top = 1, convex.points[1] = points[1];
		}
		else if (n == 2) {
			top = 2, convex.points[1] = points[1], convex.points[2] = points[2];
			if (convex.points[1] == convex.points[2]) top--;
		}
		else {
			top = 2, convex.points[1] = points[1], convex.points[2] = points[2];
			for (int i = 3; i <= n; i++){
			while (top > 1 && sgn((convex.points[top] - convex.points[top - 1]) ^ (points[i] - convex.points[top - 1])) <= 0)
				top--;
				convex.points[++top] = points[i];
			}
			if(convex.n == 2 && (convex.points[1] == convex.points[2])) convex.n--;//特判
		}
		convex.points[0] = convex.points[convex.n];
	}
	/* 判断多边形是不是凸的 */
	bool isConvex(){
		bool s[2] = {0, 0};
		for (int i = 0; i < n; i++) {
			int j = (i + 1) % n;
			int k = (j + 1) % n;
			s[sgn((points[j] - points[i]) ^ (points[k] - points[i])) + 1] = true;
			if(s[0] && s[2]) return false;
		}
		return true;
	}
	/* 点与多边形位置; 3 点上, 2 边上, 1 内部, 0 外部 */
	int pointRelation(Point q){
		for(int i = 1; i <= n; i++) if(points[i] == q) return 3;
		getLines();
		for(int i = 1; i <= n; i++)
			if(lines[i].isContainPoint(q)) return 2;
		int cnt = 0;
		for(int i = 0; i < n; i++){
			int j = i + 1;
			int k = sgn((q - points[j]) ^ (points[i] - points[j]));
			int u = sgn(points[i].y - q.y), v = sgn(points[j].y - q.y);
			if (k > 0 && u < 0 && v >= 0) cnt++;
			if (k < 0 && v < 0 && u >= 0) cnt--;
		}
		return cnt != 0;
	}
};

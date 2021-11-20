struct Point { double x, y; } points[MAXN];
bool cmpx(const Point &P1, const Point &P2) { return P1.x < P2.x; }
bool cmpy(const Point &P1, const Point &P2) { return P1.y < P2.y; }
double dist(const Point &P1, const Point &P2) {
    return hypot(P1.x - P2.x, P1.y - P2.y);
}
double divide(int l, int r) {
    if (l >= r) return DINF;     // 边界
    if (l + 1 == r) return dist(points[l], points[r]);
    int mid = (l + r) / 2;
    double p = points[mid].x;
    double d = min(divide(l, mid), divide(mid+1, r)); // 分治
    vector<Point> v;    // 把离中线距离小于 d 的丢入 v
    for (int i = l; i <= r; i++)
        if (sgn(fabs(points[i].x - p) - d) < 0)
            v.push_back(points[i]);
    sort(v.begin(), v.end(), cmpy); // 按 y 排序
    for (int i = 0; i < (int)v.size(); i++)
        for (int j = i-1; ~j; j--) { // 可能是最近点对的点个数很少
            if (sgn(v[i].y - v[j].y - d) > 0) break;
            d = min(d, dist(v[i], v[j]));
        }
    return d;
}
double nearestPoints() {
    sort(points+1, points+n+1, cmpx);   // 按 x 排序以分治
    return divide(1, n);
}

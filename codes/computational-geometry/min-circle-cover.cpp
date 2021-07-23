// TODO
#include<bits/stdc++.h>
using namespace std;
const int maxn=100005;
const double eps=1e-12;
struct point{
	double x,y;
}a[maxn];
double dis(point p,point q){
	double x=p.x-q.x,y=p.y-q.y;
	return sqrt(x*x+y*y);
}
point circle_center(point a,point b,point c){
	double x1=a.x,x2=b.x,x3=c.x;
	double y1=a.y,y2=b.y,y3=c.y;
	double A=x1*x1+y1*y1,B=x2*x2+y2*y2,C=x3*x3+y3*y3;
	double u1=x1-x2,u2=x1-x3,u3=x2-x3;
	double v1=y1-y2,v2=y1-y3,v3=y2-y3;
	point o;
	o.y=((C-A)*u1-(B-A)*u2)/(2*v1*u2-2*v2*u1);
	o.x=((C-A)*v1-(B-A)*v2)/(2*u1*v2-2*u2*v1);
	return o;
}
int main(){
	int n;
	scanf("%d", &n);
	for(int i=1;i<=n;i++)
		scanf("%lf%lf",&a[i].x,&a[i].y);
	random_shuffle(a+1,a+n+1);
	point o=a[1];
	double r=0;
	for(int i=2;i<=n;i++){
		if(dis(o,a[i])-r>eps){
			o=a[i];r=0;
			for(int j=1;j<i;j++){
				if(dis(o,a[j])-r>eps){
					o.x=(a[i].x+a[j].x)/2;
					o.y=(a[i].y+a[j].y)/2;
					r=dis(o,a[j]);
					for(int k=1;k<j;k++){
						if(dis(o,a[k])-r>eps){
							o=circle_center(a[i],a[j],a[k]);
							r=dis(o,a[k]);
						}
					}
				}
			}
		}
	}
	printf("%.10lf\n%.10lf %.10lf",r,o.x,o.y);
	return 0;
}

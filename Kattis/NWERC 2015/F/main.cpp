#include <bits/stdc++.h>
#include <iostream>

using namespace std;

struct point3D;
typedef pair<double,double> point;
typedef pair<point3D,point3D> segment;

#define R 6370
#define PI acos(-1)
#define EPS 10e-6


struct point3D {

	double x,y,z;
	
	point3D() {}

	point3D(point& p) {
		x = R*sin(p.first)*cos(p.second);
		y = R*sin(p.first)*sin(p.second);
		z = R*cos(p.first);
		normalize();
	}

	point3D(double x, double y, double z) : x(x), y(y), z(z) { normalize(); }

	void normalize() {
		double norm = norm2();
		x /= norm; y /= norm; z /= norm;
	}

	double norm2() {
		return sqrt(x*x+y*y+z*z);
	}

	double angle(const point3D& p) {
		return acos((x*p.x+y*p.y+z*p.z)/(norm2()*sqrt(p.x*p.x+p.y*p.y+p.z*p.z)));
	}

	void to_string() {
		cout << x << " " << y << " " << z << endl;
	}

};

point3D operator*(const point3D& a, const point3D& b) {
	return point3D(a.y*b.z-a.z*b.y,a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
}

bool operator==(const point3D& a, const point3D& b) {
	return a.x == b.x && a.y == b.y && a.z == b.z;
}

vector<segment> route;
vector<segment> arc;


double segment_angle(segment& s) {
	point3D p1 = s.first, p2 = s.second;
	if(p1 == p2)
		return 0.0;
	return p1.angle(p2);
}

point3D intersection_point(segment& s1, segment& s2) {
	point3D p1 = s1.first, p2 = s1.second, q1 = s2.first, q2 = s2.second;
	point3D cross_prod = (p1*p2)*(q1*q2); cross_prod.normalize();
	return cross_prod;
}

bool is_point_on_segment(segment& s, point3D& p) {
	segment s1 = make_pair(s.first,p), s2 = make_pair(p,s.second);
	return abs(segment_angle(s1)+segment_angle(s2)-segment_angle(s)) < EPS;
}

vector<point3D> split_segment(segment& s) {
	vector<point3D> inter_p;
	inter_p.push_back(s.first);

	for(int i = 0; i < arc.size(); i++) {
		point3D r1 = intersection_point(s,arc[i]);
		point3D r2 = point3D(-r1.x,-r1.y,-r1.z);
		if(is_point_on_segment(s,r1) && is_point_on_segment(arc[i],r1)) 
			inter_p.push_back(r1);
		else {
			if(is_point_on_segment(s,r2)  && is_point_on_segment(arc[i],r2))
				inter_p.push_back(r2);
		}
	}

	inter_p.push_back(s.second);
	sort(inter_p.begin(),inter_p.end(),[&](const point3D& p1, const point3D& p2) {
		return s.first.angle(p1) < s.first.angle(p2);
	});

	return inter_p;
}



void to_radians(point& p) {
	p.first = ((2.0*PI)/360.0)*p.first+PI/2.0;
	p.second = ((2.0*PI)/360.0)*p.second;
}

int main() {

	int c; cin >> c;
	for(int i = 0; i < c; i++) {
		int n; cin >> n;
		point p; cin >> p.first >> p.second; to_radians(p);
		point3D first_p(p); 
		point3D last_p(p);
		for(int j = 0; j < n-1; j++) {
			cin >> p.first >> p.second; to_radians(p);
			point3D cur_p(p);
			segment s = make_pair(last_p,cur_p);
			arc.push_back(s);
			last_p = cur_p;
		}
		segment s = make_pair(last_p,first_p);
		arc.push_back(s);
	}

	int m; cin >> m;
	route.resize(m-1);
	point p; cin >> p.first >> p.second; to_radians(p);
	point3D last_p(p);
	for(int i = 0; i < m-1; i++) {
		cin >> p.first >> p.second; to_radians(p);
		point3D cur_p(p);
		segment s = make_pair(last_p,cur_p);
		route[i] = s;
		last_p = cur_p;
	}

	double length = 0.0;
	for(int i = 0; i < m-1; i++) {	
		length += segment_angle(route[i])*R;
	}

	bool is_on_water = false;
	vector<segment> water_s;
	for(int i = 0; i < m-1; i++) {
		vector<point3D> inter_p = split_segment(route[i]);
		int n = inter_p.size();
		for(int i = 1; i < n-1; i++) {
			if(!is_on_water)
				is_on_water = true;
			else {
				segment s = make_pair(inter_p[i-1],inter_p[i]);
				water_s.push_back(s);
				is_on_water = false;
			}
		}
		if(is_on_water) {
			segment s = make_pair(inter_p[n-2],inter_p[n-1]);
			water_s.push_back(s);
		}
	}

	double water_length = 0.0;
	for(int i = 0; i < water_s.size(); i++) {	
		water_length += segment_angle(water_s[i])*R;
	}

	cout << fixed << setprecision(10) << length << " " << (water_length/length)*100.0 << endl; 

	return 0;
}

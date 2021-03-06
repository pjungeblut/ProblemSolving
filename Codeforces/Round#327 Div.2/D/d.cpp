#include <bits/stdc++.h>
#include <iostream>
using namespace std;


int main() {

	double x1, y1, x2, y2, v, t, vx, vy, wx, wy;
	cin >> x1 >> y1 >> x2 >> y2 >> v >> t >> vx >> vy >> wx >> wy;

	double l = 0, r = 10e9;
	for(int i = 0; i < 200; i++) {
		double m = (l+r)/2;
		double x = x1 + min(m,t)*vx + max(m-t,0.0)*wx;
		double y = y1 + min(m,t)*vy + max(m-t,0.0)*wy;
		double c = hypot(x2-x,y2-y);
		if(c < v*m) r = m;
		else l = m;
	}

	cout << fixed << setprecision(10) << r << endl;
	
	return 0;

}

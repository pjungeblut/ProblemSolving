#include <bits/stdc++.h>
#include <iostream>

using namespace std;

typedef complex<int> pt;
typedef pair<int,pt> pipe;
typedef vector<vector<int>> graph;

graph g;
vector<int> color;

double cross (pt a, pt b) {
	return imag(conj(a) * b);
}

double ccw(pt a, pt b, pt c) {
	return cross(b - a, c - a); // <0 => falls Rechtsknick , 0 => kollinear , >0 => Linksknick
}

// Streckenschnitt , Strecken a-b und c-d
bool lineSegmentIntersection (pt a, pt b, pt c, pt d) {
	if (ccw(a, b, c) == 0 && ccw(a, b, d) == 0) { // kollinear
		double dist = abs(a - b);
		return (abs(a - c) <= dist && abs(b - c) <= dist) || (abs(a - d) <= dist && abs(b - d) <= dist);
	}
	return ccw(a, b, c) * ccw(a, b, d) <= 0 && ccw(c, d, a) * ccw(c, d, b) <= 0;
}

bool bicolor(int i) {
	
	queue<int> q;
	color[i] = 0;
	q.push(i);
	while(!q.empty()) {
		int u = q.front(); q.pop();
		for(int v : g[u]) {
			if(color[v] == -1) {
				color[v] = (1 - color[u]);
				q.push(v);
			}
			else {
				if(color[u] == color[v])
					return false;
			}
		}
	}

	return true;

}

int main() {

	int w, p; cin >> w >> p;

	vector<pt> wells(w);
	for(int i = 0; i < w; i++) {
		int x,y; cin >> x >> y;
		pt p(x,y); wells[i] = p;		
	}	

	vector<pipe> pipes(p);
	for(int i = 0; i < p; i++) {
		int idx,x,y; cin >> idx >> x >> y;
		pt p(x,y); pipes[i] = make_pair(--idx,p);		
	}


	g.assign(p,vector<int>());
	for(int i = 0; i < p; i++) {
		pt s1 = wells[pipes[i].first], e1 = pipes[i].second; 
		for(int j = i+1; j < p; j++) {
			pt s2 = wells[pipes[j].first], e2 = pipes[j].second; 
			if(lineSegmentIntersection(s1,e1,s2,e2) && s1 != s2) {
				g[i].push_back(j);
				g[j].push_back(i);
			}
		}
	}

	/*for(int i = 0; i < p; i++) {
		cout << "Pipe " << i << ":";	
		for(int j : g[i])
			cout << " " <<j;
		cout << endl;
	}*/

	color.assign(p,-1);
	for(int i = 0; i < p; i++) {
		if(color[i] == -1) {
			if(!bicolor(i)) {
				cout << "impossible" << endl;
				return 0;
			}
		}
	}

	cout << "possible" << endl;
	return 0;
}

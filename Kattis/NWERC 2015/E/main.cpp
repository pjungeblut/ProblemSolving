#include <bits/stdc++.h>
#include <iostream>

using namespace std;

typedef long long ll;
typedef pair<ll,ll> task; 
typedef vector<vector<int>> graph;

vector<int> pairs;
vector<bool> visited;

bool dfs(graph& g, int i) {
	if (visited[i]) return false;
	visited[i] = true;
	for(int j : g[i]) {
		if (pairs[j] < 0 || dfs(g,pairs[j])) {
			pairs[j] = i; pairs[i] = j; return true;
		}
	}
	return false;
}

int main() {

	int n; cin >> n;

	vector<task> t(n);
	vector<ll> r;
	map<ll,ll> m_idx;

	int m = 0;
	graph g(n, vector<int>());
	for(int i = 0; i < n; i++) {
		cin >> t[i].first >> t[i].second;
		ll a = t[i].first, b = t[i].second;
		set<ll> res; res.insert(a+b); res.insert(a-b); res.insert(a*b);
		for(ll result : res) {
			int j = 0;
			if(m_idx.find(result) == m_idx.end()) {
				m_idx[result] = m; j = m;
				r.push_back(result);
				g.push_back(vector<int>());
				m++;
			} else {
				j = m_idx[result];
			}
			g[i].push_back(n+j);
			g[n+j].push_back(i);
		}
	}	

	/*cout << n << " " << m << endl;
	for(int i = 0; i < n; i++) {
		cout << t[i].first << " " << t[i].second << " ->";
		for(int j : g[i]) {
			cout << " " << r[j-n]; 
		}
		cout << endl;
	}*/

	//Find bipartite Matching
	pairs.assign(n+m,-1);
	for(int i = 0; i < n; i++) {
		visited.assign(n+m,false);
		if(!dfs(g,i)) {
			cout << "impossible" << endl;
			return 0;
		}
	}

	for(int i = 0; i < n; i++) {
		ll a = t[i].first, b = t[i].second, c = r[pairs[i]-n];
		cout << a;
		if(a + b == c)
			cout << " + ";
		else if(a - b == c)
			cout << " - ";
		else if(a * b == c)
			cout << " * ";
		cout << b << " = " << c << endl;
	}


	return 0;
}

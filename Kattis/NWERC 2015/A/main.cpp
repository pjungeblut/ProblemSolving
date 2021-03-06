#include <bits/stdc++.h>
#include <iostream>

using namespace std;

typedef long long ll;
typedef pair<ll,ll> pll;

int main() {

	ll n, m; cin >> n >> m;
	vector<pll> r(n);
	for(int i = 0; i < n; i++)
		cin >> r[i].first >> r[i].second; 
	
	sort(r.begin(),r.end());

	int unlock = 0;
	priority_queue<ll, vector<ll>, greater<ll> > pq;
	for(int i = 0; i < n; i++) {
		ll a = r[i].first, s = r[i].second;
		while(!pq.empty()) {
			ll u = pq.top();
		
			if(a >= u && a <= u+m) {
				pq.pop(); pq.push(a+s);
				unlock++; break;
			}

			if(a < u) {
				pq.push(a+s); break;
			}

			pq.pop();

		}

		if(pq.empty())
			pq.push(a+s);
	}

	cout << unlock << endl;

	return 0;
}

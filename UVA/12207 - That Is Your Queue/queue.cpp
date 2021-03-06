#include <bits/stdc++.h>
#include <iostream>

using namespace std;

typedef long long ll;

int main() {
	
	int ca = 1;
	ll p, c;
	while(cin >> p >> c) {
		if(p + c == 0)
			break;

		cout << "Case " << ca << ":"<<  endl;
		ca++; 
		if(p > c) {
			ll count = 1;
			set<ll> num; stack<ll> prio;
			for(int i = 0; i < c; i++) {
				char op; cin >> op;
				if(op == 'N') {
					if(!prio.empty()) {
						ll t = prio.top();
						stack<ll> h;
						while(!prio.empty()) {
							if(prio.top() != t)
								h.push(prio.top()); 
							prio.pop();	
						}
						while(!h.empty()) {
							prio.push(h.top()); 
							h.pop();	
						}
						cout << t << endl;
						continue; 
					}
					while(num.find(count) != num.end())
						count++;
					cout << count << endl;
					count++;
				} else if(op == 'E') {
					ll n; cin >> n;
					num.insert(n);
					prio.push(n);
				}
			}
		} else {
			queue<ll> q;
			for(ll i = 1; i <= p; i++)
				q.push(i);
			for(int i = 0; i < c; i++) {
				char op; cin >> op;
				if(op == 'N') {
					ll n = q.front(); q.pop(); q.push(n);
					cout << n << endl;
				} else if(op == 'E') {
					ll n; cin >> n;
					queue<ll> nq;
					nq.push(n);
					while(q.front() != n) {
						 nq.push(q.front()); q.pop();
					}
					q.pop();
					while(!q.empty()) {
						nq.push(q.front()); q.pop();
					}
					swap(q,nq);
				}
			}
	
		}

	}

	return 0;
}

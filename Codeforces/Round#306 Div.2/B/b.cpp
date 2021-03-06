#include <bits/stdc++.h>
#include <iostream>
using namespace std;

typedef long long ll;

int n,l,r,x;
vector<ll> p;

bool isValid(int set) {
	ll sum = 0;
	ll low = -1;
	ll hi = -1;
	for(int i = 0; i < p.size(); i++) {
		if((set & 1 << i) >> i) {
			sum += p[i];
			if(low == -1)
				low = i;
			hi = i;
		}
	}

	if(sum >= l && sum <= r && low != -1 && hi != -1 && p[hi]-p[low] >= x) {
		return true;
	}
	return false;
}


int main() {
	

	cin >> n >> l >> r >> x;
	p.resize(n);
	for(int i = 0; i < n; i++) {
		cin >> p[i];
	}

	sort(p.begin(),p.end());
	
	ll c = 0;
	for(int i = 0; i < pow(2,n); i++) {
		if(isValid(i))
			c++;
	}

	cout << c << endl;


}

#include <bits/stdc++.h>
#include <iostream>
#include <climits>

using namespace std;

int x, y;

bool checkPaveFrame(int a) {
	if(x % a == 0 && (y-2) % a == 0)
		return true;
	else if((x-1) % a == 0 && (y-1) % a == 0)
		return true;
	else if((x-2) % a == 0 && y % a == 0) 
		return true;

	if(a == 2) {
		if((x-1) % 2 == 0 && y % 2 == 0)
			return true;
		else if((y-1) % 2 == 0 && x % 2 == 0)
			return true;
	}
	
	return false;
}

int main() {

	while(cin >> x >> y) {
		int n;
		cin >> n;
		for(int i = 0; i < n; i++) {
			int a;
			cin >> a;
			if(checkPaveFrame(a))
				cout << "YES" << endl;
			else 
				cout << "NO" << endl;
		}

	}
	
 
	return 0;
}

#include <bits/stdc++.h>
#include <iostream>
using namespace std;


int main() {

	int n;
	cin >> n;
	
	vector<bool> hor(n,false);
	vector<bool> ver(n,false);

	int h, v;
	vector<int> work;
	int day = 1;
	while(cin >> h >> v) {
		if(!hor[h] && !ver[v]) {
			work.push_back(day);
			hor[h] = true; ver[v] = true;
		}
		day++;
	}	

	for(int i = 0; i < work.size()-1; i++)
		cout << work[i] << " ";
	cout <<	work[work.size()-1] << endl;

}

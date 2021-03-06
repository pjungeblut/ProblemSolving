#include <bits/stdc++.h>
#include <iostream>

using namespace std;

typedef pair<int,int> point;

int max_coins, r, c;
point start;
vector<point> stones, coins;
vector<int> permut;

vector<point> dir = {point(1,0),point(0,1),point(-1,0),point(0,-1)};

point operator+(const point p1, const point p2) {
	return make_pair(p1.first+p2.first,p1.second+p2.second);
}

bool isValidPoint(vector<vector<char>>& m, point& p) {
	if(p.first >= r || p.second >= c || p.first < 0 || p.second < 0)
		return false;
	
	if(m[p.first][p.second] == 'O' || m[p.first][p.second] == 'X')
		return false;

	return true;
}

bool isReachable(vector<vector<char>>& m, point& s, point& e) {
	vector<vector<bool>> vis(r,vector<bool>(c,false));
	queue<point> q; q.push(s); vis[s.first][s.second] = true;
	while(!q.empty()) {
		point p = q.front(); q.pop();
		if(p == e)
			return true;

		for(int i = 0; i < 4; i++) {
			point np = p + dir[i];
			if(isValidPoint(m,np) && !vis[np.first][np.second]) {
				q.push(np); vis[np.first][np.second] = true;
			}
		}
		
	}
	return false;
} 

void move_stone(vector<vector<char>>& m, point& old_start, point& new_start, point& stone, point& obstacle, bool backward) {
	start = new_start;
	if(backward) {
		m[old_start.first][old_start.second] = '.';
		m[new_start.first][new_start.second] = 'S';
		m[stone.first][stone.second] = 'O';
		m[obstacle.first][obstacle.second] = '.';
	}
	else {
		m[stone.first][stone.second] = '.';
		m[obstacle.first][obstacle.second] = 'X';
		m[old_start.first][old_start.second] = '.';
		m[new_start.first][new_start.second] = 'S';
	}
}

void printMap(vector<vector<char>>& m) {
	for(int i = 0; i < r; i++) {
		for(int j = 0; j < c; j++) {
			cout << m[i][j];
		}
		cout << endl;
	}
	string l(c,'#');
	cout << l << endl;
}

void find_max(int pos, vector<vector<char>>& m, set<point> cur_coins) {
	for(int i = 0; i < coins.size(); i++) {
		if(isReachable(m,start,coins[i])) {
			cur_coins.insert(coins[i]);
		}
	}

	if(cur_coins.size() > max_coins)
		max_coins = cur_coins.size();

	if(pos == stones.size())
		return;

	for(int i = 0; i < 4; i++) {
		point old_start = start;
		point stone = stones[permut[pos]];
		point m_stone = stone + dir[i];
		point new_field = stone + dir[(i + 2) % 4];
		if(isValidPoint(m,m_stone) && isValidPoint(m,new_field) && isReachable(m,start,m_stone) && m[new_field.first][new_field.second] == '.') {
			move_stone(m,old_start,stone,stone,new_field,false);
			find_max(pos+1,m,cur_coins);
			move_stone(m,stone,old_start,stone,new_field,true);
		}
	}

}


int main() {

	int test; cin >> test;
	while(test--) {
		cin >> r >> c;
		stones.clear(); coins.clear();
		vector<vector<char>> m(r,vector<char>(c));
		for(int i = 0; i < r; i++) {
			for(int j = 0; j < c; j++) {
				cin >> m[i][j];
				point p = make_pair(i,j);
				if(m[i][j] == 'S')
					start = p;
				else if(m[i][j] == 'C')
					coins.push_back(p);
				else if(m[i][j] == 'O') 
					stones.push_back(p);
			}
		}

		permut.clear();
		for(int i = 0; i < stones.size(); i++) {
			permut.push_back(i);
		}		

		max_coins = 0;
		set<point> cur_coins;
		do {
			find_max(0,m,cur_coins);
		} while(next_permutation(permut.begin(),permut.end()));
		cout << max_coins << endl;
	
	}

	return 0;
}

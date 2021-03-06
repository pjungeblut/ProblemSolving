#include <bits/stdc++.h>
#include <iostream>
using namespace std;

typedef vector<string> face;
struct point2D {
    int x, y;
    point2D(int x, int y) : x(x), y(y) { }
};
struct point3D {
    int x, y, z;
    point3D(int x, int y, int z) : x(x), y(y), z(z) { }
    
    void to_string() {
            cout << "("<< x << ", " << y << ", " << z << ")" <<endl;
    }
};
typedef pair<string,point3D> sp;
point3D operator+(const point3D& p1, const point3D& p2) {
        return point3D(p1.x+p2.x,p1.y+p2.y,p1.z+p2.z);
}
point2D  operator+(const point2D& p1, const point2D& p2) {
        return point2D(p1.x+p2.x,p1.y+p2.y);
}
vector<point3D> dir3D = {point3D(-1,0,0),point3D(1,0,0),point3D(0,0,1),point3D(0,0,-1),point3D(0,1,0),point3D(0,-1,0)};                     
int n;
vector<char> d = {'F','B','L','R','U','D'};
vector<face> f;
map<char,int> dm;
void initialize() {
    dm['F'] = 0; dm['R'] = 1; dm['B'] = 2; dm['L'] = 3; dm['U'] = 4; dm['D'] = 5;
}
point2D mapPoint(char c, point3D& p) {
        if(c == 'F')
            return point2D(n-1-p.y,n-1-p.z);
        if(c == 'R')
            return point2D(n-1-p.y,p.x);
        if(c == 'B')
            return point2D(n-1-p.y,p.z);
        if(c == 'L')
            return point2D(n-1-p.y,n-1-p.x);
        if(c == 'U')
            return point2D(n-1-p.x,n-1-p.z);
        if(c == 'D')
            return point2D(p.x,n-1-p.z);
}
bool isValidFacePoint(face& f, point2D& p) {
    return f[p.x][p.y] == ' ';
}
bool isValidPoint(point3D& p) {
        for(int i = 0; i < 6; i++) {
            point2D map_p = mapPoint(d[i],p);
            if(!isValidFacePoint(f[dm[d[i]]],map_p))
                return false;
        }
        return true;
}
void initializeFace(int n) {
        f.clear();
        f.assign(6,vector<string>(n));
}

int main() {
    initialize();
    
    string line;
    while(getline(cin,line)) {
            n = atoi(line.c_str());
            if(n == 0)
                break;
            
            initializeFace(n);
            for(int i = 0; i < 6; i++) {
                    for(int j = 0; j < n; j++) {
                            getline(cin,f[i][j]);
                    }
            }
            
            vector<vector<vector<bool>>> visited(n,vector<vector<bool>>(n,vector<bool>(n,false)));
            queue<sp> q;
            point3D start(1,1,1);
            visited[1][1][1] = true;
            q.push(make_pair(string(""),start));
            string way = "";
            while(!q.empty()) {
                    sp cur = q.front(); q.pop();
                    string cur_w = cur.first;
                    point3D cur_p = cur.second;
                    
                    if(cur_p.x == n-2 && cur_p.y == n-2 && cur_p.z == n-2) {
                            way = cur_w;
                            break;
                    }
                    
                    for(int i = 0; i < 6; i++) {
                        point3D new_p = cur_p + dir3D[i];
                        if(!visited[new_p.x][new_p.y][new_p.z] && isValidPoint(new_p)) {
                            visited[new_p.x][new_p.y][new_p.z] = true;
                            string new_w(cur_w+""+d[i]);
                            q.push(make_pair(new_w,new_p));
                        }
                    }
            }
            
            cout << way << endl;
            
            
    }
    
    
    return 0;
}

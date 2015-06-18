#include <bits/stdc++.h>
#include <iostream>

using namespace std;

typedef pair<string,string> ss;
typedef map<string,vector<string> > graph;

set<string> s1;
set<string> s2;

void dfs1(graph& g, string& node, map<string,bool>& visited, map<string,string>& translation, map<string,string>& translation2, map<string,bool>& translated, vector<string> path) {
	
    if(path.size() == 5) {
	if(path[0].compare(path[4]) == 0) {
		translation[path[0]] = path[1];
		translation[path[3]] = path[2];
		translation2[path[1]] = path[0];
		translation2[path[2]] = path[3];
		translated[path[0]] = true;
		translated[path[1]] = true;
		translated[path[2]] = true;
		translated[path[3]] = true;
	}
	return;
    }

    bool look_trans = false;
    set<string> next_node_set;
    if(path.size() == 1) {
	look_trans = true;
	next_node_set = s2;
    } else if(path.size() == 2) {
	next_node_set = s2;
    } else if(path.size() == 3) {
	look_trans = true;
	next_node_set = s1;
    } else if(path.size() == 4) {
	next_node_set = s1;
    }


    vector<string> adj_words = g[node];
    for(int i = 0; i < adj_words.size(); i++) {
	  string next_node = adj_words[i];
	  if(look_trans) {
		if(translated[node] || translated[next_node]) {
			if(translation.count(node) && next_node.compare(translation[node]) != 0)
				continue;
			else if(translation2.count(node) && next_node.compare(translation2[node]) != 0)
				continue;
			else if(translation.count(next_node) && node.compare(translation[next_node]) != 0) 
				continue;
			else if(translation2.count(next_node) && node.compare(translation2[next_node]) != 0)
				continue;
		}
	  }
	  if((!visited[next_node] && next_node_set.find(next_node) != next_node_set.end())
		|| (path.size() == 4 && path[0].compare(next_node) == 0)) {
	      path.push_back(next_node);
		visited[next_node] = true;
	      dfs1(g,next_node,visited,translation,translation2,translated,path);
	      if(path[0].compare(next_node) != 0)
		visited[next_node] = false;
	      path.pop_back();
	  }
    }

}

void dfs2(graph& g, string& node, map<string,bool>& visited, map<string,string>& translation, map<string,string>& translation2, map<string,bool>& translated, vector<string> path) {
	
    if(path.size() == 5) {
	if(path[0].compare(path[4]) == 0) {
		translation[path[0]] = path[3];
		translation[path[1]] = path[2];
		translation2[path[3]] = path[0];
		translation2[path[2]] = path[1];
		translated[path[0]] = true;
		translated[path[1]] = true;
		translated[path[2]] = true;
		translated[path[3]] = true;
	}
	return;
    }

    bool look_trans = false;
    set<string> next_node_set;
    if(path.size() == 1) {
	next_node_set = s1;
    } else if(path.size() == 2) {
	look_trans = true;
	next_node_set = s2;
    } else if(path.size() == 3) {
	next_node_set = s2;
    } else if(path.size() == 4) {
	look_trans = true;
	next_node_set = s1;
    }


    vector<string> adj_words = g[node];
    for(int i = 0; i < adj_words.size(); i++) {
	  string next_node = adj_words[i];
	  if(look_trans) {
		if(translated[node] || translated[next_node]) {
			if(translation.count(node) && next_node.compare(translation[node]) != 0)
				continue;
			else if(translation2.count(node) && next_node.compare(translation2[node]) != 0)
				continue;
			else if(translation.count(next_node) && node.compare(translation[next_node]) != 0) 
				continue;
			else if(translation2.count(next_node) && node.compare(translation2[next_node]) != 0)
				continue;
		}
	  }
	  if((!visited[next_node] && next_node_set.find(next_node) != next_node_set.end())
		|| (path.size() == 4 && path[0].compare(next_node) == 0)) {
	      path.push_back(next_node);
		visited[next_node] = true;
	      dfs2(g,next_node,visited,translation,translation2,translated,path);
	      if(path[0].compare(next_node) != 0)
		visited[next_node] = false;
	      path.pop_back();
	  }
    }

}


int main() {

  int n;
  bool first = true;
  while(cin >> n) {
    if(n == 0) {
      break;
    }
    else {
	if(first) {
	   first = false;
	}
	else {
	    cout << endl;
	}
    }
    
 
    vector<ss> l1(n);
    vector<ss> l2(n);
    map<string, int> first;
    map<string, int> second;
    
    for(int i = 0; i < n; i++) {
      string w1, w2;
      cin >> w1 >> w2;
      l1[i] = make_pair(w1,w2);
      first[w1]++;
      second[w2]++;
      s1.insert(w1);
      s1.insert(w2);
    }
    
    for(int i = 0; i < n; i++) {
      string w1, w2;
      cin >> w1 >> w2;
      l2[i] = make_pair(w1,w2);
      first[w1]++;
      second[w2]++;
      s2.insert(w1);
      s2.insert(w2);
    }
    
    graph g;
    
    for(int i = 0; i < l1.size(); i++) {
	ss p = l1[i];
	g[p.first].push_back(p.second);
    }
    
    for(int i = 0; i < l2.size(); i++) {
	ss p = l2[i];
	g[p.second].push_back(p.first);
    }

    map<string,string> translation;
    map<string,string> translation2;
    map<string,bool> translated;
    
    for(set<string>::iterator iter1 = s1.begin(); iter1 != s1.end(); iter1++) {
	  string w = *iter1;
	  int possible_translation = 0;
	  string trans = "";
	  for(set<string>::iterator iter2 = s2.begin(); iter2 != s2.end(); iter2++) {
	      string v = *iter2;
	      if(first[w] == first[v] && second[w] == second[v]) {
		 possible_translation++;
		 g[w].push_back(v);
		 g[v].push_back(w);
		 trans = v;
	      }
	  }
	  if(possible_translation == 1) {
		translation[w] = trans;
		translation2[trans] = w;
		translated[w] = true;
		translated[trans] = true;
	  }
    }
    

    map<string,bool> visited_trans;
    while(true) {
            bool every_word_translated = true;
	    for(set<string>::iterator iter1 = s1.begin(); iter1 != s1.end(); iter1++) {
		string w = *iter1;
		vector<string> path;
		path.push_back(w);
		if(translated[w] && !visited_trans[w]) {
		    map<string,bool> visited;
		    visited[w] = true;
		    dfs1(g,w,visited,translation,translation2,translated,path);
		    dfs2(g,w,visited,translation,translation2,translated,path);
		    visited_trans[w] = true;
		}
		every_word_translated = every_word_translated && translated[w];
	    }
	    if(every_word_translated)
		break;
    }
    
    for(map<string,string>::iterator trans = translation.begin(); trans != translation.end(); trans++) {
	cout << (*trans).first << "/" << (*trans).second << endl;
    }
    
    s1.clear();
    s2.clear();
    
    
  }
  
  return 0;

}

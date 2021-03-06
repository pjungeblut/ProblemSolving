#include <bits/stdc++.h>
#include <iostream>
#include <climits>

using namespace std;
#define NUM 30

class treeNode {
	public:
		treeNode(int v, int size) : v(v), size(size), p(nullptr), l(nullptr), r(nullptr) {}

		void print() {
			cout << "Value: " << v << ", Size: " << size << ", Left: " << (l ? l->v : -1) << 
				", Right: " << (r ? r->v : -1) << ", Parent: " << (p ? p->v : -1) << endl;
		}

		int v, size;
		treeNode* p; treeNode* l; treeNode* r;
};

class SearchTree {

	public:
		SearchTree(vector<int>& a) {
			build_tree(0,a.size()-1, nullptr, true, a);
		}

		treeNode* kth_element(int k) {
			if(k > root->size)
				return nullptr;
			return kth_element(root, k);	
		}

		void remove_element(treeNode *node) {
			remove(node);
		}

		vector<int> sorted_tree() {
			vector<int> a;
			for(int i = 1; i <= root->size; i++)
				a.push_back(kth_element(i)->v);
			return a;
		}
	
		int size() {
			return root->size;
		}

		void print_tree() {
			print_node(root);
		}

		void print_sorted_tree() {
			for(int i = 1; i <= size(); i++)
				cout << kth_element(i)->v << ", ";
			cout << endl;
		}

	private:
		
		void build_tree(int l, int r, treeNode* parent, bool left, vector<int>& a) {
			int m = (r+l)/2;
			int size = r-l+1;
			treeNode *new_node = new treeNode(a[m],size); new_node->p = parent;
			if(parent) {
				if(left)
					parent->l = new_node;
				else
					parent->r = new_node;
			}
			else
				root = new_node;
			if(m-1-l >= 0)
				build_tree(l,m-1,new_node,true,a);
			if(r-m-1 >= 0)
				build_tree(m+1,r,new_node,false,a);

		}

		treeNode* kth_element(treeNode *node, int k) {
			int lt_size = (node->l) ? node->l->size : 0;
			if(lt_size+1 == k) 
				return node;
		
			if(lt_size+1 < k)
				kth_element(node->r, k-lt_size-1);
			else
				kth_element(node->l, k);

		}

		bool remove(treeNode *node) {
			treeNode *parent = node->p;
			bool left = false;
			if(parent && parent->l == node) left = true;

			treeNode* dec = node->p;

			if((!node->r && node->l) || (node->r && !node->l)) {
				treeNode* child = (node->r) ? node->r : node->l;
				child->p = parent;
				if(parent) {
					if(left) parent->l = child;
					else parent->r = child;
				} else root = child;
				child->size = node->size-1;
				recursive_decrement_size(dec);
				delete node;
			} else if(node->r && node->l) {
				int z = rand() % 2;
				treeNode *swap_partner = z ? left_neighbour(node->l) : right_neighbour(node->r);
				swap(node, swap_partner);
				remove(node);
			} else {
				if(parent) {
					if(left) parent->l = nullptr;
					else parent->r = nullptr;
				} 
				recursive_decrement_size(dec);
				delete node;
			}
		}

		void swap(treeNode *node1, treeNode *node2) {
			treeNode *p = node1->p; treeNode *l = node1->l; treeNode *r = node1->r; int size = node1->size;

			if(node1 != node2->p) node1->p = node2->p;
			else node1->p = node2; 
			node1->l = node2->l; node1->r = node2->r; node1->size = node2->size;

			if(node1 != node2->p) {
				if(node2->p && node2->p->l == node2) node2->p->l = node1;
				else if(node2->p && node2->p->r == node2) node2->p->r = node1;
				else if(!node2->p) root = node1;
			}
			new_parent(node1,node2->l,node2->r);

			if(node1 != node2->p) {
				node2->l = l; node2->r = r; 
			}
			else {
				if(l == node2) node2->l = node1;
				else if(r == node2) node2->r = node1;
			}
			node2->p = p; node2->size = size;

			if(p && p->l == node1) p->l = node2;
			else if(p && p->r == node1) p->r = node2;
			else if(!p) root = node2;
			new_parent(node2,l,r);
		} 

		void new_parent(treeNode *p, treeNode *l, treeNode *r) {
			if(l && l != p) l->p = p;
			if(r && r != p) r->p = p;
		}

		void recursive_decrement_size(treeNode* node) {
			if(!node)
				return;
			node->size--;
			recursive_decrement_size(node->p);
		}

		treeNode* left_neighbour(treeNode* l) {
			return (l->r) ? left_neighbour(l->r) : l;
		}

		treeNode* right_neighbour(treeNode* r) {
			return (r->l) ? right_neighbour(r->l) : r;
		}

		void print_node(treeNode *node) {
			node->print();
			if(node->l)
				print_node(node->l);
			if(node->r)
				print_node(node->r);
		}

		treeNode *root;
		

};


int main() {

	vector<int> a;
	for(int i = 1; i < NUM; i+=2)
		a.push_back(i);
	SearchTree st(a);	
	//st.print_sorted_tree();
	vector<treeNode*> del;
	cout << st.size() << endl;
	for(int i = 3; i <= st.size(); i+=3)
		del.push_back(st.kth_element(i));
	
	for(treeNode* tn : del) {
		cout << tn->v << endl;
		st.remove_element(tn);	
		st.print_tree();
	}
	st.print_sorted_tree();


	return 0;
}

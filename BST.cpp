#include "BST.h"


void BST::del()
{
	Stack s;
	Elem* curr = root;
	while (true) {
		while (curr) {
			s.PUSH(curr);
			curr = curr->left;
		}
		if (!s.EMPTY()) {
			Elem *old = s.POP();
			curr = old->right;
			delete old;
		}
		else break;
	}
	root = nullptr;
	num = 0;
}

void BST::Write(ostream & it) const
{
	Stack s;
	if (!root) throw ErrEmpty();
	Set::Write(it);
	it << " Elements of the set: ";
	Elem* curr = root;
	while (true) {
		while (curr) {
			s.PUSH(curr);
			curr = curr->left;
		}
		if (!s.EMPTY()) {
			curr = s.POP();
			it << curr->key << ' ';
			curr = curr->right;
		}
		else break;
	}
}

void BST::Read(istream & ut)
{
	do {
		int c;
		ut >> c;
		try {
			Insert(c);
		}
		catch (ErrElExists g) {}
	} while (cin.get() != '\n');
}

BST::Elem * BST::Find(int x) const
{
	Elem* curr = root, *fath = nullptr;
	while (curr) {
		if (x == curr->key) return fath;
		fath = curr;
		if (x < curr->key) curr = curr->left;
		else curr = curr->right;
	}
	return fath;							
}

void BST::DeleteNode(Elem * fath, Elem* br)						//deleting a node whilst preserving the tree's formation 
{
	Elem* chng;
	if (!br->left) chng = br->right;
	else if (!br->right) chng = br->left;
	else {
		Elem* o = br;
		chng = br->right;
		Elem* next = chng->left;
		while (next) {
			o = chng;
			chng = next;
			next = next->left;
		}
		if (br != o) {
			o->left = chng->right;
			chng->right = br->right;
		}
		chng->left = br->left;
	}
	if (!fath) root = chng;
	else if (br == fath->left) fath->left = chng;
	else fath->right = chng;
	delete br;
	num--;
}

int BST::Min()
{
	Elem* curr = root;
	while (curr->left) {
		curr = curr->left;
	}
	return curr->key;
}

int BST::Max()
{
	Elem* curr = root;
	while (curr->right) {
		curr = curr->right;
	}
	return curr->key;
}

BST & BST::Remove(int x)												//deleting a node if its father is provided
{
	Elem* fath = Find(x);
	Elem* num=0;
	if (!fath && !root) throw ErrEmpty();
	if (!fath) num = root;
	else {
		if (x < fath->key) num = fath->left;
		if (x > fath->key) num = fath->right;
	}
	if (!num) throw ErrNoElement(x);
	DeleteNode(fath, num);
	return *this;
}

BST & BST::RemoveRange(int a, int b)									//based on the inorder algorithm for tree traversal
{
	if (a > b) throw ErrRange();
	if (!root) throw ErrEmpty();
	if (a > Max()) return *this;
	if (b < Min()) return *this;
	Stack s;
	Elem* curr, *fath = root, *br, *sp=nullptr; 
	if (b < root->key) {
		curr = root->left;
		s.PUSH(root);
	}
	else if (a > root->key) {
		curr = root->right;
		s.PUSH(root);
	}
	else {
		curr = root;
		fath = nullptr;
	}
	while (true) {
		while (curr) {
			s.PUSH(curr);
			curr = curr->left;
		}												
		if (!s.EMPTY() && s.TOP() <= b) {
			fath = s.Fath();
			curr = s.POP();
			if (curr->key >= a && curr->key <= b) {
				while (curr && curr->key >= a && curr->key <= b) {
					br = curr;
					if (sp && sp->right && sp->right->key == br->key) fath = sp;
					DeleteNode(fath, br);
					if (fath)
						if (fath->key > a) curr = fath->left;
						else curr = fath->right;
					else curr = root;
				}
			}
			else {
				if (curr->right && curr->right->key >= a) sp = curr;
				curr = curr->right;
			}
		}
		else break;
	}
	return *this;
}

BST * BST::Intersection(const BST & bst) const								//based on the inorder algorithm for tree traversal
{
	Stack s1, s2;
	Elem* curr1 = root, *curr2 = bst.root;
	BST* resTree=new BST();
	int cap = 50;
	int* arr = new int[cap];
	int* p;
	int low = 0, high, n = 0;
	bool nel1 = true, nel2 = true, exists = false;				
	while (true) {
		while (curr1 && nel1) {
			s1.PUSH(curr1);
			curr1 = curr1->left;
		}
		while (curr2 && nel2) {
			s2.PUSH(curr2);
			curr2 = curr2->left;
		}
		if ((!curr1 && s1.EMPTY()) || (!curr2 && s2.EMPTY())) break;		//as long as there are elements in any of the sets, they are compared and
		else {																//if they are equal, the number is inserted into a sorted array, from which a bst is
			if (nel1) curr1 = s1.POP();										//constructed later
			if (nel2) curr2 = s2.POP();										//if they are different, the travesal continues in the tree whose element was lesser
			if (curr1->key == curr2->key) {
				exists = true;
				if (n == cap) {
					cap += 50;
					p = new int[cap];
					for (int i = 0; i < n; i++) p[i] = arr[i];
					delete[] arr;
					arr = p;
				}
				arr[n++] = curr1->key;
				curr1 = curr1->right;
				curr2 = curr2->right;
				nel1 = true;
				nel2 = true;
			}
			else if (curr1->key < curr2->key) {
				curr1 = curr1->right;
				nel1 = true;
				nel2 = false;
			}
			else {
				curr2 = curr2->right;
				nel1 = false;
				nel2 = true;
			}
		}
	}
	if (exists) {														//making a balanced tree out of the resulting array
		int* s1 = new int[n], sb1 = 0;
		int* s2 = new int[n], sb2 = 0;
		s1[sb1++] = 0;
		s2[sb2++] = n - 1;
		do {
			low = s1[--sb1];
			high = s2[--sb2];
			if (low != high) {
				try {
					resTree->Insert(arr[low]);
				}
				catch (ErrElExists g) {}
				try {
					resTree->Insert(arr[high]);
				}
				catch (ErrElExists g) {}
				s1[sb1++] = (low + high) / 2 - 1;
				s2[sb2++] = (low + high) / 2 + 1;
			}
			else {
				try {
					resTree->Insert(arr[high]);
				}
				catch (ErrElExists g) {}
			}
		} while (sb1<0 && sb2<0);
		delete s1;
		delete s2;
	}
	return resTree;
}


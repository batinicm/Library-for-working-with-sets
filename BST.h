#ifndef _STABLO_
#define _STABLO_

#include "Set.h"
#include "Errs.h"

class BST: public Set{
private:
	struct Elem {
		int key;
		Elem * left, *right;
		Elem(int k, Elem* l=nullptr, Elem* r=nullptr): key(k), left(l), right(r){}
	};
	Elem* root=nullptr;

	void del();				
	void Write(ostream& it) const override;
	void Read(istream& ut) override;
	Elem* Find(int x) const;
	void DeleteNode(Elem* fath, Elem* br);
	int Min();
	int Max();

	friend class Stack;
public:
	BST(){}
	~BST() { del(); }
	BST(const BST& b) = delete;
	BST& operator=(const BST& b) = delete;
	bool Belongs(int x) const override {									
		Elem* fath = Find(x);
		if (fath) {
			if (fath->left && x == fath->left->key) return true;
			if (fath->right && x == fath->right->key) return true;
		}
		else if (x == root->key) return true;
		return false;														
	}
	BST& Insert(int x) override {
		Elem* fath = Find(x);
		if (fath) {
			if (fath->left && x == fath->left->key) throw ErrElExists(x);
			if (fath->right && x == fath->right->key) throw ErrElExists(x);
			if (x < fath->key) fath->left = new Elem(x);
			else fath->right = new Elem(x);
		}
		else
			if (root && x == root->key) throw new ErrElExists(x);
			else root = new Elem(x);
			num++;
		return *this;
	}
	BST& Remove(int x) override;
	BST& RemoveRange(int a, int b) override;
	BST* Intersection(const BST& bst) const;
	void DeleteAll() override { del(); }
};

class Stack {
private:
	struct Elem {
		BST::Elem* node;
		Elem* next;
		Elem(BST::Elem* p, Elem* s = nullptr) :node(p), next(s) {}
	};
	Elem* sp = nullptr;
public:
	Stack() {}
	~Stack();
	Stack(const Stack& s) = delete;
	Stack& operator=(const Stack& s) = delete;
	Stack& PUSH(BST::Elem * p) {
		Elem* nel = new Elem(p, sp);
		sp = nel;
		return *this;
	}
	BST::Elem* POP() {
		if (!sp) return nullptr;			
		BST::Elem* p = sp->node;
		Elem*old = sp;
		sp = sp->next;
		delete old;
		return p;
	}
	bool EMPTY() const {
		return sp == nullptr;
	}
	int TOP() const { 
		return sp->node->key; 
	}
	BST::Elem* Fath() const { 
		if(sp->next) return sp->next->node; 
		else return nullptr;
	}
};
#endif


#ifndef _STABLO_
#define _STABLO_

#include "Skup.h"
#include "Greske.h"

class BinStablo: public Skup{
private:
	struct Elem {
		int key;
		Elem * left, *right;
		Elem(int k, Elem* l=nullptr, Elem* r=nullptr): key(k), left(l), right(r){}
	};
	Elem* root=nullptr;

	void brisi();				
	void Pisi(ostream& it) const override;
	void Citaj(istream& ut) override;
	Elem* Nadji(int x) const;
	void BrisanjeCv(Elem* fath, Elem* br);
	int Min();
	int Max();

	friend class Stek;
public:
	BinStablo(){}
	~BinStablo() { brisi(); }
	BinStablo(const BinStablo& b) = delete;
	BinStablo& operator=(const BinStablo& b) = delete;
	bool Pripada(int x) const override {									//pogledaj da li se negde koristi u metodama ovde i u listi- ako ne, mozda da bude void pa da ispisuje
		Elem* fath = Nadji(x);
		if (fath->left && x == fath->left->key) return true;				//mnogo pazi na ovo dereferenciranje nulla
		if (fath->right && x == fath->right->key) return true;
		return false;														//ne zaboravi da u mainu kada ispitujemo pripadnost vratis odgovarajucu poruku
	}
	BinStablo& Ubaci(int x) override {
		Elem* fath = Nadji(x);
		if (fath) {
			if (fath->left && x == fath->left->key) throw Grpostoji(x);
			if (fath->right && x == fath->right->key) throw Grpostoji(x);
			if (x < fath->key) fath->left = new Elem(x);
			else fath->right = new Elem(x);
		}
		else root = new Elem(x);
		return *this;
	}
	BinStablo& Izbaci(int x) override;
	BinStablo& BrisiOpseg(int a, int b) override;
	BinStablo* Presek(const BinStablo& bst) const;
	void BrisiSve() override { brisi(); }
};

class Stek {
private:
	struct Elem {
		BinStablo::Elem* cv;
		Elem* sled;
		Elem(BinStablo::Elem* p, Elem* s = nullptr) :cv(p), sled(s) {}
	};
	Elem* sp = nullptr;
public:
	Stek() {}
	~Stek();
	Stek(const Stek& s) = delete;
	Stek& operator=(const Stek& s) = delete;
	Stek& PUSH(BinStablo::Elem * p) {
		Elem* novi = new Elem(p, sp);
		sp = novi;
		return *this;
	}
	BinStablo::Elem* POP() {
		if (!sp) return nullptr;			//ili neku klasu greske, ali kontrolisemo ovo tako da ni nije potrebno > ?
		BinStablo::Elem* p = sp->cv;
		Elem*stari = sp;
		sp = sp->sled;
		delete stari;
		return p;
	}
	bool EMPTY() const {
		return sp == nullptr || sp->cv == nullptr;
	}
	int TOP() const { 
		return sp->cv->key; 
	}
	BinStablo::Elem* Otac() const { 
		if(sp->sled) return sp->sled->cv; 
		else return nullptr;
	}
};
#endif


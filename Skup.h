#ifndef _SKUP_
#define _SKUP_

#include <iostream>
using namespace std;

class Skup {
protected:								//da li da bude private ili protected?
	int br;
public:
	Skup() { br = 0; }
	virtual ~Skup(){}
	virtual bool Pripada(int x) const = 0; 
	virtual Skup& Ubaci(int x) = 0;
	virtual Skup& Izbaci(int x) = 0;
	virtual Skup& BrisiOpseg(int a, int b) = 0;
	int BrEl()const { return br; }
	virtual void BrisiSve() = 0;
protected:
	virtual void Pisi(ostream& it) const { it << "Broj elemenata skupa: "<<br<<' '; }
	friend ostream& operator<<(ostream& it, const Skup& s) {
		s.Pisi(it);
		return it;
	}
	virtual void Citaj(istream& ut) = 0;
	friend istream& operator >> (istream& ut, Skup& s) {
		s.Citaj(ut);
		return ut;
	}
};

#endif

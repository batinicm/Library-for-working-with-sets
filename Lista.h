#ifndef _LISTA_
#define _LISTA_

#include "Skup.h"

class Lista : public Skup {
private:
	struct Elem {
		int key;
		struct Elem* sled;
		Elem(int k, Elem*s=nullptr): key(k),sled(s){}
	};
	Elem* prvi = nullptr, *posl = nullptr;
	void brisi();
	void Citaj(istream& ut) override;
	void Pisi(ostream& it) const override;
public:
	Lista(){}					//stvara praznu listu;
	Lista(const Lista& l) = delete;
	Lista& operator=(const Lista& l) = delete;
	~Lista() { brisi(); }
	bool Pripada(int x) const override; 
	Lista& Ubaci(int x) override;
	Lista& Izbaci(int x) override;
	Lista* Presek(const Lista& s) const;				//ne zaboravi da ti presek nije virtuelna metoda
	Lista& BrisiOpseg(int a, int b) override;
	void BrisiSve() override { brisi(); }
};

#endif

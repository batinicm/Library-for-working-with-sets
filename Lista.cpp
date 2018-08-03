#include "Lista.h"
#include "Greske.h"

void Lista::brisi(){
	while (prvi) {
		Elem *stari = prvi;
		prvi = prvi->sled;
		delete stari;
	}
	prvi = posl = nullptr;
	br = 0;
}

void Lista::Citaj(istream & ut){
		do {
			int b;
			ut >> b;
			Ubaci(b);
		} while (cin.get() != '\n');
}

void Lista::Pisi(ostream & it) const {
	if (!prvi) throw Grprazno();
	Skup::Pisi(it);
	it << "Elementi skupa: ";
	Elem* tek = prvi;
	while (tek) {
		it << tek->key;
		if (tek->sled) it << ' ';
		else it << endl;
		tek = tek->sled;
	}
}

Lista & Lista::Ubaci(int x){
	Elem* tek = prvi, *pret = nullptr;
	while (tek && tek->key < x) {
		pret = tek;
		tek = tek->sled;
	}
	if (tek && tek->key == x) throw Grpostoji(x);				//pazi da ga uhvatis u glavnom prog
	Elem *novi = new Elem(x, tek);						//pazi da uhvatis bad_alloc
	if (!pret) prvi = novi;
	else pret->sled = novi;
	if (!tek) posl = novi;
	br++;
	return *this;
}

Lista & Lista::Izbaci(int x)
{
	if (!prvi) throw Grprazno();
	Elem* tek =prvi , *pret = nullptr;
	while (tek && tek->key != x) {
		pret = tek;
		tek = tek->sled;
	}
	if (!tek) throw Grnepostoji(x);
	if (tek == prvi) prvi = tek->sled;
	else pret->sled = tek->sled;
	if (tek == posl) posl = pret;
	delete tek;
	br--;
	return *this;
}

Lista * Lista::Presek(const Lista & s) const
{
	Elem* p1 = prvi, *p2 = s.prvi;
	Lista *novi = new Lista;
	while (p1 != nullptr && p2 != nullptr) {
		if (p1->key == p2->key) {
			novi->Ubaci(p1->key);
			p1 = p1->sled;
			p2 = p2->sled;
		}
		else if (p1->key < p2->key) p1 = p1->sled;
		else p2 = p2->sled;
	}
	return novi;
}

bool Lista::Pripada(int x) const
{
	if (!prvi) throw Grprazno();
	Elem * tek = prvi;
	while (tek && tek->key != x) tek = tek->sled;
	if (!tek) return false;
	return true;
}

Lista & Lista::BrisiOpseg(int a, int b)
{
	if (!prvi) throw Grprazno();
	if (a>b) throw Gropseg();
	Elem* tek = prvi, *pret = nullptr;
	while (tek->key < a) { 
		pret = tek;
		tek = tek->sled; 
	}
	while (tek && (tek->key >= a && tek->key <= b)) {
		if (tek == prvi) prvi = tek->sled;
		else pret->sled = tek->sled;
		if (tek == posl) posl = pret;
		Elem *sl = tek->sled;
		delete tek;
		tek = sl;
	}
	return *this;
}

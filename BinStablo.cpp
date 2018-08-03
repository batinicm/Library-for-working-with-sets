#include "BinStablo.h"


void BinStablo::brisi()
{
	Stek s;
	Elem* tek = root;
	while (true) {
		while (tek) {
			s.PUSH(tek);
			tek = tek->left;
		}
		if (!s.EMPTY()) {
			Elem *stari = s.POP();
			tek = stari->right;
			delete stari;
		}
		else break;
	}
	root = nullptr;
}

void BinStablo::Pisi(ostream & it) const
{
	Stek s;
	Elem* tek = root;
	while (true) {
		while (tek) {
			s.PUSH(tek);
			tek = tek->left;
		}
		if (!s.EMPTY()) {
			tek = s.POP();
			it << tek->key << ' ';
			tek = tek->right;
		}
		else break;
	}
}

void BinStablo::Citaj(istream & ut)
{
	do {
		int c;
		ut >> c;
		Ubaci(c);
	} while (cin.get() != '\n');
}

BinStablo::Elem * BinStablo::Nadji(int x) const
{
	Elem* tek = root, *fath = nullptr;
	while (tek) {
		if (x == tek->key) return fath;
		fath = tek;
		if (x < tek->key) tek = tek->left;
		else tek = tek->right;
	}
	return fath;							//pomocna funkcija kojom nadjem oca cvora koji mi treba
}

void BinStablo::BrisanjeCv(Elem * fath, Elem* br)
{
	Elem* zam;
	if (!br->left) zam = br->right;
	else if (!br->right) zam = br->left;
	else {
		Elem* o = br;
		zam = br->right;
		Elem* sl = zam->left;
		while (sl) {
			o = zam;
			zam = sl;
			sl = sl->left;
		}
		if (br != o) {
			o->left = zam->right;
			zam->right = br->right;
		}
		zam->left = br->left;
	}
	if (!fath) root = zam;
	else if (br == fath->left) fath->left = zam;
	else fath->right = zam;
	delete br;
}

int BinStablo::Min()
{
	Elem* tek = root;
	while (tek->left) {
		tek = tek->left;
	}
	return tek->key;
}

int BinStablo::Max()
{
	Elem* tek = root;
	while (tek->right) {
		tek = tek->right;
	}
	return tek->key;
}

BinStablo & BinStablo::Izbaci(int x)					//sustinski brisanje cvora ako mu dam oca tog cvora
{
	Elem* fath = Nadji(x);
	Elem* br;
	if (!fath && !root) throw Grprazno();
	if (!fath) br = root;
	else {
		if (x < fath->key) br = fath->left;
		if (x > fath->key) br = fath->right;
	}
	if (!br) throw Grnepostoji(x);
	BrisanjeCv(fath, br);
	return *this;
}

BinStablo & BinStablo::BrisiOpseg(int a, int b)					
{
	if (a > b) throw Gropseg();
	if (!root) throw Grprazno();
	if (a > Max()) return *this;
	if (b < Min()) return *this;
	Stek s;
	Elem* tek, *fath = root, *br; 
	if (b < root->key) tek = root->left;
	else if (a > root->key) tek = root->right;
	else {
		tek = root;
		fath = nullptr;
	}
	while (tek && tek->key < a) {
		fath = tek;
		tek = tek->right;
	}
	while (true) {
		while (tek && tek->key>=a && tek->key<=b) {
			s.PUSH(fath);
			fath = tek;
			tek = tek->left;
		}												//father od cvora koji mi treba je pre njega na steku
		if (!s.EMPTY() && s.TOP()<=b) {
			fath = s.Otac();
			tek = s.POP();
			while (tek && tek->key >= a && tek->key <= b) {
				br = tek;
				BrisanjeCv(fath, br);
				if (fath)
					if (fath->key > a) tek = fath->left;
					else tek = fath->right;
				else tek = root;
			}
		}
		else break;
	}
	return *this;
}

BinStablo * BinStablo::Presek(const BinStablo & bst) const
{
	if (!root || !bst.root) throw Grpresek();
	Stek s1, s2;
	Elem* tek1 = root, *tek2 = bst.root;
	BinStablo* rez=new BinStablo();
	int kap = 50;
	int* niz = new int[kap];
	int* pom;
	int low = 0, high, mid, n = 0;
	bool novi1 = true, novi2 = true, ima = false;				//oznacavaju da li treba da guram na stek njegove leve potomke- ne treba ako nije novi cvor
	while (true) {
		while (tek1 && novi1) {
			s1.PUSH(tek1);
			tek1 = tek1->left;
		}
		while (tek2 && novi2) {
			s2.PUSH(tek2);
			tek2 = tek2->left;
		}
		if ((!tek1 && s1.EMPTY()) || (!tek2 && s2.EMPTY())) break;		//zavrsava se onda kada mi je tek null i stek je prazan-tada se jedno od stabala zavrsilo i nemam sta vise da uporedjujem
		else {
			if (novi1) tek1 = s1.POP();
			if (novi2) tek2 = s2.POP();
			if (tek1->key == tek2->key) {
				ima = true;
				if (n == kap) {
					kap += 50;
					pom = new int[kap];
					for (int i = 0; i < n; i++) pom[i] = niz[i];
					delete[] niz;
					niz = pom;
				}
				niz[n++] = tek1->key;
				tek1 = tek1->right;
				tek2 = tek2->right;
				novi1 = true;
				novi2 = true;
			}
			else if (tek1->key < tek2->key) {
				tek1 = tek1->right;
				novi1 = true;
				novi2 = false;
			}
			else {
				tek2 = tek2->right;
				novi1 = false;
				novi2 = true;
			}
		}
	}
	if (ima) {
		high = n - 1;
		mid = (low + high) / 2;
		rez->Ubaci(niz[mid]);
		if (!((low + high) % 2)) rez->Ubaci(niz[mid + 1]);
		while (high > mid && low < mid) {
			try {													//stavljeno u try iako ne mora-skupovi ce sigurno imati samo 1 primerak svakog elementa
				rez->Ubaci(niz[low]);
			} catch(Grpostoji &g){}
			try {
				rez->Ubaci(niz[high]);
			} catch (Grpostoji &g){}
				high--;
				low++;
		}
	}
	return rez;
}


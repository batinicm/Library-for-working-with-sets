#include "Skup.h"
#include "Lista.h"
#include "BinStablo.h"
#include "Greske.h"
#include "PerformanceCalculator.h"
#include <iomanip>
#include <string>


double* Formiranje(Lista * l, Lista* lpom, BinStablo* b, BinStablo *bpom, int tr) {
	PerformanceCalculator pc;
	double* avg = new double[2];
	avg[0] = 0; avg[1] = 0;
	int* niz = new int[tr];
	for (int k = 0; k < 3; k++) {
	for(int i=0; i<tr; i++) niz[i]= (tr + 100)*rand() / ((double)RAND_MAX);
		pc.start();
		for (int j = 0; j<tr; j++) {
			try {
				l->Ubaci(niz[j]);									
			}
			catch (Grpostoji g) {}
		}
		pc.stop();
		avg[0] += pc.elapsedMillis();
		if (k == 1) {
			lpom = l;
			l->BrisiSve();
		}
		else if (k != 2) l->BrisiSve();									//ne treba mi da ga obrise, vec da ga isprazni
		pc.start();
		for (int j = 0; j<tr; j++) {
			try {
				b->Ubaci(niz[j]);
			}
			catch (Grpostoji g) {}
		}
		pc.stop();
		avg[1] += pc.elapsedMillis();
		if (k == 1) {
			bpom = b;
			b->BrisiSve();
		}
		else if (k != 2) b->BrisiSve();
	}
	delete niz;
	avg[0] /= 3;
	avg[1] /= 3;
	return avg;
}

double Ubacivanje(Skup* s, int a) {
	PerformanceCalculator pc;
	double avg1 = 0;
	for (int k = 0; k < 3; k++) {
		pc.start();
		try {
			s->Ubaci(a);
		}
		catch (Grpostoji g) {}
		pc.stop();
		avg1 += pc.elapsedMillis();
	}
	return avg1/3;
}

double Izbacivanje(Skup* s, int a) {
	PerformanceCalculator pc;
	double avg1 = 0;
	for (int k = 0; k < 3; k++) {
		pc.start();
		try {
			s->Izbaci(a);
		}
		catch (Grnepostoji g) {}
		pc.stop();
		avg1 += pc.elapsedMillis();
	}
	return avg1 / 3;
}

double Pripadnost(Skup* s, int a) {
	PerformanceCalculator pc;
	double avg1 = 0;
	for (int k = 0; k < 3; k++) {
		pc.start();
		try {
			s->Pripada(a);
		}
		catch (Grnepostoji g) {}
		pc.stop();
		avg1 += pc.elapsedMillis();
	}
	return avg1 / 3;
}

void Ispis(ostream& it, double* niz) {
	for (int k = 0; k < 6; k++) {
		it << setprecision(3)<< setw(6) << niz[k]<<' ';
		if (k == 5) it << endl;
	}
}

void Peformanse() {										//stavka u meniju pre izbora bilo kakve reprezentacije: izmeri performanse obe reprezentacije skupa

	int vr[] = { 200,500,1000,10000,100000,1000000 };
	int gr[] = {150,400,850,9000,98000,999500};
	double forml[6], umetl[6], brisl[6], pretl[6], presl[6];			//nizovi vrednosti za listu
	double forms[6], umets[6], briss[6], prets[6], press[6];			//nizovi vrednosti za stablo
	PerformanceCalculator pc;

	for (int i = 0; i < 6; i++) {
		Lista *l = new Lista(), *lpom;
		BinStablo *b = new BinStablo(), *bpom;
		double* avg;
		double avg1 = 0;
		avg = Formiranje(l, lpom, b, bpom, vr[i]);
		forml[i] = avg[0];
		forms[i] = avg[1];	
		delete avg;
		int a = gr[i]*rand() / ((double)RAND_MAX);						//kako bismo ubacivali isti broj u obe reprezentacije-sto je i poenta
		avg1 = Ubacivanje(l, a);
		umetl[i] = avg1; 
		avg1 = Ubacivanje(b, a);
		umets[i] = avg1;
		a = gr[i] * rand() / ((double)RAND_MAX);
		avg1 = Izbacivanje(l, a);
		brisl[i] = avg1;
		avg1 = Izbacivanje(b, a);
		briss[i] = avg1;
		a = gr[i] * rand() / ((double)RAND_MAX);
		avg1 = Pripadnost(l, a);
		pretl[i] = avg1;
		avg1 = Pripadnost(b, a);
		prets[i] = avg1;
		avg1 = 0;
		for (int k = 0; k < 3; k++) {
			pc.start();
			l->Presek(*lpom);									// da li mi treba try?
			pc.stop();
			avg1 += pc.elapsedMillis();
		}
		presl[i] = avg1/3;
		avg1 = 0;
		for (int k = 0; k < 3; k++) {
			pc.start();
			b->Presek(*bpom);									
			pc.stop();
			avg1 += pc.elapsedMillis();
		}
		press[i] = avg1/3;
		delete l;
		delete lpom;
		delete b;
		delete bpom;
	}
	string titles[] = { "Velicina skupa","formiranje","umetanje","brisanje","pretraga","skupovna operacija" };
	for (int k = 0; k < 6; k++) {							//ispis performansi liste
		cout << setw(15) << titles[k] << ' ';
		switch (k) {
		case 0: for (int k = 0; k < 6; k++) {
			cout << vr[k] << setw(6);
			if (k == 5) cout << endl;
		} 
				break;
		case 1: Ispis(cout, forml); break;
		case 2: Ispis(cout, umetl); break;
		case 3: Ispis(cout, brisl); break;
		case 4: Ispis(cout, pretl); break;
		case 5: Ispis(cout, presl); break;
		default: break;
		}
	}
	for (int k = 0; k < 6; k++) {							//ispis performansi stabla
		cout << setw(15) << titles[k] << ' ';
		switch (k) {
		case 0: for (int k = 0; k < 6; k++) {
			cout << vr[k] << setw(6);
			if (k == 5) cout << endl;
		}
				break;
		case 1: Ispis(cout, forms); break;
		case 2: Ispis(cout, umets); break;
		case 3: Ispis(cout, briss); break;
		case 4: Ispis(cout, prets); break;
		case 5: Ispis(cout, press); break;
		default: break;
		}
	}
}
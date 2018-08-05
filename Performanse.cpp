#include "Set.h"
#include "List.h"
#include "BST.h"
#include "Errs.h"
#include "PerformanceCalculator.h"
#include <iomanip>
#include <string>


double* Formation(List * l, List* lpom, BST* b, BST *bpom, int tr) {						//formation of a list and bst made up of same numbers so that
	PerformanceCalculator pc;																//the performance measurements are accurate
	double* avg = new double[2];
	avg[0] = 0; avg[1] = 0;
	int* arr = new int[tr];
	for (int k = 0; k < 3; k++) {
	for(int i=0; i<tr; i++) arr[i]= (tr + 100)*rand() / ((double)RAND_MAX);
		pc.start();
		for (int j = 0; j<tr; j++) {
			try {
				l->Insert(arr[j]);									
			}
			catch (ErrElExists g) {}
		}
		pc.stop();
		avg[0] += pc.elapsedMillis();
		if (k == 1) {
			lpom = l;
			l->DeleteAll();
		}
		else if (k != 2) l->DeleteAll();									
		pc.start();
		for (int j = 0; j<tr; j++) {
			try {
				b->Insert(arr[j]);
			}
			catch (ErrElExists g) {}
		}
		pc.stop();
		avg[1] += pc.elapsedMillis();
		if (k == 1) {
			bpom = b;
			b->DeleteAll();
		}
		else if (k != 2) b->DeleteAll();
	}
	delete arr;
	avg[0] /= 3;
	avg[1] /= 3;
	return avg;
}

double Insertion(Set* s, int a) {
	PerformanceCalculator pc;
	double avg1 = 0;
	for (int k = 0; k < 3; k++) {
		pc.start();
		try {
			s->Insert(a);
		}
		catch (ErrElExists g) {}
		pc.stop();
		avg1 += pc.elapsedMillis();
	}
	return avg1/3;
}

double Removal(Set* s, int a) {
	PerformanceCalculator pc;
	double avg1 = 0;
	for (int k = 0; k < 3; k++) {
		pc.start();
		try {
			s->Remove(a);
		}
		catch (ErrNoElement g) {}
		pc.stop();
		avg1 += pc.elapsedMillis();
	}
	return avg1 / 3;
}

double Membership(Set* s, int a) {
	PerformanceCalculator pc;
	double avg1 = 0;
	for (int k = 0; k < 3; k++) {
		pc.start();
		try {
			s->Belongs(a);
		}
		catch (ErrNoElement g) {}
		pc.stop();
		avg1 += pc.elapsedMillis();
	}
	return avg1 / 3;
}

void WriteAll(ostream& it, double* arr) {
	for (int k = 0; k < 6; k++) {
		it << setprecision(3)<< setw(6) << arr[k]<<' ';
		if (k == 5) it << endl;
	}
}

void Performances() {										

	int vr[] = { 200,500,1000,10000,100000,1000000 };
	int gr[] = {150,400,850,9000,98000,999500};
	double forml[6], insl[6], reml[6], searchl[6], interl[6];			//arrays of results for individual samples -- linked list
	double formt[6], inst[6], remt[6], searcht[6], intert[6];			//arrays of results for individual samples -- BST
	PerformanceCalculator pc;

	for (int i = 0; i < 6; i++) {
		List *l = new List(), *lpom=0;
		BST *b = new BST(), *bpom=0;
		double* avg;
		double avg1 = 0;
		avg = Formation(l, lpom, b, bpom, vr[i]);
		forml[i] = avg[0];
		formt[i] = avg[1];	
		delete avg;
		int a = gr[i]*rand() / ((double)RAND_MAX);						//the same number is inserted in both representations
		avg1 = Insertion(l, a);
		insl[i] = avg1; 
		avg1 = Insertion(b, a);
		inst[i] = avg1;
		a = gr[i] * rand() / ((double)RAND_MAX);
		avg1 = Removal(l, a);
		reml[i] = avg1;
		avg1 = Removal(b, a);
		remt[i] = avg1;
		a = gr[i] * rand() / ((double)RAND_MAX);
		avg1 = Membership(l, a);
		searchl[i] = avg1;
		avg1 = Membership(b, a);
		searcht[i] = avg1;
		avg1 = 0;
		for (int k = 0; k < 3; k++) {
			pc.start();
			l->Intersection(*lpom);									
			pc.stop();
			avg1 += pc.elapsedMillis();
		}
		interl[i] = avg1/3;
		avg1 = 0;
		for (int k = 0; k < 3; k++) {
			pc.start();
			b->Intersection(*bpom);									
			pc.stop();
			avg1 += pc.elapsedMillis();
		}
		intert[i] = avg1/3;
		delete l;
		delete lpom;
		delete b;
		delete bpom;
	}
	string titles[] = { "Number of elements","formation","insertion","removal","search","set operation" };
	for (int k = 0; k < 6; k++) {							//list performance print
		cout << setw(15) << titles[k] << ' ';
		switch (k) {
		case 0: for (int k = 0; k < 6; k++) {
			cout << vr[k] << setw(6);
			if (k == 5) cout << endl;
		} 
				break;
		case 1: WriteAll(cout, forml); break;
		case 2: WriteAll(cout, insl); break;
		case 3: WriteAll(cout, reml); break;
		case 4: WriteAll(cout, searchl); break;
		case 5: WriteAll(cout, interl); break;
		default: break;
		}
	}
	for (int k = 0; k < 6; k++) {							//bst performance print
		cout << setw(15) << titles[k] << ' ';
		switch (k) {
		case 0: for (int k = 0; k < 6; k++) {
			cout << vr[k] << setw(6);
			if (k == 5) cout << endl;
		}
				break;
		case 1: WriteAll(cout, formt); break;
		case 2: WriteAll(cout, inst); break;
		case 3: WriteAll(cout, remt); break;
		case 4: WriteAll(cout, searcht); break;
		case 5: WriteAll(cout, intert); break;
		default: break;
		}
	}
}
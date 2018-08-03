#include <iostream>
#include <string>
#include "Greske.h"
#include "Lista.h"
#include "Skup.h"
#include "BinStablo.h"

int main() {
	BinStablo b1, b2;

	while (true) {
		try {
			cout << "Elementi prvog skupa? ";
			cin >> b1;
			cout << "Opseg elemenata koji zelite da obrisete iz skupa 1: ";
			int x, y; cin >> x >> y;
			cout << "Rezultujuci skup: " << b1.BrisiOpseg(x, y) << endl;;
			cout << "Elementi drugog skupa? ";
			cin >> b2;
			BinStablo* b3 = b1.Presek(b2);
			cout << "Presek:" << *b3 << endl;
			cout << "Koji element zelite da izbacite iz skupa 1? ";
			cin >> x;
			cout<<b1.Izbaci(x);
			cout << "Koji element zelite da izbacite iz skupa 2? ";
			cin >> y;
			cout<<b2.Izbaci(y);
			cout << "Koji element zelite da ubacite u skup 2?";
			cin >> x;
			cout<<b2.Ubaci(x);
		}
		catch (Grpostoji&g) { cout << g;}
		catch (Grnepostoji&g) { cout << g; }
		catch (Gropseg&g) { cout << g; }
		catch (Grprazno&g) { cout << g; }
		catch (Grpresek&g) { cout << g; }
		catch (bad_alloc) { cout << "Nema vise mesta!"<<endl; } 
		string pom;
		getline(cin, pom);
	}
}
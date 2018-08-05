#include <iostream>
#include <string>
#include "Errs.h"
#include "List.h"
#include "Set.h"
#include "BST.h"
#include <fstream>

void Performances();

int main() {
	Set** arr = new Set*[10];
	int n = 0, x, y, ch, z;
	List *l;
	BST* b;
	bool rad = true;
	ifstream fajl;
	string name;

	while (true) {
		cout << " Possible representations of the set: " << endl
			<< " 1. Singly linked sorted list " << endl
			<< " 2. Binary search tree " << endl
			<< " 3. Simultanious performance testing " << endl;
		cout << " Your choice? ";
		int chc; cin >> chc;
		cout << endl;
		switch (chc) {
		case 1: cout << "*** Active representation: linked list ***" << endl << endl;
			for (int i = 0; i < 10; i++) arr[i] = new List();
			break;
		case 2:  cout << "*** Active representation: BST ***" << endl << endl;
			for (int i = 0; i < 10; i++) arr[i] = new BST();
			break;
		case 3: Performances(); getline(cin, name); continue; break;
		default: cout << " Invalid choice! Try again: " << endl;
			cout << endl; continue; break;
		}
		rad = true;
		while (rad) {
			cout << endl;
			cout << " Select an operation: " << endl
				<< " 1. Set formation " << endl
				<< " 2. Element insertion " << endl
				<< " 3. Element deletion " << endl
				<< " 4. Set membership validation " << endl
				<< " 5. Set intersection " << endl
				<< " 6. Array of sets print " << endl
				<< " 0. Quit current representation " << endl;
			cout << " Your choice: ";
			cin >> ch;
			cout << endl;
			switch (ch) {
			case 0: rad = false;
				for (int i = 0; i < 10; i++) delete arr[i];
				break;
			case 1:
				if (n == 10) {
					cout << " The array of sets is full, choose a different operation \n\n";
					continue;
				}
				cout << " Type the serial number of the set you wish to form: ";
				cin >> y;
				if (y > 10 || y < 1) {
					cout << " A set with that number is non-existent; enter a number between 1 and 10  : ";
					cin >> y;
				}
				if (arr[y - 1]->NumOfEls() != 0) {
					cout << " Set already formed!\n\n";
					continue;
				}
				cout << " Select a set formation source: " << endl
					<< " 1. File " << endl
					<< " 2. Standard input " << endl;
				cout << " Your choice: ";
				cin >> z;
				switch (z) {
				case 1:
					cout << " Enter the name of your file: ";
					cin >> name;
					fajl.open(name);
					try {
						if (!fajl.is_open()) throw ErrFile();
					}
					catch (ErrFile g) { cout << g << endl; continue; }
					do {
						fajl >> x;
						char c = fajl.get();
						if (c != ' ' && c != '\n' && !fajl.eof()) {
							cout << " Nonvalid file!" << endl << endl;
							arr[y - 1]->DeleteAll();
							break;
						}
						try {
							arr[y - 1]->Insert(x);
						}
						catch (ErrElExists g) {}
					} while (!fajl.eof());
					fajl.close();
					break;
				case 2: cout << " Enter the serial number of a set: ";
					cin >> *arr[y - 1];
					break;
				default: cout << " Invalid choice!" << endl << endl;
				}
				if (arr[y - 1]->NumOfEls() != 0) {
					n++;
					cout << " Entered set: " << *arr[y - 1] << endl;
					cout << " It is now the " << y << ". set in the array of formed sets " << endl << endl;
				}
				break;
			case 2: cout << " Which set do you wish to work with? ";
				cin >> y;
				if (y > 10 || y < 1) {
					cout << " A set with that number is non-existent; enter a number between 1 and 10  : ";
					cin >> y;
				}
				if (arr[y - 1]->NumOfEls() == 0) n++;
				cout << " Enter the element of the set: ";
				cin >> x;
				try {
					arr[y - 1]->Insert(x);
					cout << " Set " << y << " : " << *arr[y - 1] << endl << endl;
				}
				catch (ErrElExists g) { cout << g << endl; }
				break;
			case 3:
				if (n == 0) {
					cout << " No set is yet formed!\n\n";
					continue;
				}
				cout << " Which set do you wish to work with? ";
				cin >> y;
				if (y > 10 || y < 1) {
					cout << " A set with that number is non-existent; enter a number between 1 and 10 : ";
					cin >> y;
				}
				if (arr[y - 1]->NumOfEls() == 0) {
					cout << ErrEmpty() << endl;
					continue;
				}
				cout << endl;
				cout << " Select what you wish to remove from the set " << endl;
				cout << " 1. An element " << endl
					<< " 2. A range " << endl;
				cout << " Your choice: ";
				cin >> z;
				switch (z) {
				case 1:
					cout << " Enter the element: ";
					cin >> x;
					try {
						arr[y - 1]->Remove(x);
						cout << " Set " << y << ": " << *arr[y - 1] << endl << endl;
					}
					catch (ErrNoElement g) { cout << g << endl; }
					break;
				case 2:
					cout << " Insert the range you wish to delete: ";
					int m, p; cin >> p >> m;
					try {
						arr[y - 1]->RemoveRange(p, m);
						cout << " Set " << y << ": " << *arr[y - 1] << endl << endl;
					}
					catch (ErrRange g) { cout << g << endl; }
					break;
				default: cout << " Invalid choice! " << endl; break;
				}
				break;
			case 4:
				if (n == 0) {
					cout << " No set was formed!\n\n";
					continue;
				}
				cout << " Which set do you wish to work with? ";
				cin >> y;
				if (y > 10 || y < 1) {
					cout << " A set with that number is non-existent; enter a number between 1 and 10 : ";
					cin >> y;
				}
				cout << " The number: ";
				cin >> x;
				cout << endl;
				try {
					bool da;
					da = arr[y - 1]->Belongs(x);
					if (da) cout << " The number is an element of the set. \n\n";
					else cout << " The number is not an element of the set. \n\n";
				}
				catch (ErrNoElement g) { cout << g << endl; }
				catch (ErrEmpty g) { cout << g << endl; }
				break;
			case 5:
				if (n == 0) {
					cout << " No set was formed!\n\n";
					continue;
				}
				cout << " The sets you wish to work with? ";
				cin >> x >> y;
				if (x < 1 || x>10 || y < 1 || y>10) {
					cout << " The set numbers are invalid \n\n";
					continue;
				}
				int i;
				for (i = 0; i < 10; i++) if (arr[i]->NumOfEls() == 0) break;
				if (i == 10) cout << " There is no space for the resulting set \n";
				if (chc == 1) {
					List* l1 = (List*)arr[x - 1];
					List* l2 = (List*)arr[y - 1];
					l = l1->Intersection(*l2);
					if (i != 10) arr[i] = l;
					cout << *l << endl;
				}
				else {
					BST* b1 = (BST*)arr[x - 1];
					BST* b2 = (BST*)arr[y - 1];
					b = b1->Intersection(*b2);
					cout << " The intersection of selected sets: " << *b << endl;
					if (i != 10) {
						arr[i] = b;
						cout << " The resulting set is " << (i + 1) << ". set in the array " << endl;
					}
				}
				cout << endl;
				break;
			case 6: cout << " The array of sets: " << endl;
				for (int i = 0; i < 10; i++) cout << *arr[i] << endl;
				break;
			default: cout << " Invalid choice!\n\n"; break;
			}
		}
	}
}
#include "List.h"
#include "Errs.h"

void List::del(){
	while (head) {
		Elem *old = head;
		head = head->next;
		delete old;
	}
	head = tail = nullptr;
	num = 0;
}

void List::Read(istream & ut){
		do {
			int b;
			ut >> b;
			try{
				Insert(b);
			}
			catch (ErrElExists g) {}
		} while (cin.get() != '\n');
}

void List::Write(ostream & it) const {
	if (!head) throw ErrEmpty();
	Set::Write(it);
	it << "Elements of the set: ";
	Elem* curr = head;
	while (curr) {
		it << curr->key;
		if (curr->next) it << ' ';
		else it << endl;
		curr = curr->next;
	}
}

List & List::Insert(int x){
	Elem* curr = head, *prev = nullptr;
	while (curr && curr->key < x) {
		prev = curr;
		curr = curr->next;
	}
	if (curr && curr->key == x) throw ErrElExists(x);				
	Elem *nel = new Elem(x, curr);						
	if (!prev) head = nel;
	else prev->next = nel;
	if (!curr) tail = nel;
	num++;
	return *this;
}

List & List::Remove(int x)
{
	if (!head) throw ErrEmpty();
	Elem* curr =head , *prev = nullptr;
	while (curr && curr->key != x) {
		prev = curr;
		curr = curr->next;
	}
	if (!curr) throw ErrNoElement(x);
	if (curr == head) head = curr->next;
	else prev->next = curr->next;
	if (curr == tail) tail = prev;
	delete curr;
	num--;
	return *this;
}

List * List::Intersection(const List & s) const
{
	Elem* p1 = head, *p2 = s.head;
	List *nel = new List;
	while (p1 != nullptr && p2 != nullptr) {
		if (p1->key == p2->key) {
			nel->Insert(p1->key);
			p1 = p1->next;
			p2 = p2->next;
		}
		else if (p1->key < p2->key) p1 = p1->next;
		else p2 = p2->next;
	}
	return nel;
}

bool List::Belongs(int x) const
{
	if (!head) throw ErrEmpty();
	Elem * curr = head;
	while (curr && curr->key != x) curr = curr->next;
	if (!curr) return false;
	return true;
}

List & List::RemoveRange(int a, int b)
{
	if (!head) throw ErrEmpty();
	if (a>b) throw ErrRange();
	Elem* curr = head, *prev = nullptr;
	while (curr->key < a) { 
		prev = curr;
		curr = curr->next; 
	}
	while (curr && (curr->key >= a && curr->key <= b)) {
		if (curr == head) head = curr->next;
		else prev->next = curr->next;
		if (curr == tail) tail = prev;
		Elem *next = curr->next;
		delete curr;
		curr = next;
	}
	return *this;
}

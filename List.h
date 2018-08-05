#ifndef _LISTA_
#define _LISTA_

#include "Set.h"

class List : public Set {
private:
	struct Elem {
		int key;
		struct Elem* next;
		Elem(int k, Elem*s=nullptr): key(k),next(s){}
	};
	Elem* head = nullptr, *tail = nullptr;
	void del();
	void Read(istream& ut) override;
	void Write(ostream& it) const override;
public:
	List(){}					
	List(const List& l) = delete;
	List& operator=(const List& l) = delete;
	~List() { del(); }
	bool Belongs(int x) const override; 
	List& Insert(int x) override;
	List& Remove(int x) override;
	List* Intersection(const List& s) const;				
	List& RemoveRange(int a, int b) override;
	void DeleteAll() override { del(); }
};

#endif

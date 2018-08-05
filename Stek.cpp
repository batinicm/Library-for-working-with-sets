#include "BST.h"

Stack::~Stack()
{
	while (sp) {
		Elem* stari = sp;
		sp = sp->next;
		delete stari;
	}
	sp = nullptr;
}

#include "BinStablo.h"

Stek::~Stek()
{
	while (sp) {
		Elem* stari = sp;
		sp = sp->sled;
		delete stari;
	}
	sp = nullptr;
}

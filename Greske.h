#ifndef _GRESKE_
#define _GRESKE_
#include <iostream>
using namespace std;

class Grpostoji {
private:
	int x;
public:
	Grpostoji(int a):x(a){}
	friend ostream& operator<<(ostream& it, const Grpostoji& g) {
		it << "*** Element "<< g.x <<" vec postoji u skupu! ***\n";
		return it;
	}
};
class Grnepostoji {
private:
	int x;
public:
	Grnepostoji(int a) :x(a) {}
	friend ostream& operator<<(ostream& it, const Grnepostoji& g) {
		it << "*** Element " << g.x << " ne postoji u skupu! ***\n";
		return it;
	}
};
class Gropseg {
public:
	friend ostream& operator<<(ostream& it, const Gropseg& g) {
		it << "*** Granice opsega su nevalidne! ***\n";
		return it;
	}
};
class Grprazno {
public:
	friend ostream& operator<<(ostream& it, const Grprazno&) {
		return it << "***Skup je prazan!***\n";
	}
};
class Grpresek {
public:
	friend ostream& operator<<(ostream& it, const Grpresek&) {
		return it << "***Nije moguce naci presek ova dva skupa!***\n";
	}
};
#endif

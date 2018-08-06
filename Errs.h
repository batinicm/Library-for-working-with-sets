#ifndef _GRESKE_
#define _GRESKE_
#include <iostream>
using namespace std;

class ErrElExists {
private:
	int x;
public:
	ErrElExists(int a):x(a){}
	friend ostream& operator<<(ostream& it, const ErrElExists& g) {
		it << "*** The element "<< g.x <<" already exists in the set! ***\n";
		return it;
	}
};
class ErrNoElement {
private:
	int x;
public:
	ErrNoElement(int a) :x(a) {}
	friend ostream& operator<<(ostream& it, const ErrNoElement& g) {
		it << "*** The element " << g.x << " does not exist in the set! ***\n";
		return it;
	}
};
class ErrRange {
public:
	friend ostream& operator<<(ostream& it, const ErrRange& g) {
		it << "*** Range limits invalid! ***\n";
		return it;
	}
};
class ErrEmpty {
public:
	friend ostream& operator<<(ostream& it, const ErrEmpty&) {
		return it << "*** The set is empty! ***\n";
	}
};

class ErrFile {
public:
	friend ostream& operator<<(ostream& it, const ErrFile&) {
		return it << "*** File not opened! ***\n";
	}
};
#endif

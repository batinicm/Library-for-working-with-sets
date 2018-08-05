#ifndef _SET_
#define _SET_

#include <iostream>
using namespace std;

class Set {
protected:								
	int num;
public:
	Set() { num = 0; }
	virtual ~Set(){}
	virtual bool Belongs(int x) const = 0; 
	virtual Set& Insert(int x) = 0;
	virtual Set& Remove(int x) = 0;
	virtual Set& RemoveRange(int a, int b) = 0;
	int NumOfEls()const { return num; }
	virtual void DeleteAll() = 0;
protected:
	virtual void Write(ostream& it) const { it << "Number of elements in the set: "<<num<<' '; }
	friend ostream& operator<<(ostream& it, const Set& s) {
		s.Write(it);
		return it;
	}
	virtual void Read(istream& ut) = 0;
	friend istream& operator >> (istream& ut, Set& s) {
		s.Read(ut);
		return ut;
	}
};

#endif

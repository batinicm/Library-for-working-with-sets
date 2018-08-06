#ifndef PERFORMANCE_CALCULATOR_H__
#define PERFORMANCE_CALCULATOR_H__
#include "windows.h"
class PerformanceCalculator {
	LARGE_INTEGER startCounter;
	LARGE_INTEGER stopCounter;
	LARGE_INTEGER frequency;
public:
	PerformanceCalculator() {
		startCounter.QuadPart = stopCounter.QuadPart = 0;
		QueryPerformanceFrequency(&frequency);
	}
	void start() {
		QueryPerformanceCounter(&startCounter);
	}
	void stop() {
		QueryPerformanceCounter(&stopCounter);
	}
	double elapsedMillis() const {
		return (stopCounter.QuadPart - startCounter.QuadPart)*1000. / frequency.QuadPart;
	}
};

class MTRand_int32 { // Mersenne Twister random number generator
public:
	// default constructor: uses default seed only if this is the first instance
	MTRand_int32() { if (!init) seed(5489UL); init = true; }
	// constructor with 32 bit int as seed
	MTRand_int32(unsigned long s) { seed(s); init = true; }
	// constructor with array of size 32 bit ints as seed
	MTRand_int32(const unsigned long* array, int size) { seed(array, size); init = true; }
	// the two seed functions
	void seed(unsigned long); // seed with 32 bit integer
	void seed(const unsigned long*, int size); // seed with array
											   // overload operator() to make this a generator (functor)
	unsigned long operator()() { return rand_int32(); }
	// 2007-02-11: made the destructor virtual; thanks "double more" for pointing this out
	virtual ~MTRand_int32() {} // destructor
protected: // used by derived classes, otherwise not accessible; use the ()-operator
	unsigned long rand_int32(); // generate 32 bit random integer
private:
	static const int n = 624, m = 397; // compile time constants
									   // the variables below are static (no duplicates can exist)
	static unsigned long state[n]; // state vector array
	static int p; // position in state array
	static bool init; // true if init function is called
					  // private functions used to generate the pseudo random numbers
	unsigned long twiddle(unsigned long, unsigned long); // used by gen_state()
	void gen_state(); // generate new state
					  // make copy constructor and assignment operator unavailable, they don't make sense
	MTRand_int32(const MTRand_int32&); // copy constructor not defined
	void operator=(const MTRand_int32&); // assignment operator not defined
};

// inline for speed, must therefore reside in header file
inline unsigned long MTRand_int32::twiddle(unsigned long u, unsigned long v) {
	return (((u & 0x80000000UL) | (v & 0x7FFFFFFFUL)) >> 1)
		^ ((v & 1UL) * 0x9908B0DFUL);
	// 2013-07-22: line above modified for performance according to http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/Ierymenko.html
	// thanks Vitaliy FEOKTISTOV for pointing this out
}

inline unsigned long MTRand_int32::rand_int32() { // generate 32 bit random int
	if (p == n) gen_state(); // new state vector needed
							 // gen_state() is split off to be non-inline, because it is only called once
							 // in every 624 calls and otherwise irand() would become too big to get inlined
	unsigned long x = state[p++];
	x ^= (x >> 11);
	x ^= (x << 7) & 0x9D2C5680UL;
	x ^= (x << 15) & 0xEFC60000UL;
	return x ^ (x >> 18);
}

// generates double floating point numbers in the half-open interval [0, 1)
class MTRand : public MTRand_int32 {
public:
	MTRand() : MTRand_int32() {}
	MTRand(unsigned long seed) : MTRand_int32(seed) {}
	MTRand(const unsigned long* seed, int size) : MTRand_int32(seed, size) {}
	~MTRand() {}
	double operator()() {
		return static_cast<double>(rand_int32()) * (1. / 4294967296.);
	} // divided by 2^32
private:
	MTRand(const MTRand&); // copy constructor not defined
	void operator=(const MTRand&); // assignment operator not defined
};

// generates double floating point numbers in the closed interval [0, 1]
class MTRand_closed : public MTRand_int32 {
public:
	MTRand_closed() : MTRand_int32() {}
	MTRand_closed(unsigned long seed) : MTRand_int32(seed) {}
	MTRand_closed(const unsigned long* seed, int size) : MTRand_int32(seed, size) {}
	~MTRand_closed() {}
	double operator()() {
		return static_cast<double>(rand_int32()) * (1. / 4294967295.);
	} // divided by 2^32 - 1
private:
	MTRand_closed(const MTRand_closed&); // copy constructor not defined
	void operator=(const MTRand_closed&); // assignment operator not defined
};

// generates double floating point numbers in the open interval (0, 1)
class MTRand_open : public MTRand_int32 {
public:
	MTRand_open() : MTRand_int32() {}
	MTRand_open(unsigned long seed) : MTRand_int32(seed) {}
	MTRand_open(const unsigned long* seed, int size) : MTRand_int32(seed, size) {}
	~MTRand_open() {}
	double operator()() {
		return (static_cast<double>(rand_int32()) + .5) * (1. / 4294967296.);
	} // divided by 2^32
private:
	MTRand_open(const MTRand_open&); // copy constructor not defined
	void operator=(const MTRand_open&); // assignment operator not defined
};

// generates 53 bit resolution doubles in the half-open interval [0, 1)
class MTRand53 : public MTRand_int32 {
public:
	MTRand53() : MTRand_int32() {}
	MTRand53(unsigned long seed) : MTRand_int32(seed) {}
	MTRand53(const unsigned long* seed, int size) : MTRand_int32(seed, size) {}
	~MTRand53() {}
	double operator()() {
		return (static_cast<double>(rand_int32() >> 5) * 67108864. +
			static_cast<double>(rand_int32() >> 6)) * (1. / 9007199254740992.);
	}
private:
	MTRand53(const MTRand53&); // copy constructor not defined
	void operator=(const MTRand53&); // assignment operator not defined
};
unsigned long MTRand_int32::state[n] = { 0x0UL };
int MTRand_int32::p = 0;
bool MTRand_int32::init = false;

void MTRand_int32::gen_state() { // generate new state vector
	for (int i = 0; i < (n - m); ++i)
		state[i] = state[i + m] ^ twiddle(state[i], state[i + 1]);
	for (int i = n - m; i < (n - 1); ++i)
		state[i] = state[i + m - n] ^ twiddle(state[i], state[i + 1]);
	state[n - 1] = state[m - 1] ^ twiddle(state[n - 1], state[0]);
	p = 0; // reset position
}

void MTRand_int32::seed(unsigned long s) {  // init by 32 bit seed
	state[0] = s & 0xFFFFFFFFUL; // for > 32 bit machines
	for (int i = 1; i < n; ++i) {
		state[i] = 1812433253UL * (state[i - 1] ^ (state[i - 1] >> 30)) + i;
		// see Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier
		// in the previous versions, MSBs of the seed affect only MSBs of the array state
		// 2002/01/09 modified by Makoto Matsumoto
		state[i] &= 0xFFFFFFFFUL; // for > 32 bit machines
	}
	p = n; // force gen_state() to be called for next random number
}

void MTRand_int32::seed(const unsigned long* array, int size) { // init by array
	seed(19650218UL);
	int i = 1, j = 0;
	for (int k = ((n > size) ? n : size); k; --k) {
		state[i] = (state[i] ^ ((state[i - 1] ^ (state[i - 1] >> 30)) * 1664525UL))
			+ array[j] + j; // non linear
		state[i] &= 0xFFFFFFFFUL; // for > 32 bit machines
		++j; j %= size;
		if ((++i) == n) { state[0] = state[n - 1]; i = 1; }
	}
	for (int k = n - 1; k; --k) {
		state[i] = (state[i] ^ ((state[i - 1] ^ (state[i - 1] >> 30)) * 1566083941UL)) - i;
		state[i] &= 0xFFFFFFFFUL; // for > 32 bit machines
		if ((++i) == n) { state[0] = state[n - 1]; i = 1; }
	}
	state[0] = 0x80000000UL; // MSB is 1; assuring non-zero initial array
	p = n; // force gen_state() to be called for next random number
}

#endif

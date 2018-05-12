#ifndef INTEGER_H
#define INTEGER_H
#include <iostream>
#include "String.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long u64;

#define upper4(b) ((b >> 4) & 0x0F)
#define lower4(b) (b & 0x0F)

int highestbit(int n);

class Integer {

	friend Integer operator+(const Integer &n1, const Integer &n2);
	friend Integer operator-(const Integer &n1, const Integer &n2);
	friend Integer operator*(const Integer &n1, const Integer &n2);
	friend Integer operator%(const Integer &n1, const Integer &n2);

public:
	Integer();
	Integer(u32 n);
	Integer(const char *);
	Integer(const Integer &n);
	const Integer& operator=(const Integer &n);
	~Integer();
	String toHexString();
	String toString();


private:
	u32 *m;
	u32 len;

};

#endif
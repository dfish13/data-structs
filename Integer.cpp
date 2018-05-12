#include <cstring>
#include "Integer.h"

int highestbit(int n) {
	int mask = 0x80000000, c = 32;
	while ((c > 0) && !(mask & n)) {
		n <<= 1;
		c--;
	}
	return c;
}

Integer::Integer() {
	m = NULL;
	len = 0;
}

Integer::Integer(u32 n) {
	m = new u32;
	m[0] = n;
	len = 1;
}

Integer::Integer(const Integer& n) {
	m = new u32[n.len];
	len = n.len;
	memcpy(m, n.m, len*sizeof(u32));
}

const Integer& Integer::operator=(const Integer &n) {
	delete [] m;
	m = new u32[n.len];
	len = n.len;
	memcpy(m, n.m, len*sizeof(u32));
	return *this;
}

Integer::~Integer() {
	delete [] m;
}

String Integer::toHexString() {
	char digits[17] = "0123456789abcdef";
	u32 a, mask = 0x0000000F, *arr = (u32 *) this->m;
	String s("0x");
	int i, j = 32;
	// eat up leading zeroes
	while (!((arr[0] >> (j-4)) & mask))
		j -= 4;

	for (i = 0; i < this->len; i++) {
		while (j > 0) {
			a = (arr[i] >> (j-4)) & mask;
			s = s + digits[a];
			j -= 4;
		}
		j = 32;	
	}

	return s;
}

Integer operator+(const Integer &n1, const Integer &n2) {
	Integer sum;
	int max = (n1.len > n2.len) ? n1.len : n2.len;
	u32 *m = new u32[max];
	u64 a, b, c = 0;
	int i = max - 1;
	while (i >= 0) {
		a = (u64) n1.m[i];
		b = (u64) n2.m[i];
		c += a + b;
		m[i] = c;
		c >>= 32;
		i--;
	}
	if (c) {
		u32 *temp = new u32[max + 1];
		memcpy((temp + 1), m, max*sizeof(u32));
		temp[0] = c;
		sum.m = temp;
		sum.len = max + 1;
		delete [] m;
	}
	else {
		sum.m = m;
		sum.len = max;
	}

	return sum;
}

Integer operator*(const Integer &n1, const Integer &n2) {
	Integer prod;
	u64 a, b, c = 0;
	u32 m = n1.len, n = n2.len;
	int i, j;
	u64 *arr = new u64[(m+n)-1];

	for (i = 0; i < (m+n)-1; i++)
		arr[i] = 0;

	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			a = n1.m[i];
			b = n2.m[j];
			arr[i+j] += a*b;
		}
	}

	for (i = (m+n)-2; i >= 0; i--) {
		arr[i] += c;
		c = arr[i] >> 32;
	}

	if (c) {
		prod.m = new u32[m+n];
		prod.m[0] = (u32) c;
		for (i = 1; i < (m+n); i++) {
			prod.m[i] = (u32) arr[i-1];
		}
		prod.len = m+n;
	}
	else {
		prod.m = new u32[(m+n)-1];
		for (i = 0; i < (m+n)-1; i++) {
			prod.m[i] = (u32) arr[i];
		}
		prod.len = (m+n)-1;
	}

	delete [] arr;
	return prod;
}

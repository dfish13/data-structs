#include <stdlib.h>
#include <string.h>
#include "String.h"


String::String() {
	cstr = new char[INIT_SIZE + 1];
	max = INIT_SIZE;
	size = 0;
}

String::String(char *s) {
	max = size = strlen(s);
	cstr = new char[size+1];
	strcpy(cstr, s);
}

String::String(char c) {
	max = size = 1;
	cstr = new char[size+1];
	cstr[0] = c;
	cstr[1] = '\0';
}

String::String(const String &s) {
	max = size = s.size;
	cstr = new char[size+1];
	strcpy(cstr, s.cstr);
}

String::~String() {
	delete [] cstr;
}

char String::operator[](size_t i) const {
	return cstr[i];
}

const char* String::cstring() const {
	return cstr;
}

size_t String::len() {
	return size;
}

void String::shrink() {
	if (max > size) {
		char *buf = new char[size+1];
		strcpy(buf, cstr);
		delete [] cstr;
		cstr = buf;
		max = size;
	}
}

void String::grow() {
	char *buf = new char[(max*=GROW)+1];
	strcpy(buf, cstr);
	delete [] cstr;
	cstr = buf;
}

const String& String::operator=(const String& s) {
	delete [] cstr;
	size = max = s.size;
	cstr = new char[size + 1];
	strcpy(cstr, s.cstr);
	return *this;
}

std::ostream& operator<<(std::ostream &os, const String &s) {
	return os << s.cstr ;
}

std::istream& operator>>(std::istream &is, String &s) {
	char delims[] = {' ', '\n', '\t'};
	char c;
	int i = 0;

	// eat up delim chars
	while (is.get(c)) {
		if (c != delims[0] && c != delims[1] && c != delims[2]) {
			is.putback(c);
			break;
		}
	}

	while (is.get(c)) {
		if (i == s.max) {
			s.cstr[i] = '\0' ;
			s.grow();
		}
		if (c != delims[0] && c != delims[1] && c != delims[2]) {
			s.cstr[i] = c;
		}
		else {
			is.putback(c);
			break;
		}
		i++;
	}
	s.size = i;
	s.cstr[i] = '\0' ;
	return is;
}

String operator+(const String &a, const String &b) {
	String c;
	c.size = c.max  = a.size + b.size;
	c.cstr = new char[c.size + 1];
	strcpy(c.cstr, a.cstr);
	strcat(c.cstr, b.cstr);
	return c;
}

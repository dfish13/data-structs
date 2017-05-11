#include <cstdlib>
#include <cstring>
#include "String.h"


String::String() {
	cstr = NULL;
	size = max = 0;
}

String::String(const char *s) {
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

String String::substring(size_t pos, size_t len) const {
	char buf[len + 1];
	strncpy(buf, &cstr[pos], len);
	return String(buf);
}

char String::operator[](size_t i) const {
	return cstr[i];
}

bool String::operator==(const String &s) const {
	return !strcmp(cstr, s.cstr);
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
	if(cstr == NULL) {
		max = 1;
		size = 0;
		cstr = new char[max + 1];
	} else {
		char *buf = new char[(max*=GROW)+1];
		strcpy(buf, cstr);
		delete [] cstr;
		cstr = buf;
	}
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
			s.grow();
			s.cstr[i] = '\0' ;
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
	char *sum = new char[a.size + b.size + 1];
	strcpy(sum, a.cstr);
	strcat(sum, b.cstr);
	return String(sum);
}

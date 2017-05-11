#ifndef STRING_H
#define STRING_H
#include <iostream>

#define GROW 2

class String {
	
	friend std::ostream& operator<<(std::ostream &os, const String &s);
	friend std::istream& operator>>(std::istream &is, String &s);
	friend String operator+(const String &a, const String &b);

	public:
		String();
		String(const char *s);
		String(char c);
		String(const String &s);
		~String();
		String substring(size_t pos = 0, size_t len = npos) const;
		char operator[](size_t i) const;
		const String& operator=(const String& s);
		bool operator==(const String &s) const;
		const char* cstring() const;
		size_t len();
		void shrink();
	
	private:
		void grow();
		char *cstr;
		size_t size, max;

		static const size_t npos = -1;
};

#endif

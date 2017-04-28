#include <iostream>

#define GROW 2
#define INIT_SIZE 1

class String {
	
	friend std::ostream& operator<<(std::ostream &os, const String &s);
	friend std::istream& operator>>(std::istream &is, String &s);
	friend String operator+(const String &a, const String &b);


	public:
		String();
		String(char *s);
		String(char c);
		String(const String &s);
		~String();
		String substring(int i);
		char operator[](size_t i) const;
		const String& operator=(const String& s);
		const char* cstring() const;
		size_t len();
		void shrink();
	
	private:
		void grow();
		char *cstr;
		int size, max;
};
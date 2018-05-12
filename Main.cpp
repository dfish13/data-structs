#include "String.h"
#include "Stack.h"
#include "Integer.h"
#include <iostream>

using namespace std;

bool string_tests();
bool stack_tests();
bool integer_tests();

typedef bool (*func_ptr_t)(void);

func_ptr_t tests[] = {
	&string_tests,
	&stack_tests,
	&integer_tests,
	NULL
};

int main(int argc, char **argv) {


	int i = 0, passed = 0;

	while (tests[i] != NULL) {
		if(tests[i]()) {
			cout << "pass\n" ;
			++passed;
		}
		else {
			cout << "fail\n" ;
		}
		i++;
	}

	cout << passed << '/' << i << " tests passed.\n" ;

	return 0;
}

bool string_tests() {
	String a("hi"), b, c("bye");
	b = a;
	return (a == b) && !(a == c);
}

bool stack_tests() {
	bool success = true;
	
	Stack<char> s;
	if (!s.empty())
		success = false;

	s.push('A');
	s.push('B');

	if (s.size() != 2)
		success = false;
	if (s.pop() != 'B')
		success = false;
	if (s.pop() != 'A')
		success = false;

	return s.empty();
}

bool integer_tests() {
	int i;
	String s, answer("0x350ed972b7230ec8e482387a8997cee5a5d");

	Integer n(1);

	for (i = 0; i < 5; i++) {
		n = n * 0xbadf00d;
	}

	s = n.toHexString();
	return (s == answer);
}

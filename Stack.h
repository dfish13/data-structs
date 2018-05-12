#ifndef STACK_H
#define STACK_H
#include <utility>

template <typename Object>
class Stack {

	public:

		// disallow copying and moving stacks
		Stack() : s(0), top(NULL) {}
		Stack(const Stack &) = delete;
		Stack(Stack &&) = delete;
		Stack & operator=(const Stack &) = delete;
		Stack & operator=(Stack &&) = delete;

		~Stack() {
			while (!empty()) 
				pop();
		}

		const Object & peek() const {
			return top->data;
		}

		Object pop() {
			Node * a = top;
			top = top->next;
			Object temp = std::move(a->data);
			delete a;
			--s;
			return temp;
		}

		void push(const Object & d) {
			Node * temp = new Node(d, top);
			top = temp;
			++s;
		}

		void push(Object && d) {
			Node * temp = new Node(d, top);
			top = temp;
			++s;
		}

		bool empty() const {
			return s == 0;
		}

		int size() const {
			return s;
		}


	private:
		struct Node {
			Object data;
			Node *next;

			Node(const Object & d = Object(), Node * p = NULL)
				: data(d), next(p) {}

			Node(Object && d, Node * p = NULL)
				: data(std::move(d)), next(p) {}
		};

		Node *top;
		int s;
};

#endif

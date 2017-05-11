#ifndef STACK_H
#define STACK_H
#include <utility>

template <typename Object>
class Stack {

	public:

		const Object & peek() const {
			return top->data;
		}

		Object pop() {
			Node * a = top;
			top = top->next;
			Object temp = std::move(a->data);
			delete a;
			return temp;
		}

		void push(const Object & d) {
			Node * temp = new Node(d, top);
			top = temp;
		}

		void push(Object && d) {
			Node * temp = new Node(d, top);
			top = temp;
		}

		bool empty() {
			return top != NULL;
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
};

#endif

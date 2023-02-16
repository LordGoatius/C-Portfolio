#ifndef STACK_H
#define STACK_H

#include "Deque.hpp"

template<typename T>
class Stack {
private:
	Deque<T> container_;
public:
	Stack() {}
	~Stack() {}

	void push(const T& data) {
		container_.push_back(data);
	}

	void pop() {
		container_.pop_back();
	}

	T& top() {
		return container_.back();
	}

	size_t size() {
		return container_.size();
	}

	T& at(size_t index) {
		return container_.at(index);
	}

	string toString() const {
		return container_.toString();
	}

	friend ostream& operator<<(ostream& os, const Stack<T>& d) {
		os << d.toString();
		return os;
	}
};
#endif

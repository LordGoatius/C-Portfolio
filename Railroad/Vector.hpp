#ifndef VECTOR_H
#define VECTOR_H

#include "Deque.hpp"

template<typename T>
class Vector {
private:
	Deque<T> container_;
public:
	Vector() {}
	~Vector() {}

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

	friend ostream& operator<<(ostream& os, const Vector<T>& d) {
		os << d.toString();
		return os;
	}
};
#endif


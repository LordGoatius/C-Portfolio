#ifndef QUEUE_H
#define QUEUE_H

#include "Deque.hpp"

template<typename T>
class Queue {
private:
	Deque<T> container_;
public:
	Queue() {}
	~Queue() {}

	void push(const T& data) {
		container_.push_back(data);
	}

	void pop() {
		container_.pop_front();
	}

	T& top() {
		return container_.front();
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

	friend ostream& operator<<(ostream& os, const Queue<T>& d) {
		os << d.toString();
		return os;
	}
};
#endif

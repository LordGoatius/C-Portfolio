#ifndef DEQUE_H
#define DEQUE_H
#include "DequeInterface.h"
#include <iostream>

using namespace std;

template<typename T>
class Deque : public DequeInterface<T> {
private:
	size_t capacity;
	size_t size_;
	size_t front_index;
	size_t rear_index;
	T* data_;
public:
	Deque(void) : capacity(DEFAULT_CAPACITY), size_(0), front_index(0), rear_index(-1), data_(new T[DEFAULT_CAPACITY]) {}
	~Deque(void) { delete[] data_; }

	/** Insert item at front of deque */
	virtual void push_front(const T& value) {
		if (size_ == capacity) {
			capacity *= 2;
			T* temp = new T[capacity];
			copyFront(data_, temp, capacity / 2, value);
			T* tempTwo = data_;
			data_ = temp;
			delete[] tempTwo;
			++size_;
			++rear_index;
		}
		else {
			for (unsigned i = size_; i > 0; --i) {
				data_[i] = data_[i - 1];
			}
			data_[0] = value;
			++size_;
			++rear_index;
		}
	}

	void copyFront(const T* old, T* next, size_t size, const T& value) {
		next[0] = value;
		for (unsigned i = 0; i < size; ++i) {
			next[i + 1] = old[i];
		}
	}

	void copy(const T* old, T* next, size_t size) {
		size /= 2;
		for (unsigned i = 0; i < size; ++i) {
			next[i] = old[i];
		}
	}

	/** Insert item at rear of deque */
	virtual void push_back(const T& value) {
		if (size_ == capacity) {
			capacity *= 2;
			T* temp = new T[capacity];
			copy(data_, temp, capacity);
			T* tempTwo = data_;
			data_ = temp;
			delete[] tempTwo;
			data_[size_] = value;
			++size_;
			++rear_index;
		}
		else {
			data_[size_] = value;
			++size_;
			++rear_index;
		}
	}

	/** Remove the front item of the deque */
	virtual void pop_front(void) {
		for (unsigned i = 0; i < size_ - 1; ++i) {
			data_[i] = data_[i + 1];
		}
		data_[rear_index] = 0;
		--rear_index;
		--size_;
	}

	/** Remove the rear item of the deque */
	virtual void pop_back(void) {
		data_[rear_index] = 0;
		--rear_index;
		--size_;
	}

	/** Return the front item of the deque (Do not remove) */
	virtual T& front(void) {
		return data_[front_index];
	}

	/** Return the rear item of the deque (Do not remove) */
	virtual T& back(void) {
		return data_[rear_index];
	}

	/** Return the number of items in the deque */
	virtual size_t size(void) const {
		return size_;
	}

	/** Return true if deque is empty */
	virtual bool empty(void) const {
		if (size_ == 0) return true;
		return false;
	}

	/** Return item in deque at index (0 based) */
	virtual T& at(size_t index) {
		return data_[index];
	}

	/** Return the deque items */
	virtual string toString(void) const {
		ostringstream oss;
		for (size_t i = 0; i < size_; ++i) oss << " " << data_[i];
		if (!this->empty()) return oss.str().substr(1, oss.str().size());
		return "";
	}

	friend ostream& operator<<(ostream& os, const Deque<T>& d) {
		os << d.toString();
		return os;
	}
};
#endif


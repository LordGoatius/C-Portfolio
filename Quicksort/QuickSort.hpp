#ifndef QUICKSORT_H
#define QUICKSORT_H

#include<sstream>
#include "QSInterface.h"

using namespace std;

template<typename T>
class QuickSort : public QSInterface<T> {
private:
	T* array_;
	size_t capacity_;
	size_t size_;
public:
	int comparison;
	int exchanges;

	QuickSort(size_t capacity) : capacity_(capacity), size_(0), comparison(0), exchanges(0) {
		array_ = new T[capacity];
		for (unsigned i = 0; i < capacity; ++i) {
			array_[i] = 0;
		}
	}
	virtual ~QuickSort() {
		delete[] array_;
	}

	virtual bool addElement(T element) {
		++size_;
		if (size_ == capacity_) {
			reallocate();
		}
		array_[size_ - 1] = element;
		return true;
	}

	void reallocate() {
		T* temp = new T[capacity_ * 2];
		for (unsigned i = 0; i < capacity_ * 2; ++i) {
			temp[i] = 0;
		}
		for (unsigned i = 0; i < capacity_; ++i) {
			temp[i] = array_[i];
		}
		capacity_ *= 2;

		T* tempTwo = this->array_;
		this->array_ = temp;
		delete[] tempTwo;
	}

	virtual bool sort(size_t left, size_t right) {
		if (left != right) {
			size_t pivot = partition(left, right, medianOfThree(left, right));

			sort(left, pivot);
			sort(pivot + 1, right);
		}
		return true;
	}

	virtual bool sortAll() {
		comparison = 0;
		exchanges = 0;
		return sort(0, size_);
	}

	virtual bool clear() {
		for (unsigned i = 0; i < capacity_; ++i) {
			array_[i] = 0;
		}
		size_ = 0;
		comparison = 0;
		exchanges = 0;
		return true;
	}

	virtual size_t capacity() const {
		return this->capacity_;
	}

	virtual size_t size() const {
		return this->size_;
	}

	virtual int medianOfThree(size_t left, size_t right) {
		cout << size_;
		if (size_ == 0 || left >= right || right > size_) return -1;
		int mid = ((left + right) / 2);

		if (array_[mid] < array_[left]) {
			++comparison;
			swap(array_[mid], array_[left]);
		}
		if (array_[mid] > array_[right-1]) {
			++comparison;
			swap(array_[mid], array_[right-1]);
		}
		if (array_[mid] < array_[left]) {
			++comparison;
			swap(array_[mid], array_[left]);
		}
		if (array_[mid] > array_[right - 1]) {
			++comparison;
			swap(array_[mid], array_[right - 1]);
		}
		return mid;
	}

	virtual int partition(size_t left, size_t right, size_t pivotIndex) {
		if (size_ == 0 || left >= right || right > size_ || pivotIndex > right) return -1;
		swap(array_[left], array_[pivotIndex]);
		++exchanges;
		size_t up = left + 1;
		size_t down = right - 1;
		do {
			++comparison;
			while ((up != right - 1) && !(array_[left] < array_[up])) {
				++comparison;
				++up;
			}
			while (array_[left] < array_[down]) {
				++comparison;
				--down;
			}
			if (up < down) {
				++comparison;
				swap(array_[up], array_[down]);
				++exchanges;
			}
		} while (up < down);

		swap(array_[left], array_[down]);
		return down;
	}

	virtual string toString() const {
		if (size_ == 0) return "Empty";
		ostringstream oss;
		for (unsigned i = 0; i < size_ - 1; ++i) {
			oss << array_[i] << ",";
		}
		oss << array_[size_ - 1];
		return oss.str();
	}

	friend ostream& operator<<(ostream& os, const QuickSort<T>& QuickSort) {
		os << QuickSort.toString();
		return os;
	}
};
#endif


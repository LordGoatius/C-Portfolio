#ifndef LINKED_LIST_INTERFACE_H
#define LINKED_LIST_INTERFACE_H
#include <string>
using namespace std;

template<typename T>
class LinkedListInterface {
public:
	LinkedListInterface(void) {}
	virtual ~LinkedListInterface(void) {}

	virtual void push_front(const T& value) = 0;

	virtual void pop_front(void) = 0;

	virtual T& front(void) = 0;

	virtual bool empty(void) const = 0;

	virtual void remove(const T& value) = 0;

	virtual void clear(void) = 0;

	virtual void reverse(void) = 0;

	virtual size_t size(void) const = 0;

	virtual string toString(void) const = 0;
};
#endif	// LINKED_LIST_INTERFACE_H
#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include "LinkedListInterface.h"

#include<iostream>

template<typename T>
class LinkedList : public LinkedListInterface<T> {
public:
	LinkedList(void) : head(NULL) {}
	LinkedList(const LinkedList<T>& list) {
		for (Node* temp = list.head; temp != NULL; temp = temp->next) {
			push_front(temp->data);
		}
		reverse();
	}

	~LinkedList(void) {
		this->clear();
	}

	LinkedList<T>& operator=(const LinkedList<T>& list) {
		LinkedList<string> copy = LinkedList<string>(list);
		LinkedList<string>* temp = this;
		*this = copy;
		copy = temp;
		return *this;
	}

	//inserts at front
	virtual void push_front(const T& value) {
		head = new Node(value, head);
	}

	//removes front node
	virtual void pop_front(void) {
		Node* temp = head->next;
		delete head;
		head = temp;
	}

	//returns head data
	virtual T& front(void) {
		return head->data;
	}

	//return true if empty
	virtual bool empty(void) const {
		if (head == NULL) {
			return true;
		} else {
			return false;
		}
	}

	//remove nodes with value
	virtual void remove(const T& value) {
		if (this->empty()) {
			return;
		}
		Node* myPtr = head;
		Node* temp = NULL;
		while (myPtr->data == value) {
			this->pop_front();
			if (this->empty()) {
				myPtr = NULL;
				break;
			}
			else
				myPtr = head;
		}

		for (; myPtr != NULL; myPtr = myPtr->next) {
			temp = NULL;
			while (myPtr->next != NULL && myPtr->next->data == value) {
				temp = myPtr->next;
				if (myPtr->next->next != NULL)
					myPtr->next = myPtr->next->next;
				else
					myPtr->next = NULL;		
				delete temp;
			}

		}
	}

	//deletes all nodes
	virtual void clear(void) {
		Node* temp = NULL;
		while (head != NULL) {
			temp = head->next;
			delete head;
			head = temp;
		}
	}

	//reverses all nodes
	virtual void reverse(void) {
		Node* previous = NULL;
		Node* next = NULL;
		Node* current = head;
		while (current != NULL) {
			next = current->next;
			current->next = previous;
			previous = current;
			current = next;
		}
		head = previous;
	}

	//return nodes
	virtual size_t size(void) const {
		Node* temp = head;
		int count = 0;
		while (temp != NULL) {
			count++;
			temp = temp->next;
		}
		return count;
	}
	
	virtual string toString(void) const {
		Node* temp = head;
		string str = "";
		while (temp != NULL) {
			str = str + (string)temp->data;
			str += " ";
			temp = temp->next;
		}
		return str;
	}

private:
	struct Node {
		T data;
		Node* next;
		Node(const T& d, Node* n) :data(d), next(n) {}
	};
	Node* head;
};
#endif

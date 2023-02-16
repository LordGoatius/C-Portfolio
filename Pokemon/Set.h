#ifndef SET_H_
#define SET_H_

#include "SetInterface.h"

using namespace std;

template<typename T>
class Set : public SetInterface<T> {
private:
	struct Node {
		T data;
		Node* next;
		Node(const T& d, Node* n) : data(d), next(n) {}
	};
	Node* head;
public:
	Set(void) : head(NULL) {}
	Set(const Set<T>& list) {
		for (Node* temp = list.head; temp != NULL; temp = temp->next) {
			push_front(temp->data);
		}
		reverse();
	} 

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

	/*Set<T>& operator=(const Set<T>& list) {
		Set<T> copy = Set<T>(list);
		Set<T>* temp = this;
		*this = copy;
		copy = temp;
		return *this;
	}*/

	virtual ~Set(void) {
		this->clear();
	}

	Node* last() {
		Node* temp = head;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		return temp;
	}

	// Inserts item into the set, if the container doesn't already contain an element with an equivalent value. 
	virtual bool insert(const T& item) {
		if (this->head == NULL) {
			head = new Node(item, NULL);
			return true;
		}
		if (count(item)) return false;
		if (this->size() == 1 && item.compare(this->head->data) > 0) {
			head->next = new Node(item, NULL);
			return true;
		} 
		else if (this->size() == 1 && item.compare(this->head->data) < 0) {
			head = new Node(item, this->head);
			return true;
		}
		if (item.compare(this->head->data) < 0) {
			head = new Node(item, this->head);
			return true;
		}
		if (item.compare(this->last()->data) > 0) {
			Node* temp = this->last();
			temp->next = new Node(item, NULL);
			return true;
		}

		Node* temp = head;
		while (item.compare(temp->next->data) > 0 ) {
			temp = temp->next;
		}
		if (temp->next == NULL) {
			Node* toInsert = new Node(item, NULL);
			temp->next = toInsert;
			return true;
		}
		Node* toInsert = new Node(item, temp->next);
		temp->next = toInsert;
		return true;
	}

	// Removes all items from the set. 
	virtual void clear(void) {
		Node* temp = NULL;
		while (head != NULL) {
			temp = head->next;
			delete head;
			head = temp;
		}
	}

	// Returns number of elements contained by the Set. 
	virtual size_t size(void) const {
		Node* temp = head;
		int count = 0;
		while (temp != NULL) {
			count++;
			temp = temp->next;
		}
		return count;
	}

	//returns 1 if contains element equivalent to item, else 0
	virtual size_t count(const T& item) {
		Node* temp = head;
		while (temp != NULL) {
			if (temp->data == item) return 1;
			temp = temp->next;
		}
		return 0;
	}

	//string representation of items in Set
	virtual string toString() const {
		Node* temp = head;
		string str = "[";
		while (temp != NULL) {
			str = str + (string)temp->data;
			str += ",";
			temp = temp->next;
		}
		str = str.substr(0, str.length() - 1);
		str += "]";
		return str;
	}

	string toStringTwo() const {
		Node* temp = head;
		string str = "";
		while (temp != NULL) {
			str = str + (string)temp->data;
			str += ",";
			temp = temp->next;
		}
		str = str.substr(0, str.length() - 1);
		return str;
	}

	friend ostream& operator<<(ostream& os, const Set<T>& linkedList) {
		os << linkedList.toStringTwo();
		return os;
	}
};
#endif
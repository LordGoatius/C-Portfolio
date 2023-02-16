#ifndef STATION_H
#define STATION_H

#include "Deque.hpp"
#include "Vector.hpp"
#include "Stack.hpp"
#include "Queue.hpp"

template<typename T>
class Station {
private:
	Vector<T> train_;
	Stack<T> stack_;
	Queue<T> queue_;
	T turnTableCar;
	bool empty;
public:
	Station() : empty(true) {}
	~Station() {}

	T& getCar() {
		return turnTableCar;
	}

	string addCar(const T& car) {
		if (!this->empty) return "Turntable occupied!";
		turnTableCar = car;
		empty = false;
		return "OK";
	}

	string removeCar() {
		if (this->empty) return "Turntable empty!";
		train_.push(turnTableCar);
		empty = true;
		return "OK";
	}

	string topCar() {
		if (this->empty) return "Turntable empty!";
		return turnTableCar.toString();
	}

	string sizeTrain() {
		ostringstream oss;
		oss << train_.size();
		return oss.str();
	}

	string addStack() {
		if (this->empty) return "Turntable empty!";
		stack_.push(turnTableCar);
		empty = true;
		return "OK";
	}

	string removeStack() {
		if (stack_.size() == 0) return "Stack empty!";
		if (!this->empty) return "Turntable occupied!";
		turnTableCar = stack_.top();
		stack_.pop();
		empty = false;
		return "OK";
	}

	string topStack() {
		if (stack_.size() == 0) return "Stack empty!";
		ostringstream oss;
		oss << stack_.top().toString();
		return oss.str();
	}

	string sizeStack() {
		ostringstream oss;
		oss << stack_.size() ;
		return oss.str();
	}

	string addQueue() {
		if (this->empty) return "Turntable empty!";
		queue_.push(turnTableCar);
		empty = true;
		return "OK";
	}

	string removeQueue() {
		if (queue_.size() == 0) return "Queue empty!";
		if (!this->empty) return "Turntable occupied!";
		turnTableCar = queue_.top();
		queue_.pop();
		empty = false;
		return "OK";
	}

	string topQueue() {
		if (queue_.size() == 0) return "Queue Empty!";
		string top = queue_.toString().substr(0, 1);
		return top;
	}

	string sizeQueue() {
		ostringstream oss;
		oss << queue_.size();
		return oss.str();
	}

	size_t sizeQueue(int d) {
		return queue_.size();
	}

	string outQueue() {
		return queue_.toString();
	}

	string outStack() {
		return stack_.toString();
	}

	string outTrain() {
		return train_.toString();
	}

	string find(T car) {
		ostringstream oss;
		if (turnTableCar == car && !empty) {
			oss << "Turntable";
			return oss.str();
		}
		for (unsigned i = 0; i < queue_.size(); ++i) {
			if (car == queue_.at(i)) {
				oss << "Queue[" << i << "]";
				return oss.str();
			}
		}
		for (unsigned i = 0; i < stack_.size(); ++i) {
			if (car == stack_.at(i)) {
				oss << "Stack[" << i << "]";
				return oss.str();
			}
		}
		for (unsigned i = 0; i < train_.size(); ++i) {
			if (car == train_.at(i)) {
				oss << "Train[" << i << "]";
				return oss.str();
			}
		}
		return "Not Found!";
	}

	string toString() const {

	}
};
#endif
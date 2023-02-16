#ifndef EXPRESSIONMANAGER_H_
#define EXPRESSIONMANAGER_H_

#include<stack>
#include<iomanip>
#include<fstream>
#include<string>
#include<sstream>
#include<iostream>
#include "ExpressionManagerInterface.h"

using namespace std;

class ExpressionManager : public ExpressionManagerInterface {
private:
	string expression;
public:
	ExpressionManager(void) : expression("") {}
	ExpressionManager(string expression) : expression(expression) {
	}

	void checkBalanced() {
		//cout << expression;
		istringstream iss(expression);
		string item;

		stack<string> stack;

		string err = "Unbalanced";

		while (iss >> item) {
			if (item == "(" || item == "[" || item == "{") {
				stack.push(item);
			}
			else if (item == ")") {
				if (stack.empty()) throw err;
				if (stack.top() == "(") {
					stack.pop();
					continue;
				}
				else throw err;
			}
			else if (item == "}") {
				if (stack.empty()) throw err;
				if (stack.top() == "{") {
					stack.pop();
					continue;
				}
				else throw err;
			}
			else if (item == "]") {
				if (stack.empty()) throw err;
				if (stack.top() == "[") {
					stack.pop();
					continue;
				}
				else throw err;
			}
		}
		if (!stack.empty()) throw err;
	}

	void checkNoError() {
		istringstream iss(expression);
		string item;

		stack<string> stack;

		string err;

		while (iss >> item) {
			if (item == "[" || item == "{" || item == "(" || item == ")" || item == "}" || item == "]") continue;
			else if (isdigit(item.at(0))) {
				if (stack.empty()) {
					stack.push(item);
				}
				else if (isdigit(stack.top().at(0))) {
					err = "Missing Operator";
					throw err;
				}
			}
			else if (item == "+" || item == "-" || item == "*" || item == "/" || item == "%") {
				if (stack.empty()) {
					err = "Missing Operand";
					throw err;
				}
				else if (isdigit(stack.top().at(0))) {
					stack.pop();
				}
			}
			else {
				err = "Illegal Operator";
				throw err;
			}
		}
		if (stack.empty()) {
			err = "Missing Operand";
			throw err;
		}
	}


	virtual ~ExpressionManager(void) {}

	/** Return the integer value of the infix expression */
	virtual int value(void) {
		string postfix = this->postfix();
		istringstream iss(postfix);
		string item;

		stack<string> stack;

		while (iss >> item) {
			if (isdigit(item.at(0))) stack.push(item);
			else {
				int op1 = stoi(stack.top());
				stack.pop();
				int op2 = stoi(stack.top());
				stack.pop();

				if (item == "+") stack.push(to_string(op2 + op1));
				else if (item == "-") stack.push(to_string(op2 - op1));
				else if (item == "/") stack.push(to_string(op2 / op1));
				else if (item == "*") stack.push(to_string(op2 * op1));
				else if (item == "%") stack.push(to_string(op2 % op1));
			}
		}
		return stoi(stack.top());
	}

	/** Return the infix items from the expression
		Throw an error if not a valid infix expression as follows:
		First check to see if the expression is balanced ("Unbalanced"),
		then throw the appropriate error immediately when an error is found
		(ie., "Missing Operand", "Illegal Operator", "Missing Operator") */
	virtual string infix(void) {
		checkBalanced();
		checkNoError();

		return this->toString();
	}

	/** Return a postfix representation of the infix expression */
	virtual string postfix(void) {
		string infix = this->infix();
		istringstream iss(infix);
		string item;

		ostringstream postfix;

		stack<string> stack;

		while (iss >> item) {
			if (isdigit(item.at(0))) postfix << item << " ";
			else if (item == "(" || item == "[" || item == "{" ) 
				stack.push(item);
			else if (item == "+" || item == "-") {
				if (stack.empty()) stack.push(item);
				else if (stack.top() == "(" || stack.top() == "[" || stack.top() == "{") stack.push(item);
				else if (stack.top() == "+" || stack.top() == "-" || stack.top() == "*" || stack.top() == "/" || stack.top() == "%") {
					while (!stack.empty() && (stack.top() == "+" || stack.top() == "-" || stack.top() == "*" || stack.top() == "/" || stack.top() == "%")) {
						postfix << stack.top() << " ";
						stack.pop();
					}
					stack.push(item);
				}
			}
			else if (item == "*" || item == "/" || item == "%") {
				if (stack.empty()) stack.push(item);
				else if (stack.top() == "(" || stack.top() == "[" || stack.top() == "{" || stack.top() == "+" || stack.top() == "-") stack.push(item);
				else if (stack.top() == "*" || stack.top() == "/" || stack.top() == "%") {
					postfix << stack.top() << " ";
					stack.pop();
					stack.push(item);
				}
			}
			else if (item == ")" || item == "]" || item == "}") {
				while (stack.top() != "(" && stack.top() != "[" && stack.top() != "{") {
					postfix << stack.top() << " ";
					stack.pop();
				}
				stack.pop();
			}
		}
		while (!stack.empty()) {
			postfix << stack.top() << " ";
			stack.pop();
		}

		return postfix.str();
	}

	/** Return a prefix representation of the infix expression */
	virtual string prefix(void) {
		string postfix = this->postfix();
		istringstream iss(postfix);
		string item;

		stack<string> stack;

		while (iss >> item) {
			if (isdigit(item.at(0))) stack.push(item);
			else {
				string one = stack.top();
				stack.pop();

				string two = stack.top();
				stack.pop();

				string toPush = " " + item + " " + two + " " + one;
				stack.push(toPush);
			}
		}
		string pre = stack.top();
		stack.pop();

		string next;
		ostringstream prefix;

		istringstream iss_2(pre);
		while (iss_2 >> next) {
			prefix << next << " ";
		}

		return prefix.str();
	}

	/** Return the infix vector'd expression items */
	virtual string toString(void) const {
		istringstream iss(expression);
		string item;

		ostringstream oss;

		while (iss >> item) {
			if (item != " ") {
				oss << item << " ";
			}
		}
		return oss.str();
	}
};
#endif

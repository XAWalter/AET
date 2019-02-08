#include <iostream>
#include <sstream>
#include <stack>
#include <cctype>	//to check if operator

#include "arithmeticExpression.h"

using namespace std;

arithmeticExpression::arithmeticExpression(const string &val) {
	root = NULL;
	infixExpression = val;
}

void arithmeticExpression::buildTree() {
	stack<TreeNode*> tmp;
	string postFix;
	TreeNode* node;
	char setKey = 'a';
	char check;

	postFix = infix_to_postfix();

	for (int i = 0; i < postFix.size(); i++) {

		check = postFix.at(i);

		if (isalnum(check)) {
			node = new TreeNode(check, setKey);
			setKey++;
			
			tmp.push(node);
		}
		else {
			node = new TreeNode(check, setKey);
			setKey++;

				node->right = tmp.top();
				tmp.pop();

				node->left = tmp.top();
				tmp.pop();


			tmp.push(node);
		}
	}

	root = tmp.top();
}

int arithmeticExpression::priority(char op) {
	int priority = 0;
	if (op == '(') {
		priority = 3;
	}
	else if (op == '*' || op == '/') {
		priority = 2;
	}
	else if (op == '+' || op == '-') {
		priority = 1;
	}
	return priority;
}

string arithmeticExpression::infix_to_postfix() {
	stack<char> s;
	ostringstream oss;
	char c;
	for (unsigned i = 0; i < infixExpression.size(); ++i) {
		c = infixExpression.at(i);
		if (c == ' ') {
			continue;
		}
		if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')') { //c is an operator
			if (c == '(') {
				s.push(c);
			}
			else if (c == ')') {
				while (s.top() != '(') {
					oss << s.top();
					s.pop();
				}
				s.pop();
			}
			else {
				while (!s.empty() && priority(c) <= priority(s.top())) {
					if (s.top() == '(') {
						break;
					}
					oss << s.top();
					s.pop();
				}
				s.push(c);
			}
		}
		else { //c is an operand
			oss << c;
		}
	}
	while (!s.empty()) {
		oss << s.top();
		s.pop();
	}
	return oss.str();
}

void arithmeticExpression::infix() {
	infix(root);
	cout << endl;
}

void arithmeticExpression::prefix() {
	prefix(root);
	cout << endl;
}

void arithmeticExpression::postfix() {
	postfix(root);
	cout << endl;
}

void arithmeticExpression::infix(TreeNode *a) {
	if (a != NULL) {
		infix(a->left);
		cout << a->data << " ";
		infix(a->right);
	}
}

void arithmeticExpression::prefix(TreeNode *a) {
	if (a != NULL) {
		cout << a->data << " ";
		prefix(a->left);
		prefix(a->right);
	}
}

void arithmeticExpression::postfix(TreeNode *a) {
	if (a != NULL) {
		postfix(a->left);
		postfix(a->right);
		cout << a->data << " ";
	}
}

//void arithmeticExpression::visualizeTree(const string &outputFilename) {
//	ofstream outFS(outputFilename.c_str());
//	if (!outFS.is_open()) {
//		cout << "Error opening " << outputFilename << endl;
//		return;
//	}
//	outFS << "digraph G {" << endl;
//	visualizeTree(outFS, root);
//	outFS << "}";
//	outFS.close();
//	string jpgFilename = outputFilename.substr(0, outputFilename.size() - 4) + ".jpg";
//	string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
//	system(command.c_str());
//}
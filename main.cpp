/*
 * Author: Naim Miah
 * Date: ~~~
 * Project Description: Converts infix expression to postfix expression and then evaluates it. If you wish just to postfix, its
 * not hard to make adjustments.
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <stack>
#include <limits>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;


int eval(int op1, int op2, string c) {
    char *cOperate = new char[c.length() + 1];
    strcpy(cOperate, c.c_str());
    cout << *cOperate << endl;
    switch (*cOperate) {
        case '*':
            delete[] cOperate;
            return op2 * op1;
        case '/':
             delete[] cOperate;
            return op2 / op1;
        case '+':
            delete[] cOperate;
            return op2 + op1;
        case '-':
            delete[] cOperate;
            return op2 - op1;
        default :
            delete[] cOperate;
            return 0;
    }
    
}
// lets be smart about this
template <typename T>
bool isOperator(T c) {
    return c == "+" || c == "-" || c == "/" || c == "*" || c == "^" || c == "(" || c == ")";
}

int evalEquation(vector<string> v) {
    stack<int> s;
    int val = 0;
    for (int i = (v.size()-1); i > -1; i--) {
        string tempS = v[i];
        if (isOperator(tempS)) {
            int op1 = s.top();
            s.pop();
            int op2 = s.top();
            s.pop();
            val = eval(op1, op2, tempS);
            s.push(val);
        }  else {
            int tempValue1 = atoi(tempS.c_str());
            s.push(tempValue1);
            //cout << s.top() << endl;
        }
    }
    
    return val;
}
//I think this was important
int lengthfunction(int number)
{
    int counter=0;
    while(number)
    {
        number=number/10;
        counter++;
    }
    return (counter);
}
int priority(char a) {
    int temp;
    if (a == '^')
        temp = 1;
    else  if (a == '*' || a == '/')
        temp = 2;
    else  if (a == '+' || a == '-')
        temp = 3;
    return temp;
}

int main() {
    string infix;
    int counter = 0;
    vector<string> v;
    while (true) {
        cout << setw(40) << "Nahid's CALULACTOR" << endl;
        cout << "Enter an arithmetic expression(Press . to exit): " << endl;
        cin >> infix;
        
        stack<char> operator_stack;
        stack<string> operatend_stack;
        string temp;
        stringstream output;
        stringstream stream(std::stringstream::in | std::stringstream::out);
        stream << infix;
        int operand1;
        char op;
        
        for (unsigned i = 0; i < infix.length(); i++) {
            if(infix[i] == '.')
                return 0;
            // not in the mood to write two different functions, its retarded
            if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/' || infix[i] == '^') {
                while (!operator_stack.empty() && priority(operator_stack.top()) <= priority(infix[i])) {
                    temp = operator_stack.top();
                    output << operator_stack.top();
                    operatend_stack.push(temp);
                    operator_stack.pop();
                }
                operator_stack.push(infix[i]);
                stream >> op;
                counter++;
            } else if (infix[i] == '(') {
                operator_stack.push(infix[i]);
                stream >> op;
                ++counter;
            } else if (infix[i] == ')') {
                while (operator_stack.top() != '(') {
                    temp = operator_stack.top();
                    output << operator_stack.top();
                    operatend_stack.push(temp);
                    operator_stack.pop();
                }
                stream >> op;
                counter++;
                operator_stack.pop();
            } else {
                if(i == counter) {
                    stream >> operand1;
                    temp = to_string(operand1);
                    operatend_stack.push(temp);
                    counter = counter + lengthfunction(operand1);
                }
                output << infix[i];
            }
        }
        
        while (!operator_stack.empty()) {
            temp = operator_stack.top();
            output << operator_stack.top();
            operatend_stack.push(temp);
            operator_stack.pop();
        }
        while (!operatend_stack.empty()) {
            v.push_back(operatend_stack.top());
            operatend_stack.pop();
        }
        
        cout << setw(20) << "Answer\n" << evalEquation(v) << endl;
        
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return 0;
}

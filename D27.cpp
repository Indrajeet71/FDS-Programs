/*
Implement C++ program for expression conversion as infix to postfix and its evaluation using stack based on given conditions:
1. Operands and operator, both must be single character.
2. Input Postfix expression must be in a desired format.
3. Only '+', '-', '*' and '/ ' operators are expected.
*/

#include <iostream>
using namespace std;

class Node
{
private:
    char op;
    Node *prev;

public:
    Node(char op, Node *prev) : op(op), prev(prev) {}
    char getOp() { return this->op; }
    Node *getPrev() { return prev; }
    void setPrev(Node *prev) { this->prev = prev; }
};

class Stack
{
private:
    Node *head;

public:
    Stack() : head(nullptr) {}
    void push(char op)
    {
        Node *nNode = new Node(op, this->head);
        this->head = nNode;
    }
    char top()
    {
        return this->head->getOp();
    }
    char pop()
    {
        char op = this->head->getOp();
        Node *node = this->head;
        this->head = this->head->getPrev();
        delete node;
        return op;
    }
    bool isEmpty()
    {
        return this->head == nullptr;
    }
    ~Stack()
    {
        while (this->head != nullptr)
        {
            Node *node = this->head;
            this->head = this->head->getPrev();
            delete node;
        }
    }
};

class Expression
{
public:
    static string infixToPostfix(string infix)
    {
        string postfix = "";
        Stack *s = new Stack();
        for (int i = 0; i < infix.length(); i++)
        {
            if (infix[i] == ' ')
                continue;
            else if (infix[i] != '+' && infix[i] != '-' && infix[i] != '*' && infix[i] != '/')
                postfix += infix[i];
            else if ((infix[i] == '*' || infix[i] == '/') && (s->isEmpty() || s->top() == '+' || s->top() == '-'))
                s->push(infix[i]);
            else
            {
                while ((!s->isEmpty() && (infix[i] == '+' || infix[i] == '-')) || (!s->isEmpty() && (infix[i] == '*' || infix[i] == '/') && (s->top() == '*' || s->top() == '/')))
                    postfix += s->pop();
                s->push(infix[i]);
            }
        }
        while (!s->isEmpty())
            postfix += s->pop();
        delete s;
        return postfix;
    }
};

int main(void)
{
    string exp;
    cout << "Enter expression\t:\t";
    getline(cin, exp);
    cout << Expression::infixToPostfix(exp) << "\n";
    return 0;
}
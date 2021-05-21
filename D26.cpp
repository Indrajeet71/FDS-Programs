/*
In any language program mostly syntax error occurs due to unbalancing delimiter such as (),{},[]. Write C++ program using stack to check whether given expression is well parenthesized or not.
*/

#include <iostream>
#include <exception>
using namespace std;

class InvalidParenthesisException : public exception
{
public:
    const char *what() const throw()
    {
        return "Parenthesis mismatch";
    }
};

class Node
{
private:
    char bracket;
    Node *prev;

public:
    Node(char bracket, Node *prev) : bracket(bracket), prev(prev) {}
    char getBracket() { return this->bracket; }
    Node *getPrev() { return prev; }
    void setPrev(Node *prev) { this->prev = prev; }
};

class Stack
{
private:
    Node *head;

public:
    Stack() : head(nullptr) {}
    void push(char bracket)
    {
        Node *nNode = new Node(bracket, this->head);
        this->head = nNode;
    }
    char top()
    {
        return this->head->getBracket();
    }
    char pop()
    {
        char bracket = this->head->getBracket();
        Node *node = this->head;
        this->head = this->head->getPrev();
        delete node;
        return bracket;
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
    static bool checkExpression(string exp)
    {
        Stack *s = new Stack();
        try
        {
            for (int i = 0; i < exp.length(); i++)
            {
                if (exp[i] == '(' || exp[i] == '[' || exp[i] == '{')
                    s->push(exp[i]);
                else if (exp[i] == ')' || exp[i] == ']' || exp[i] == '}')
                {
                    if (exp[i] == ')' && s->top() == '(')
                        s->pop();
                    else if (exp[i] == ']' && s->top() == '[')
                        s->pop();
                    else if (exp[i] == '}' && s->top() == '{')
                        s->pop();
                    else
                        throw InvalidParenthesisException();
                }
            }
        }
        catch (exception e)
        {
            return false;
        }
        return true;
    }
};

int main(void)
{
    string exp;
    cout << "Enter expression\t:\t";
    getline(cin, exp);
    string message = Expression::checkExpression(exp) ? "Expression has valid parenthesis." : "Expression has invalid parenthesis.";
    cout << message << "\n";
    return 0;
}
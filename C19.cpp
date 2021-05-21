/*
Department of Computer Engineering has student's club named 'Pinnacle Club'. Students of  second,  third  and  final  year  of  department can  be  granted  membership  on  request. Similarly one may cancel the membership of club. First node is reserved for president of club and last node is reserved for secretary of club. Write C++ program to maintain club member‘s information using singly linkedlist.  Store  student  PRN  and  Name.  Write functions to:
a)Add and delete the members as well as president or even secretary.
b)Compute total number of members of club
c)Display members
d)Two linked lists exists for two divisions. Concatenate two lists.
*/

#include <iostream>
using namespace std;

class Exception
{
private:
    string message;

public:
    Exception(string message) : message(message) {}
    string getErrorMessage() { return this->message; }
};

class EmptyListException : public Exception
{
public:
    EmptyListException(string message) : Exception("EmptyListException : " + message) {}
};

class Member
{
private:
    static int count;
    int PRN;
    string name;
    string role;

public:
    Member(string name, string role) : PRN(++count), name(name), role(role) {}
    string toString()
    {
        char buffer[100];
        sprintf(buffer, "Member {\n\tPRN\t:\t%d\n\tName\t:\t%s\n\tRole\t:\t%s\n}", this->PRN, this->name.c_str(), this->role.c_str());
        return buffer;
    }
};
int Member::count = 0;

class Node
{
private:
    Member *data;
    Node *next;

public:
    Node(Member *data, Node *next) : data(data), next(next) {}
    Member *getMember() { return data; }
    Node *getNext() { return next; }
    void setNext(Node *next) { this->next = next; }
    ~Node() { delete this->data; }
};

class SinglyLinkedList
{
private:
    Node *tail;
    Node *head;
    int count;

public:
    SinglyLinkedList() : tail(nullptr), head(nullptr), count(0) {}
    Member *pop()
    {
        if (this->head == nullptr)
            throw EmptyListException("List is empty");
        Member *data = this->head->getMember();
        this->head = this->head->getNext();
        this->count--;
        return data;
    }
    Member *top()
    {
        if (this->head == nullptr)
            throw EmptyListException("List is empty");
        return this->head->getMember();
    }
    void push(Member *data)
    {
        if (this->head == nullptr)
            this->tail = this->head = new Node(data, nullptr);
        else
        {
            this->tail->setNext(new Node(data, nullptr));
            this->tail = this->tail->getNext();
        }
        this->count++;
    }
    void printList()
    {
        cout << "Members [";
        for (Node *iter = this->head; iter; iter = iter->getNext())
            cout << "\n"
                 << iter->getMember()->toString() << "\n";
        cout << "]\n";
    }
    int getCount() { return this->count; }
    void append(SinglyLinkedList other)
    {
        this->tail->setNext(other.head);
        this->tail = other.tail;
    }
    void clear()
    {
        Node *iter = this->head;
        while (iter)
        {
            Node *next = iter->getNext();
            delete iter;
            iter = next;
        }
        this->tail = this->head = nullptr;
        this->count = 0;
    }
    ~SinglyLinkedList() { this->clear(); }
};

class PinnacleClubUtils
{
public:
    static int menu()
    {
        cout << "Select a option :\n";
        cout << "0. Exit\n";
        cout << "1. Push\n";
        cout << "2. Pop\n";
        cout << "3. Top\n";
        cout << "4. Print Members\n";
        cout << "5. Print Count\n";
        cout << "6. Clear List\n";
        int choice;
        cout << "Enter choice\t:\t";
        cin >> choice;
        if (choice < 0 || choice > 6)
        {
            cout << "Invalid choice. Please try again.\n\n\n";
            choice = PinnacleClubUtils::menu();
        }
        return choice;
    }
    static Member *getMember()
    {
        string name, role;
        cout << "Enter Name\t:\t";
        cin >> name;
        cout << "Enter Role\t:\t";
        cin >> role;
        return new Member(name, role);
    }
};

int main(void)
{
    SinglyLinkedList *members = new SinglyLinkedList();
    while (true)
    {
        int choice = PinnacleClubUtils::menu();
        if (choice == 0)
            break;
        switch (choice)
        {
        case 1:
            members->push(PinnacleClubUtils::getMember());
            break;
        case 2:
            try
            {
                Member *member = members->pop();
                cout << member->toString() << "\n";
                delete member;
            }
            catch (Exception e)
            {
                cerr << e.getErrorMessage() << "\n";
            }
            break;
        case 3:
            try
            {
                cout << members->top()->toString() << "\n";
            }
            catch (Exception e)
            {
                cerr << e.getErrorMessage() << "\n";
            }
            break;
        case 4:
            members->printList();
            break;
        case 5:
            cout << "Total members\t:\t" << members->getCount() << "\n";
            break;
        case 6:
            members->clear();
            cout << "List cleared.\n";
            break;
        default:
            break;
        }
        cout << "\n\n";
    }
    delete members;
    return 0;
}
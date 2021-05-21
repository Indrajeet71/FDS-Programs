/*
Write C++ program for storing appointment schedule for day. Appointments are booked randomly using linked list. Set start and end time and min and max duration for visit slot. Write functions for-
a) Display free slots
b) Book appointment
c) Cancel appointment ( check validity, time bounds, availability)
d) Sort list based on time
e) Sort list based on time using pointer manipulation
*/

#include <iostream>
#include <exception>
using namespace std;

class Exception
{
private:
    string message;

public:
    Exception(string message) : message(message) {}
    string getErrorMessage() { return this->message; }
};

class EmptyListException : public exception
{
public:
    const char *what() const throw()
    {
        return "List is empty";
    }
};

class InvalidHoursException : public exception
{
public:
    const char *what() const throw()
    {
        return "Select working hours (9 to 21)";
    }
};

class InvalidMinutesException : public exception
{
public:
    const char *what() const throw()
    {
        return "Select 0 or 30 mins only";
    }
};

class AppointmentUnavailableException : public exception
{
public:
    const char *what() const throw()
    {
        return "Appointment slot already taken";
    }
};

class Appointment
{
private:
    string name;
    int hour, minute;

public:
    Appointment(string name, int hour, int minute) : name(name), hour(hour), minute(minute) {}
    int getHour() { return this->hour; }
    int getMinute() { return this->minute; }
    string toString()
    {
        char buffer[100];
        sprintf(buffer, "Appointment {\n\tName\t:\t%s\n\tTime\t:\t%d:%s\n}", this->name.c_str(), this->hour, this->minute == 0 ? "00" : "30");
        return buffer;
    }
};

class Node
{
private:
    Appointment *data;
    Node *next;

public:
    Node(Appointment *data, Node *next) : data(data), next(next) {}
    Appointment *getAppointment() { return data; }
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
    Appointment *pop()
    {
        if (this->head == nullptr)
            throw EmptyListException();
        Appointment *data = this->head->getAppointment();
        this->head = this->head->getNext();
        this->count--;
        return data;
    }
    Appointment *top()
    {
        if (this->head == nullptr)
            throw EmptyListException();
        return this->head->getAppointment();
    }
    void push(Appointment *data)
    {
        Node *nNode = new Node(data, nullptr);
        if (this->head == nullptr)
            this->tail = this->head = nNode;
        else
        {
            if ((nNode->getAppointment()->getHour() * 100 + nNode->getAppointment()->getMinute()) < (head->getAppointment()->getHour() * 100 + head->getAppointment()->getMinute()))
            {
                nNode->setNext(this->head);
                this->head = nNode;
            }
            else if ((nNode->getAppointment()->getHour() * 100 + nNode->getAppointment()->getMinute()) == (head->getAppointment()->getHour() * 100 + head->getAppointment()->getMinute()))
                throw AppointmentUnavailableException();
            else
            {
                Node *iter = nullptr;
                for (iter = this->head; iter->getNext() != nullptr && (nNode->getAppointment()->getHour() * 100 + nNode->getAppointment()->getMinute()) < (iter->getNext()->getAppointment()->getHour() * 100 + iter->getNext()->getAppointment()->getMinute()); iter = iter->getNext())
                    if ((nNode->getAppointment()->getHour() * 100 + nNode->getAppointment()->getMinute()) == (iter->getNext()->getAppointment()->getHour() * 100 + iter->getNext()->getAppointment()->getMinute()))
                        throw AppointmentUnavailableException();
                nNode->setNext(iter->getNext());
                iter->setNext(nNode);
            }
        }
        this->count++;
    }
    void printAppointmentSlots()
    {
        Node *iter = this->head;
        cout << "Available appointment slots :\n";
        for (int h = 9; h < 22; h++)
        {
            bool available = true;
            while (iter)
            {
                if (iter->getAppointment()->getHour() == h && iter->getAppointment()->getMinute() == 0)
                {
                    available = false;
                    break;
                }
                iter = iter->getNext();
            }
            if (available)
                cout << h << ":00\t";
            available = true;
            while (iter)
            {
                if (iter->getAppointment()->getHour() == h && iter->getAppointment()->getMinute() == 30)
                {
                    available = false;
                    break;
                }
                iter = iter->getNext();
            }
            if (available)
                cout << h << ":30\t";
        }
        cout << "\n";
    }
    void printList()
    {
        cout << "Appointments [";
        for (Node *iter = this->head; iter; iter = iter->getNext())
            cout << "\n"
                 << iter->getAppointment()->toString() << "\n";
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

class AppointmentUtils
{
private:
    static int getHour()
    {
        int h;
        try
        {
            cout << "Enter hour\t:\t";
            cin >> h;
            if (h < 9 || h > 21)
                throw InvalidHoursException();
        }
        catch (const exception &e)
        {
            cerr << e.what() << '\n';
            h = getHour();
        }
        return h;
    }
    static int getMinute()
    {
        int m;
        try
        {
            cout << "Enter minute\t:\t";
            cin >> m;
            if (m != 0 && m != 30)
                throw InvalidMinutesException();
        }
        catch (const exception &e)
        {
            cerr << e.what() << '\n';
            m = getMinute();
        }
        return m;
    }

public:
    static int menu()
    {
        cout << "Select a option :\n";
        cout << "0. Exit\n";
        cout << "1. Book appointment\n";
        cout << "2. Pop\n";
        cout << "3. Top\n";
        cout << "4. Print Appointments\n";
        cout << "5. Print Count\n";
        cout << "6. Clear List\n";
        cout << "7. Print Available slots\n";
        int choice;
        cout << "Enter choice\t:\t";
        cin >> choice;
        if (choice < 0 || choice > 7)
        {
            cout << "Invalid choice. Please try again.\n\n\n";
            choice = AppointmentUtils::menu();
        }
        return choice;
    }
    static Appointment *getAppointment()
    {
        string name;
        cout << "Enter name\t:\t";
        cin >> name;
        return new Appointment(name, getHour(), getMinute());
    }
};

int main(void)
{
    SinglyLinkedList *appointments = new SinglyLinkedList();
    while (true)
    {
        int choice = AppointmentUtils::menu();
        if (choice == 0)
            break;
        switch (choice)
        {
        case 1:
            try
            {
                appointments->push(AppointmentUtils::getAppointment());
            }
            catch (const exception &e)
            {
                cerr << e.what() << '\n';
                cerr << "Appointment not booked\n";
            }

            break;
        case 2:
            try
            {
                Appointment *appointment = appointments->pop();
                cout << appointment->toString() << "\n";
                delete appointment;
            }
            catch (Exception e)
            {
                cerr << e.getErrorMessage() << "\n";
            }
            break;
        case 3:
            try
            {
                cout << appointments->top()->toString() << "\n";
            }
            catch (Exception e)
            {
                cerr << e.getErrorMessage() << "\n";
            }
            break;
        case 4:
            appointments->printList();
            break;
        case 5:
            cout << "Total appointments\t:\t" << appointments->getCount() << "\n";
            break;
        case 6:
            appointments->clear();
            cout << "List cleared.\n";
            break;
        case 7:
            appointments->printAppointmentSlots();
            break;
        default:
            break;
        }
        cout << "\n\n";
    }
    delete appointments;
    return 0;
}
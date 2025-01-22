// A) Design a ticket booking system where customers arrive to book tickets and join a queue. The system should process customers in a first-come, first-served (FIFO) manner. The queue must provide the following operations (options) to the user: 1. Add Customer -> Add a new customer to the booking queue. 2. Process Booking -> Process the ticket booking for the current customer in line and remove them from the queue after processing. 3. View Queue -> Display the current list of customers waiting in the queue. The system should simulate real-life ticket booking, where customers are served in the order of arrival. B) Name the data structure used for the ticket booking system. Example (Expected Output): --- Welcome to ABC Ticket Booking System -- 1. Add Customer 2. Process Booking 3. View Queue Enter Your Choice (1-3): 1 Enter Customer Name: Virat Customer Virat has joined the queue. Enter Your Choice (1-3): 1 Enter Customer Name: Rohit Customer Rohit has joined the queue. Enter Your Choice (1-3): 3 Current Queue: Virat -> Rohit Enter Your Choice (1-3): 2 Booking processed for customer: Virat Enter Your Choice (1-3): 3 Current Queue: Rohit



#include <iostream>
#include <string>
using namespace std;

class Node {
    public:
        string data;
        Node* next;
        Node(string data) {
            this->data = data;
            this->next = NULL;
        }
};

class Queue {
    private:
        Node* front;
        Node* rear;
    public:
        Queue() {
            front = NULL;
            rear = NULL;
        }
        void enqueue(string data) {
            Node* newNode = new Node(data);
            if (rear == NULL) {
                front = newNode;
                rear = newNode;
            } else {
                rear->next = newNode;
                rear = newNode;
            }
        }
        string dequeue() {
            if (front == NULL) {
                return "";
            }
            Node* temp = front;
            front = front->next;
            string data = temp->data;
            delete temp;
            return data;
        }
        void display() {
            Node* temp = front;
            while (temp != NULL) {
                cout << temp->data;
                if (temp->next != NULL) {
                    cout << "-> ";
                }
                temp = temp->next;
            }
            cout << endl;
        }
};

int main() {
    Queue queue;
    int choice;
    string name;
    do {
        cout << "--- Welcome to ABC Ticket Booking System ---" << endl;
        cout << "1. Add Customer" << endl;
        cout << "2. Process Booking" << endl;
        cout << "3. View Queue" << endl;
        cout << "Enter Your Choice (1-3): ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter Customer Name: ";
                cin >> name;
                queue.enqueue(name);
                cout << "Customer " << name << " has joined the queue." << endl;
                break;
            case 2:
                name = queue.dequeue();
                if (name == "") {
                    cout << "Queue is empty." << endl;
                } else {
                    cout << "Booking processed for customer: " << name << endl;
                }
                break;
            case 3:
                cout << "Current Queue: ";
                queue.display();
                break;
            default:
                cout << "Invalid choice. Please enter a valid choice (1-3)." << endl;
        }
    } while (choice != 0);
    return 0;
}

// B) name the data structure used for ticket booking system
// A) Queue 
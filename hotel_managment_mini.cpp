#include <iostream>
#include <string>
using namespace std;

//----------------- NODE STRUCTURES ----------------//
struct RoomType {
    string type;
    int price;
    RoomType *left, *right;
};

struct Customer {
    int roomNo;
    string name;
    string roomType;
    Customer *next;
};

//----------------- GLOBALS ----------------//
Customer* head = nullptr; // Linked List Head
RoomType* root = nullptr; // BST Root

const int MAX = 10;
int front = -1, rear = -1;
int availableRooms[MAX];

// Stack for checkout history
string checkoutHistory[50];
int top = -1;

//----------------- QUEUE FUNCTIONS ----------------//
bool isFull() { return (rear == MAX - 1); }
bool isEmpty() { return (front == -1 || front > rear); }

void enqueue(int roomNo) {
    if (isFull()) return;
    if (front == -1) front = 0;
    availableRooms[++rear] = roomNo;
}

int dequeue() {
    if (isEmpty()) return -1;
    return availableRooms[front++];
}

//----------------- STACK FUNCTIONS ----------------//
void pushHistory(string name) {
    if (top < 49) checkoutHistory[++top] = name;
}

void showHistory() {
    if (top == -1) {
        cout << "No checkout history yet.\n";
        return;
    }
    cout << "\n--- Checkout History (Recent First) ---\n";
    for (int i = top; i >= 0; i--) cout << checkoutHistory[i] << endl;
}

//----------------- BST FUNCTIONS ----------------//
RoomType* insertRoomType(RoomType* root, string type, int price) {
    if (!root) {
        RoomType* newNode = new RoomType{type, price, nullptr, nullptr};
        return newNode;
    }
    if (type < root->type)
        root->left = insertRoomType(root->left, type, price);
    else if (type > root->type)
        root->right = insertRoomType(root->right, type, price);
    return root;
}

void inorder(RoomType* root) {
    if (root) {
        inorder(root->left);
        cout << root->type << " - Rs." << root->price << endl;
        inorder(root->right);
    }
}

//----------------- LINKED LIST FUNCTIONS ----------------//
void addCustomer(int roomNo, string name, string type) {
    Customer* newCust = new Customer{roomNo, name, type, nullptr};
    if (!head) head = newCust;
    else {
        Customer* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = newCust;
    }
}

void showCustomers() {
    if (!head) {
        cout << "No customers currently checked-in.\n";
        return;
    }
    cout << "\n--- Current Guests ---\n";
    Customer* temp = head;
    while (temp) {
        cout << "Room: " << temp->roomNo << " | Name: " << temp->name 
             << " | Type: " << temp->roomType << endl;
        temp = temp->next;
    }
}

void removeCustomer(int roomNo) {
    if (!head) return;
    Customer *temp = head, *prev = nullptr;

    if (head->roomNo == roomNo) {
        pushHistory(head->name);
        head = head->next;
        delete temp;
        return;
    }

    while (temp && temp->roomNo != roomNo) {
        prev = temp;
        temp = temp->next;
    }

    if (temp) {
        pushHistory(temp->name);
        prev->next = temp->next;
        delete temp;
    }
}

//----------------- MAIN SYSTEM FUNCTIONS ----------------//
void checkIn() {
    if (isEmpty()) {
        cout << "No rooms available!\n";
        return;
    }

    int roomNo = dequeue();
    string name, type;
    cout << "Enter customer name: ";
    cin >> ws;
    getline(cin, name);
    cout << "Enter room type (Standard/Deluxe/Suite): ";
    cin >> type;
    addCustomer(roomNo, name, type);
    cout << "Check-in successful! Room " << roomNo << " allocated.\n";
}

void checkOut() {
    int roomNo;
    cout << "Enter room number to checkout: ";
    cin >> roomNo;
    removeCustomer(roomNo);
    enqueue(roomNo);
    cout << "Checkout successful! Room " << roomNo << " is now available.\n";
}

//----------------- DRIVER CODE ----------------//
int main() {
    // Initialize room queue
    for (int i = 101; i <= 110; i++) enqueue(i);

    // Insert room types in BST
    root = insertRoomType(root, "Standard", 2000);
    root = insertRoomType(root, "Deluxe", 3500);
    root = insertRoomType(root, "Suite", 6000);

    int choice;
    do {
        cout << "\n===== HOTEL MANAGEMENT SYSTEM =====\n";
        cout << "1. Show Room Types\n";
        cout << "2. Show Available Rooms\n";
        cout << "3. Check-in Customer\n";
        cout << "4. Check-out Customer\n";
        cout << "5. View Current Guests\n";
        cout << "6. View Checkout History\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: inorder(root); break;
            case 2:
                if (isEmpty()) cout << "No available rooms.\n";
                else {
                    cout << "\n--- Available Rooms ---\n";
                    for (int i = front; i <= rear; i++)
                        cout << availableRooms[i] << " ";
                    cout << endl;
                }
                break;
            case 3: checkIn(); break;
            case 4: checkOut(); break;
            case 5: showCustomers(); break;
            case 6: showHistory(); break;
            case 0: cout << "Exiting system...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}

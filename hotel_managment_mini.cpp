#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// Node for customer record (Linked List)
struct Customer {
    int roomNumber;
    string name;
    int days;
    double bill;
    Customer* next;
};

// Hotel Management Class
class Hotel {
private:
    Customer* head;

public:
    Hotel() {
        head = NULL;
    }

    // Book a room (Insert at end of Linked List)
    void bookRoom(int room, string cname, int days, double pricePerDay) {
        Customer* newCustomer = new Customer();
        newCustomer->roomNumber = room;
        newCustomer->name = cname;
        newCustomer->days = days;
        newCustomer->bill = days * pricePerDay;
        newCustomer->next = NULL;

        if (head == NULL) {
            head = newCustomer;
        } else {
            Customer* temp = head;
            while (temp->next != NULL)
                temp = temp->next;
            temp->next = newCustomer;
        }

        cout << "\n✅ Room " << room << " booked for " << cname 
             << " for " << days << " days. Bill = " << newCustomer->bill << endl;
    }

    // Search by room number
    void searchRoom(int room) {
        Customer* temp = head;
        while (temp != NULL) {
            if (temp->roomNumber == room) {
                cout << "\n🔎 Room Found!\n";
                cout << "Room Number: " << temp->roomNumber << "\nName: " << temp->name
                     << "\nDays: " << temp->days << "\nBill: " << temp->bill << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "\n❌ Room not found!\n";
    }

    // Display all bookings
    void displayAll() {
        if (head == NULL) {
            cout << "\n⚠️ No bookings available!\n";
            return;
        }
        cout << "\n--- Hotel Records ---\n";
        Customer* temp = head;
        while (temp != NULL) {
            cout << "Room " << temp->roomNumber << " | Name: " << temp->name
                 << " | Days: " << temp->days << " | Bill: " << temp->bill << endl;
            temp = temp->next;
        }
    }

    // Checkout (Delete node from Linked List)
    void checkout(int room) {
        if (head == NULL) {
            cout << "\n⚠️ No records!\n";
            return;
        }

        Customer* temp = head;
        Customer* prev = NULL;

        while (temp != NULL && temp->roomNumber != room) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == NULL) {
            cout << "\n❌ Room not found!\n";
            return;
        }

        if (prev == NULL) {
            head = head->next;
        } else {
            prev->next = temp->next;
        }

        cout << "\n✅ Checkout successful for Room " << room 
             << ". Bill Paid = " << temp->bill << endl;
        delete temp;
    }
};

// Main Menu
int main() {
    Hotel h;
    int choice, room, days;
    string name;
    double pricePerDay = 1000.0; // fixed rate

    do {
        cout << "\n===== Hotel Management System =====";
        cout << "\n1. Book Room";
        cout << "\n2. Search Room";
        cout << "\n3. Display All Records";
        cout << "\n4. Checkout";
        cout << "\n5. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter Room Number: ";
            cin >> room;
            cout << "Enter Customer Name: ";
            cin >> name;
            cout << "Enter Number of Days: ";
            cin >> days;
            h.bookRoom(room, name, days, pricePerDay);
            break;

        case 2:
            cout << "Enter Room Number to Search: ";
            cin >> room;
            h.searchRoom(room);
            break;

        case 3:
            h.displayAll();
            break;

        case 4:
            cout << "Enter Room Number to Checkout: ";
            cin >> room;
            h.checkout(room);
            break;

        case 5:
            cout << "\n👋 Exiting... Thank you!\n";
            break;

        default:
            cout << "\n⚠️ Invalid Choice!\n";
        }
    } while (choice != 5);

    return 0;
}

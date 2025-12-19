#include <iostream>
#include <string>
using namespace std;

const int TOTAL_SEATS = 30;

/* Singly Linked List Node */
struct Passenger {
    int seatNo;
    string name;
    int age;
    char gender;
    Passenger* next;
};

/* Global Head Pointer */
Passenger* head = NULL;

/* Function Declarations */
void bookTicket(int seats[]);
void cancelTicket(int seats[]);
void viewTrainStatus(int seats[]);
void viewPassengerList();
void freeMemory(int seats[]);

/* Main Function */
int main() {
    int choice;

    // Dynamic allocation for seat status array
    int* seats = new int[TOTAL_SEATS];

    // Initialize all seats as available
    for (int i = 0; i < TOTAL_SEATS; i++)
        seats[i] = 0;

    do {
        cout << "\n===== Railway Reservation System =====\n";
        cout << "1. Book Ticket\n";
        cout << "2. Cancel Ticket\n";
        cout << "3. View Train Status\n";
        cout << "4. View Passenger List\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                bookTicket(seats);
                break;
            case 2:
                cancelTicket(seats);
                break;
            case 3:
                viewTrainStatus(seats);
                break;
            case 4:
                viewPassengerList();
                break;
            case 5:
                freeMemory(seats);
                cout << "Program exited successfully.\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 5);

    return 0;
}

/* Book Ticket */
void bookTicket(int seats[]) {
    int seatNo = -1;

    // Find first available seat
    for (int i = 0; i < TOTAL_SEATS; i++) {
        if (seats[i] == 0) {
            seatNo = i + 1;
            break;
        }
    }

    if (seatNo == -1) {
        cout << "Sorry! No seats available.\n";
        return;
    }

    Passenger* newPassenger = new Passenger;

    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, newPassenger->name);

    cout << "Enter Age: ";
    cin >> newPassenger->age;

    cout << "Enter Gender (M/F): ";
    cin >> newPassenger->gender;

    newPassenger->seatNo = seatNo;
    newPassenger->next = head;
    head = newPassenger;

    seats[seatNo - 1] = 1;

    cout << "Ticket booked! Seat No: " << seatNo << endl;
}

/* Cancel Ticket */
void cancelTicket(int seats[]) {
    int seatNo;
    cout << "Enter Seat Number to cancel: ";
    cin >> seatNo;

    Passenger* temp = head;
    Passenger* prev = NULL;

    while (temp != NULL && temp->seatNo != seatNo) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        cout << "No booking found for this seat number.\n";
        return;
    }

    if (prev == NULL)
        head = temp->next;
    else
        prev->next = temp->next;

    seats[seatNo - 1] = 0;
    delete temp;

    cout << "Ticket cancelled successfully.\n";
}

/* View Train Status */
void viewTrainStatus(int seats[]) {
    cout << "\n----- Train Status -----\n";
    for (int i = 0; i < TOTAL_SEATS; i++) {
        cout << "Seat " << i + 1 << ": ";
        if (seats[i] == 1)
            cout << "Booked\n";
        else
            cout << "Available\n";
    }
}

/* View Passenger List */
void viewPassengerList() {
    if (head == NULL) {
        cout << "No passengers booked yet.\n";
        return;
    }

    Passenger* temp = head;
    cout << "\n----- Passenger List -----\n";
    while (temp != NULL) {
        cout << "Seat No: " << temp->seatNo
             << " | Name: " << temp->name
             << " | Age: " << temp->age
             << " | Gender: " << temp->gender << endl;
        temp = temp->next;
    }
}

/* Free All Allocated Memory */
void freeMemory(int seats[]) {
    Passenger* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        delete temp;
    }
    delete[] seats;
}

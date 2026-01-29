#include "../Functions/functions.h"

void registrationMenu() {
    cout << "\tWhat do you want to register for?\n\t\t0) Close The Registrations\n\t\t1) Bank Registration\n\t\t2) vehicle Registration" << endl;

    int choice;
    cin >> choice;

    if (choice == 0) { //Recursion Base Case
        cout << "Thank you for Registering!" << endl;
        return;
    } else if (choice == 1) {
        cout << "Bank Registration Selected" << endl;

        string owner, email, password, address;
        
        cout << "Enter Your Name: ";
        cin >> owner;
        cout << "Enter Your email: ";
        cin >> email;
        cout << "Select a password: ";
        cin >> password;
        cout << "Enter Your address: ";
        cin >> address;

        accRegistration(owner, email, password, address);
    } else if (choice == 2) {
        cout << "vehicle Registration Selected" << endl;

        string vehicleNum, owner, email, address;
        int wheels;
        
        cout << "Enter Your Name: ";
        cin >> owner;
        cout << "Enter Your vehicle Number: ";
        cin >> vehicleNum;
        cout << "Enter Your vehicle Type(2-Wheels, 4-Wheels): ";
        cin >> wheels;
        cout << "Enter Your email: ";
        cin >> email;
        cout << "Enter Your address: ";
        cin >> address;

        vehicleRegistration(vehicleNum, wheels, owner, email, address);
    } else {
        cout << "Invalid Choice! Try Again" << endl;
    }

    registrationMenu(); //Recursiive Call
}

int main() {
    cout << "\tWelcome to Registration Form!" << endl;

    registrationMenu();

    return 0;
}
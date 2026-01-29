#include "../Functions/functions.h"

void adminControls(string admin) {
    cout << "\tAdmin Controls\n\t\t0) Close Admin Dashboard\n\t\t1) View Bank Accounts\n\t\t2) View Registered Vehicles \n\t\t3) View Issued Challans" << endl;

    int choice;
    cin >> choice;

    if (choice == 0) { //Recursion Base Case
        cout << "Admin Dashboard Closed" << endl;
        return;
    } else if (choice == 1) {
        cout << "*****Bank Accounts*****" << endl;

        try {
            string file = "./Finances/Accounts.json";
            
            int rows, cols;
            getSize(file, rows, cols);

            string **arr = new string*[rows];
            for (int i = 0; i < rows; i++)
                arr[i] = new string[cols];

            toArray(file, arr, rows, cols);

            for(int i = 0;i < rows;i++) {
                for(int j = 0;j < cols;j++) {
                    cout << "\t" << arr[i][j] << "\t"; 
                }
                cout << "\n--------------------------------------------------------------------------------------------------------------" << endl;
            }

            for (int i = 0; i < rows; i++)
                delete[] arr[i];
            delete[] arr;
        } catch(...) {
            cout << "No Accounts Registered at the Moment!" << endl;
        }

    } else if (choice == 2) {
        cout << "*****Registered Vehicles*****" << endl;

        try{
            string file = "./Challans/Vehicle Registration.json";
            
            int rows, cols;
            getSize(file, rows, cols);

            string **arr = new string*[rows];
            for (int i = 0; i < rows; i++)
                arr[i] = new string[cols];

            toArray(file, arr, rows, cols);

            for(int i = 0;i < rows;i++) {
                for(int j = 0;j < cols;j++) {
                    cout << "\t" << arr[i][j] << "\t"; 
                }
                cout << "\n--------------------------------------------------------------------------------------------------------------" << endl;
            }

            for (int i = 0; i < rows; i++)
                delete[] arr[i];
            delete[] arr;
        } catch(...) {
            cout << "No Vehicles Registered at this Moment!" << endl;
        }

    } else if (choice == 3) {
        cout << "*****Issued Challans*****" << endl;

        try{
            string file = "./Challans/Challans.json";
            
            int rows, cols;
            getSize(file, rows, cols);

            string **arr = new string*[rows];
            for (int i = 0; i < rows; i++)
                arr[i] = new string[cols];

            toArray(file, arr, rows, cols);

            for(int i = 0;i < rows;i++) {
                for(int j = 0;j < cols;j++) {
                    cout << "\t" << arr[i][j] << "\t"; 
                }
                cout << "\n--------------------------------------------------------------------------------------------------------------" << endl;
            }

            for (int i = 0; i < rows; i++)
                delete[] arr[i];
            delete[] arr;
        } catch(...) {
            cout << "No Challans at the Moment!" << endl;
        }

    } else {
        cout << "Invalid Choice! Try Again" << endl;
    }
    adminControls(admin); //Recursiive Call
}

int main() {
    cout << "\tADMIN CONTROLS" << endl;

    string admin, password;

    cout << "Enter Admin Username: ";
    cin >> admin;

    try{
        if(adminExist(admin)) {
            cout << "Enter Password: ";
            cin >> password;
            
            if(adminLogin(admin, password)) {
                adminControls(admin);
            } else {
                cout << "Incorrect Password, Login Failed!" << endl;
            }
        } else {
            cout << "No Admin with Username " << admin << endl;
        }
    } catch(...) {
        cout << "No Admin at this Moment!" << endl;
    }

    return 0;
}
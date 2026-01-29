#include "../Functions/functions.h"

void bankMenu(string email) {
    cout << "\tWhat type of Transaction you want to do?\n\t\t0) Close The Bank\n\t\t1) Deposit Money\n\t\t2) Credit Money\n\t\t3) Pay Challan" << endl;

    int choice;
    cin >> choice;

    if (choice == 0) { //Recursion Base Case
        cout << "Thank you for Using our Bank!" << endl;
        return;
    } else if (choice == 1) {
        cout << "Money Deposit Selected!" << endl;

        int deposit;
        
        cout << "Enter the amount of Money you want to Deposit: ";
        cin >> deposit;

        moneyDeposit(email, deposit);
        sendEmailAsync(email, "Money Deposit Notification", "An amount of " + to_string(deposit) + " is deposited in your account!");
    } else if (choice == 2) {
        cout << "Money Credit Selected!" << endl;

        int credit;
        
        cout << "Enter the amount of Money you want to Credit: ";
        cin >> credit;

        moneyCredit(email, credit);
    } else if (choice == 3) {
        cout << "Challan Payment Selected!" << endl;

        string accounts = "./Finances/Accounts.json", challans = "./Challans/Challans.json";

            try {
                int rowAcc, colAcc, rowCh, colCh;
                getSize(accounts, rowAcc, colAcc);
                getSize(challans, rowCh, colCh);

                string **acc = new string*[rowAcc];
                for (int i = 0; i < rowAcc; i++)
                    acc[i] = new string[colAcc];

                string **challan = new string*[rowCh];
                for (int i = 0; i < rowCh; i++)
                    challan[i] = new string[colCh];

                toArray(accounts, acc, rowAcc, colAcc);
                toArray(challans, challan, rowCh, colCh);

                payment(email, acc, rowAcc, challan, rowCh);

                for (int i = 0; i < rowAcc; i++)
                    delete[] acc[i];
                delete[] acc;

                for (int i = 0; i < rowCh; i++)
                    delete[] challan[i];
                delete[] challan;
            } catch(...) {
                cout << "No Challans at the Moment!" << endl;
                sendEmailAsync(email, "Challan Payment", "You Currently have No Challans!");
            }

    } else {
        cout << "Invalid Choice! Try Again" << endl;
    }

    bankMenu(email); //Recursiive Call
}

int main() {
    cout << "\tWelcome to Pseudo-Bank!" << endl;

    string email, password;

    cout << "Enter Your E-Mail you have given to Bank: ";
    cin >> email;

    try {
        if(accExist(email)) {
            cout << "Enter your Bank Password: ";
            cin >> password;
            
            if(bankLogin(email, password)) {
                bankMenu(email);
            } else {
                cout << "Incorrect Password, Login Failed!" << endl;
            }
        } else {
            cout << "Account Does not Exist. Please Register First!" << endl;
        }
    } catch(...) {
        cout << "No Accounts Registered at the Moment!" << endl;
    }

    return 0;
}

#include <bits/stdc++.h>
using namespace std;

class Transaction
{
public:
    int transactionId;
    string type;
    double amount;
    string details;

    Transaction(int id, string t, double a, string d)
    {
        transactionId = id;
        type = t;
        amount = a;
        details = d;
    }

    void display()
    {
        cout << "Transaction ID: " << transactionId
             << " | Type: " << type
             << " | Amount: " << fixed << setprecision(2)
             << amount
             << " | Details: " << details << endl;
    }
};

class Customer
{
public:
    int customerId;
    string name;
    string phone;

    Customer(int id, string n, string p)
    {
        customerId = id;
        name = n;
        phone = p;
    }

    void displayCustomer()
    {
        cout << "Customer ID: " << customerId << endl;
        cout << "Name: " << name << endl;
        cout << "Phone: " << phone << endl;
    }
};

class Account
{
public:
    int accountNumber;
    double balance;
    Customer customer;
    vector<Transaction> history;

    static int nextTransactionId;

    Account(int accNo, Customer c, double initialBalance)
        : customer(c)
    {
        accountNumber = accNo;

        if (initialBalance >= 0)
            balance = initialBalance;
        else
            balance = 0;
    }

    void addTransaction(string type, double amount,
                        string details)
    {
        history.push_back(
            Transaction(nextTransactionId++, type,
                        amount, details)
        );
    }

    void deposit(double amount)
    {
        if (amount <= 0)
        {
            cout << "Invalid amount!\n";
            return;
        }

        balance += amount;

        addTransaction("Deposit", amount,
                       "Money deposited");

        cout << "Deposit successful!\n";
        cout << "Current Balance: " << balance << endl;
    }

    void withdraw(double amount)
    {
        if (amount <= 0)
        {
            cout << "Invalid amount!\n";
            return;
        }

        if (amount > balance)
        {
            cout << "Insufficient balance!\n";
            return;
        }

        balance -= amount;

        addTransaction("Withdrawal", amount,
                       "Money withdrawn");

        cout << "Withdrawal successful!\n";
        cout << "Current Balance: " << balance << endl;
    }

    void transfer(Account &receiver, double amount)
    {
        if (accountNumber == receiver.accountNumber)
        {
            cout << "Cannot transfer to the same account!\n";
            return;
        }

        if (amount <= 0)
        {
            cout << "Invalid amount!\n";
            return;
        }

        if (amount > balance)
        {
            cout << "Insufficient balance!\n";
            return;
        }

        balance -= amount;
        receiver.balance += amount;

        addTransaction("Transfer Out", amount,
                       "To account " +
                       to_string(receiver.accountNumber));

        receiver.addTransaction("Transfer In", amount,
                                "From account " +
                                to_string(accountNumber));

        cout << "Transfer successful!\n";
        cout << "Your Current Balance: " << balance << endl;
    }

    void showAccount()
    {
        cout << "\n===== ACCOUNT INFORMATION =====\n";

        customer.displayCustomer();

        cout << "Account Number: " << accountNumber << endl;
        cout << "Balance: " << fixed << setprecision(2)
             << balance << endl;
    }

    void showRecentTransactions(int n)
    {
        cout << "\n===== RECENT TRANSACTIONS =====\n";

        if (n <= 0)
        {
            cout << "Enter a valid transaction count!\n";
            return;
        }

        if (history.empty())
        {
            cout << "No transactions found.\n";
            return;
        }

        int start = max(0, (int)history.size() - n);

        for (int i = start; i < (int)history.size(); i++)
        {
            history[i].display();
        }
    }
};

int Account::nextTransactionId = 1;

int main()
{
    Customer c1(101, "Roysul", "01700000000");
    Customer c2(102, "Rahim", "01800000000");

    Account a1(1001, c1, 5000);
    Account a2(1002, c2, 3000);

    int choice;
    double amount;

    do
    {
        cout << "\n===== BANK MANAGEMENT SYSTEM =====\n";
        cout << "1. Show Account Information\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Transfer Money\n";
        cout << "5. Recent Transactions\n";
        cout << "6. Show Receiver Account\n";
        cout << "0. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            a1.showAccount();
            break;

        case 2:
            cout << "Enter deposit amount: ";
            cin >> amount;
            a1.deposit(amount);
            break;

        case 3:
            cout << "Enter withdrawal amount: ";
            cin >> amount;
            a1.withdraw(amount);
            break;

        case 4:
            cout << "Enter transfer amount: ";
            cin >> amount;
            a1.transfer(a2, amount);
            break;

        case 5:
        {
            int n;
            cout << "How many recent transactions? ";
            cin >> n;
            a1.showRecentTransactions(n);
            break;
        }

        case 6:
            a2.showAccount();
            break;

        case 0:
            cout << "Thank you for using our system!\n";
            break;

        default:
            cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 0);

    return 0;
}

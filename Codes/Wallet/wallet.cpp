#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Account
{
protected:
    string account_number;
    double balance;

public:
    Account(string acc_number, double initial_balance)
        : account_number(acc_number), balance(initial_balance) {}

    virtual void deposit(double amount)
    {
        if (amount > 0)
        {
            balance += amount;
        }
    }

    virtual bool withdraw(double amount)
    {
        if (amount > 0 && balance - amount >= 0)
        {
            balance -= amount;
            return true;
        }
        return false;
    }

    virtual void add(double amounttoadd)
    {
        balance += amounttoadd;
    }

    virtual void accountStatement() const
    {
        cout << "Account statement for " << account_number << ":" << endl;
        cout << "Balance: " << balance << endl;
    }

    string getAccountNumber() const
    {
        return account_number;
    }

    double getBalance() const
    {
        return balance;
    }

    virtual ~Account() {}
};

class Wallet : public Account
{
private:
    double fd_amount;
    int fd_remaining_transactions;

public:
    Wallet(string acc_number, double initial_balance)
        : Account(acc_number, initial_balance), fd_amount(0), fd_remaining_transactions(0) {}

    double getFixedDepositAmount() const
    {
        return fd_amount;
    }

    int getRemainingFDTransactions() const
    {
        return fd_remaining_transactions;
    }

    void createFixedDeposit(double amount, int num_transactions)
    {
        if (amount > 0)
        {
            fd_amount = amount;
            fd_remaining_transactions = num_transactions;
        }
    }

    void add(double amounttoadd) override
    {
        Account::add(amounttoadd);
        cout << "Added amount: " << amounttoadd << " successfully." << endl;
        double updated = getBalance();
        cout << "Updated Balance:" << updated << endl;
        return;
        
    }

    bool withdraw(double amount) override
    {
        if (Account::withdraw(amount))
        {
            cout << "Withdrawn amount: " << amount << " successfully." << endl;
            double rem = getBalance();
            cout << "Remaining Balance:" << rem << endl;
            return true;
        }
        else
        {
            cout << "Errx! Insufficient Balance." << endl;
            return false;
        }
    }

    void accountStatement() const override
    {
        Account::accountStatement();
        cout << "Fixed deposit amount: " << fd_amount << endl;
        cout << "Remaining FD transactions: " << fd_remaining_transactions << endl;
    }
};

class WalletSystem
{
private:
    vector<Account *> accounts;

public:
    ~WalletSystem()
    {
        for (auto &account : accounts)
        {
            delete account;
        }
    }

    void createWallet(string account_number, double initial_balance)
    {
        for (auto &account : accounts)
        {
            if (account->getAccountNumber() == account_number)
            {
                cout << "Account already exists!" << endl;
                return;
            }
        }
        Wallet *wallet = new Wallet(account_number, initial_balance);
        accounts.push_back(wallet);
        cout << "Wallet created successfully!" << endl;
    }

    Account *findAccountByAccountNumber(string account_number)
    {
        for (auto &account : accounts)
        {
            if (account->getAccountNumber() == account_number)
            {
                return account;
            }
        }
        return nullptr;
    }

    void transferAmount(string sender_account_number, string receiver_account_number, double amount)
    {
        Account *sender_account = findAccountByAccountNumber(sender_account_number);
        Account *receiver_account = findAccountByAccountNumber(receiver_account_number);

        if (!sender_account || !receiver_account)
        {
            cout << "Invalid account numbers." << endl;
            return;
        }

        if (sender_account->withdraw(amount))
        {
            receiver_account->deposit(amount);

            if (sender_account->getBalance() == receiver_account->getBalance())
            {
                sender_account->deposit(10);
                receiver_account->deposit(10);
            }

            cout << "Amount transferred successfully!" << endl;
        }
        else
        {
            cout << "Transfer failed." << endl;
        }
    }

    void accountStatement(string account_number)
    {
        Account *account = findAccountByAccountNumber(account_number);

        if (!account)
        {
            cout << "Account not found." << endl;
            return;
        }

        account->accountStatement();
    }

    void overview()
    {
        cout << "Overview of all accounts:" << endl;
        for (const Account *account : accounts)
        {
            account->accountStatement();
            cout << endl;
        }
    }

    void fixedDeposit(string account_number, double amount)
    {
        Account *account = findAccountByAccountNumber(account_number);

        if (!account)
        {
            cout << "Account not found." << endl;
            return;
        }

        if (amount < 0.0001)
        {
            cout << "The fixed deposit amount must be greater than 0.0001 F₹." << endl;
            return;
        }

        if (dynamic_cast<Wallet *>(account)->getFixedDepositAmount() > 0)
        {
            cout << "You already have a fixed deposit." << endl;
            return;
        }

        dynamic_cast<Wallet *>(account)->createFixedDeposit(amount, 5);
        cout << "Fixed deposit created successfully!" << endl;
    }

    void addamount(string account_number, double amount)
    {
        Account *account = findAccountByAccountNumber(account_number);
        if (!account)
        {
            cout << "Account not found!" << endl;
            return;
        }
        account->add(amount);
    }

    void withdrawamount(string account_number , double amount)
    {
        Account *account = findAccountByAccountNumber(account_number);
        if(!account)
        {
            cout<<"Account not found!"<<endl;
            return;
        }
        account->withdraw(amount);
    }
};



int main()
{
    WalletSystem walletSystem;
    int choice;

    do
    {
        cout << endl;
        cout << "Select an option:" << endl;
        cout << "1. Create wallet" << endl;
        cout << "2. Transfer amount" << endl;
        cout << "3. Account statement" << endl;
        cout << "4. Overview" << endl;
        cout << "5. Fixed deposit" << endl;
        cout << "6. Add amount" << endl;
        cout << "7. Withdraw amount" << endl;
        cout << "8. Exit" << endl;

        cout << endl;

        cin >> choice;

        string account_number, sender_account_number, receiver_account_number;
        double initial_balance, transfer_amount, fd_amount, add_amount, withdraw_amount;

        switch (choice)
        {
        case 1:
            cout << "Enter your account number: ";
            cin >> account_number;
            cout << "Enter your initial balance: ";
            cin >> initial_balance;
            walletSystem.createWallet(account_number, initial_balance);
            break;
        case 2:
            cout << "Enter the sender's account number: ";
            cin >> sender_account_number;
            cout << "Enter the receiver's account number: ";
            cin >> receiver_account_number;
            cout << "Enter the amount to transfer: ";
            cin >> transfer_amount;
            walletSystem.transferAmount(sender_account_number, receiver_account_number, transfer_amount);
            break;
        case 3:
            cout << "Enter the account number: ";
            cin >> account_number;
            walletSystem.accountStatement(account_number);
            break;
        case 4:
            walletSystem.overview();
            break;
        case 5:
            cout << "Enter the account number: ";
            cin >> account_number;
            cout << "Enter the fixed deposit amount: ";
            cin >> fd_amount;
            walletSystem.fixedDeposit(account_number, fd_amount);
            break;
        case 6:
            cout << "Enter Account Number: ";
            cin >> account_number;
            cout << "Enter Amount to be added: ";
            cin >> add_amount;
            walletSystem.addamount(account_number, add_amount);
            break;
        case 7:
            cout << "Enter Account Number: ";
            cin >> account_number;
            cout << "Enter Amount to withdraw: ";
            cin >> withdraw_amount;
            walletSystem.withdrawamount(account_number, withdraw_amount);
            break;
        case 8:
            cout << "Exiting program." << endl;
            return 0;

        default:
            cout << "Invalid option." << endl;
        }
    } while (choice != 8);

    return 0;
}

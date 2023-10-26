#include <iostream>
#include <vector>
#include <map>
#include <iomanip>
#include <sstream>

using namespace std;

class User
{
public:
    string userId;
    string name;
    string email;
    string mobile;
};

class Expense
{
public:
    string paidBy;
    vector<string> participants;
    string expenseType;
    double totalAmount;
    vector<double> shares;
};

class ExpenseManager
{
private:
    vector<User> users;
    vector<Expense> expenses;
    map<string, double> balances;
    map<string, map<string, double>> detailedBalances; // New map for detailed balances

public:
    void addUser(const User &user)
    {
        users.push_back(user);
        balances[user.userId] = 0.0;
    }

    void addExpense(const Expense &expense)
    {
        expenses.push_back(expense);
        if (expense.expenseType == "EQUAL")
        {
            double share = expense.totalAmount / expense.participants.size();
            for (const string &participant : expense.participants)
            {
                balances[participant] += share;
                balances[expense.paidBy] -= share;
                if(participant!=expense.paidBy)
                detailedBalances[participant][expense.paidBy] += share; // Update detailed balances
            }
        }
        else if (expense.expenseType == "EXACT")
        {
            for (int i = 0; i < expense.participants.size(); ++i)
            {
                balances[expense.participants[i]] += expense.shares[i];
                balances[expense.paidBy] -= expense.shares[i];
                if(expense.participants[i]!=expense.paidBy)
                    detailedBalances[expense.participants[i]][expense.paidBy] += expense.shares[i]; // Update detailed balances
            }
        }
        else if (expense.expenseType == "PERCENT")
        {
            double totalPercent = 0.0;
            for (double percent : expense.shares)
            {
                totalPercent += percent;
            }
            for (int i = 0; i < expense.participants.size(); ++i)
            {
                double share = (expense.shares[i] / totalPercent) * expense.totalAmount;
                balances[expense.participants[i]] += share;
                balances[expense.paidBy] -= share;
                if(expense.participants[i]!=expense.paidBy)
                detailedBalances[expense.participants[i]][expense.paidBy] += share; // Update detailed balances
            }
        }
    }

    void showBalance(const string &userId)
    {
        if (userId.empty())
        {
            cout << "Overall Balances:" << endl;
            for (const auto &entry : balances)
            {
                if (entry.second < 0.0)
                {
                    cout << entry.first << " To Collect: " << fixed << setprecision(2) << -entry.second << endl;
                }
                else
                cout << entry.first << " owes: " << fixed << setprecision(2) << entry.second << endl;
            }
        }
        else
        {
            cout << userId << "'s Detailed Balances:" << endl;
            for (const auto &entry : detailedBalances[userId])
            {
                cout << userId << " owes " << entry.first << ": " << fixed << setprecision(2) << entry.second << endl;
            }
        }
    }
};

int main()
{
    cout<<endl;

    ExpenseManager expenseManager;

    cout<<"--------------Welcome to Splitwise---------------";
    cout<<endl;
    cout<<endl;
    cout<<"Enter Number of Users: ";
    int num;
    cin>>num;
    User userArray[num];

     for (int i = 0; i < num; i++)
    {
        string userId = "u" + to_string(i + 1);

        cout << "Enter Name of user " << i + 1 << ": ";
        string username, useremail, userphone;
        cin >> username;

        cout << "Enter E-mail of user " << i + 1 << ": ";
        cin >> useremail;

        cout << "Enter Phone of user " << i + 1 << ": ";
        cin >> userphone;

        User user = {userId, username, useremail, userphone};
        userArray[i] = user;

        expenseManager.addUser(user);
        cout<<endl;
    }

    cout << "Users added successfully!" << endl;

    int numExpenses;
    cout << "Enter the number of expenses: ";
    cin >> numExpenses;
    cin.ignore(); // Clear newline from input buffer

    for (int i = 0; i < numExpenses; ++i)
    {
        Expense expense;
        string input;
        cout << "Enter expense details for expense " << i + 1 << ": ";
        getline(cin, input);
        stringstream ss(input);

        ss >> expense.paidBy >> expense.totalAmount;
        int numParticipants;
        ss >> numParticipants;

        expense.participants.resize(numParticipants);
        for (int j = 0; j < numParticipants; ++j)
        {
            ss >> expense.participants[j];
        }

        ss >> expense.expenseType;
        if (expense.expenseType == "EQUAL")
        {
            // No shares to read for EQUAL
        }
        else if (expense.expenseType == "EXACT")
        {
            expense.shares.resize(numParticipants);
            for (int j = 0; j < numParticipants; ++j)
            {
                ss >> expense.shares[j];
            }
        }
        else if (expense.expenseType == "PERCENT")
        {
            expense.shares.resize(numParticipants);
            for (int j = 0; j < numParticipants; ++j)
            {
                ss >> expense.shares[j];
            }
        }

        expenseManager.addExpense(expense);
    }

    cout << "Expenses added successfully!" << endl;

    string userId;
    cout << "Enter user id for balance check (or type 'SHOW SHOW' for all balances): ";
    while (cin >> userId)
    {
        if (userId == "exit")
            return 0;
        if (userId == "SHOW")
        {
            cin >> userId;
            if (userId == "SHOW")
            {
                expenseManager.showBalance("");
            }
            else
            {
                expenseManager.showBalance(userId);
            }
        }
    }

    return 0;
}

#include <iostream>
#include <vector>
#include <map>
#include <iomanip>
#include <sstream>

using namespace std;

class User {
public: 
    string userId;
    string name;
    string email;
    string mobile;
};

class Expense {
public:
    string paidBy;
    vector<string> participants;
    string expenseType;
    double totalAmount;
    vector<double> shares;
};

class ExpenseManager {
private:
    vector<User> users;
    vector<Expense> expenses;
    map<string, double> balances;

public:
    void addUser(const User& user) {
        users.push_back(user);
        balances[user.userId] = 0.0;
    }

    void addExpense(const Expense& expense) {
        expenses.push_back(expense);
        if (expense.expenseType == "EQUAL") {
            double share = expense.totalAmount / expense.participants.size();
            for (const string& participant : expense.participants) {
                balances[participant] += share;
                balances[expense.paidBy] -= share;
            }
        }
        else if (expense.expenseType == "EXACT") {
            for (int i = 0; i < expense.participants.size(); ++i) {
                balances[expense.participants[i]] += expense.shares[i];
                balances[expense.paidBy] -= expense.shares[i];
            }
        }
        else if (expense.expenseType == "PERCENT") {
            double totalPercent = 0.0;
            for (double percent : expense.shares) {
                totalPercent += percent;
            }
            for (int i = 0; i < expense.participants.size(); ++i) {
                double share = (expense.shares[i] / totalPercent) * expense.totalAmount;
                balances[expense.participants[i]] += share;
                balances[expense.paidBy] -= share;
            }
        }
    }

    void showBalance(const string& userId) {
        for (const auto& entry : balances) {
            if (entry.second != 0.0 && entry.first != userId) {
                cout << userId << " owes " << entry.first << ": " << fixed << setprecision(2) << entry.second << endl;
            }
        }
    }
};

int main() {
    ExpenseManager expenseManager;

    // Add users
    User u1 = {"u1", "User1", "user1@example.com", "1234567890"};
    User u2 = {"u2", "User2", "user2@example.com", "9876543210"};
    User u3 = {"u3", "User3", "user3@example.com", "5555555555"};
    User u4 = {"u4", "User4", "user4@example.com", "9999999999"};

    expenseManager.addUser(u1);
    expenseManager.addUser(u2);
    expenseManager.addUser(u3);
    expenseManager.addUser(u4);

    int numExpenses;
    cin >> numExpenses;
    cin.ignore(); // Clear newline from input buffer

    for (int i = 0; i < numExpenses; ++i) {
        Expense expense;
        string input;
        getline(cin, input);
        stringstream ss(input);

        ss >> expense.paidBy >> expense.totalAmount;
        int numParticipants;
        ss >> numParticipants;

        expense.participants.resize(numParticipants);
        for (int j = 0; j < numParticipants; ++j) {
            ss >> expense.participants[j];
        }

        ss >> expense.expenseType;
        if (expense.expenseType == "EQUAL") {
            // No shares to read for EQUAL
        }
        else if (expense.expenseType == "EXACT") {
            expense.shares.resize(numParticipants);
            for (int j = 0; j < numParticipants; ++j) {
                ss >> expense.shares[j];
            }
        }
        else if (expense.expenseType == "PERCENT") {
            expense.shares.resize(numParticipants);
            for (int j = 0; j < numParticipants; ++j) {
                ss >> expense.shares[j];
            }
        }

        expenseManager.addExpense(expense);
    }

    string userId;
    while (cin >> userId) {
        if (userId == "SHOW") {
            cin >> userId;
            if (userId == "SHOW") {
                expenseManager.showBalance("");
            } else {
                expenseManager.showBalance(userId);
            }
        }
    }
    return 0;
}

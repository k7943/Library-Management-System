#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

class Transaction {
public:
    string bookID;
    string memberID;
    string issueDate;
    string returnDate;
    double fine;

    Transaction() {}

    Transaction(string bID, string mID, string issue, string ret, double f)
        : bookID(bID), memberID(mID), issueDate(issue), returnDate(ret), fine(f) {}

    void display() const {
        cout << "Book ID: " << bookID
             << "\nMember ID: " << memberID
             << "\nIssue Date: " << issueDate
             << "\nReturn Date: " << returnDate
             << "\nFine: ₹" << fine << "\n\n";
    }

    string toCSV() const {
        return bookID + "," + memberID + "," + issueDate + "," + returnDate + "," + to_string(fine);
    }

    static Transaction fromCSV(const string& line) {
        stringstream ss(line);
        string bID, mID, issue, ret, fineStr;
        getline(ss, bID, ',');
        getline(ss, mID, ',');
        getline(ss, issue, ',');
        getline(ss, ret, ',');
        getline(ss, fineStr, ',');

        return Transaction(bID, mID, issue, ret, stod(fineStr));
    }
};

vector<Transaction> transactions;

// Add new transaction
void addTransaction(const string& bookID, const string& memberID, const string& issueDate, const string& returnDate, double fine) {
    transactions.emplace_back(bookID, memberID, issueDate, returnDate, fine);
}

// View all transactions
void viewTransactions() {
    if (transactions.empty()) {
        cout << "No transactions recorded.\n";
        return;
    }
    for (const Transaction& t : transactions) {
        t.display();
    }
}

// Save transactions to file
void saveTransactions(const string& filename) {
    ofstream file(filename);
    for (const Transaction& t : transactions) {
        file << t.toCSV() << "\n";
    }
    file.close();
}

// Load transactions from file
void loadTransactions(const string& filename) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        transactions.push_back(Transaction::fromCSV(line));
    }
    file.close();
}

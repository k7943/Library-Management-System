#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <sstream>
#include "book.cpp"
#include "member.cpp"
using namespace std;

struct Transaction {
    string bookID;
    string memberID;
    string issueDate;
    string returnDate;
    double fine;

    string toCSV() const {
        return bookID + "," + memberID + "," + issueDate + "," + returnDate + "," + to_string(fine);
    }
};

vector<Transaction> transactions;

string getCurrentDate() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    stringstream ss;
    ss << setfill('0') << setw(2) << ltm->tm_mday << "-"
       << setfill('0') << setw(2) << 1 + ltm->tm_mon << "-"
       << 1900 + ltm->tm_year;
    return ss.str();
}

int dateDifference(const string& issueDate, const string& returnDate) {
    tm tm1{}, tm2{};
    istringstream(issueDate) >> get_time(&tm1, "%d-%m-%Y");
    istringstream(returnDate) >> get_time(&tm2, "%d-%m-%Y");

    time_t t1 = mktime(&tm1);
    time_t t2 = mktime(&tm2);
    if (t1 == -1 || t2 == -1) return 0;

    double seconds = difftime(t2, t1);
    return static_cast<int>(seconds / (60 * 60 * 24));
}

// Issue book
void issueBook() {
    string bookID, memberID;
    cout << "Enter Book ID to issue: ";
    getline(cin, bookID);
    cout << "Enter Member ID: ";
    getline(cin, memberID);

    // Find book
    Book* book = nullptr;
    for (Book& b : books) {
        if (b.bookID == bookID) {
            book = &b;
            break;
        }
    }
    if (!book || book->availableCopies <= 0) {
        cout << "Book not available.\n";
        return;
    }

    // Find member
    Member* member = nullptr;
    for (Member& m : members) {
        if (m.memberID == memberID) {
            member = &m;
            break;
        }
    }
    if (!member) {
        cout << "Member not found.\n";
        return;
    }

    // Proceed to issue
    book->availableCopies--;
    string today = getCurrentDate();
    transactions.push_back({bookID, memberID, today, "NA", 0.0});
    cout << "Book issued on " << today << ". Please return within 14 days.\n";
}

// Return book
void returnBook() {
    string bookID, memberID;
    cout << "Enter Book ID to return: ";
    getline(cin, bookID);
    cout << "Enter Member ID: ";
    getline(cin, memberID);

    // Find the last unreturned transaction
    for (Transaction& t : transactions) {
        if (t.bookID == bookID && t.memberID == memberID && t.returnDate == "NA") {
            string today = getCurrentDate();
            int days = dateDifference(t.issueDate, today);
            double fine = max(0, days - 14) * 2.0;
            t.returnDate = today;
            t.fine = fine;

            // Update book and member
            for (Book& b : books) {
                if (b.bookID == bookID) {
                    b.availableCopies++;
                    break;
                }
            }
            for (Member& m : members) {
                if (m.memberID == memberID) {
                    m.fineAmount += fine;
                    break;
                }
            }

            cout << "Book returned on " << today << ". Fine: ₹" << fine << "\n";
            return;
        }
    }

    cout << "No matching issue record found.\n";
}

// Save transactions
void saveTransactions(const string& filename) {
    ofstream file(filename);
    for (const Transaction& t : transactions) {
        file << t.toCSV() << "\n";
    }
    file.close();
}

// Load transactions
void loadTransactions(const string& filename) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string bID, mID, issue, ret, fineStr;
        getline(ss, bID, ',');
        getline(ss, mID, ',');
        getline(ss, issue, ',');
        getline(ss, ret, ',');
        getline(ss, fineStr, ',');
        Transaction t = {bID, mID, issue, ret, stod(fineStr)};
        transactions.push_back(t);
    }
    file.close();
}

#include <iostream>
#include <unordered_map>
#include <vector>
#include <iomanip>
#include <sstream>
#include "book.cpp"
#include "member.cpp"
#include "transaction.cpp"
using namespace std;

string getCurrentDate() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    stringstream ss;
    ss << setfill('0') << setw(2) << ltm->tm_mday << "-"
       << setfill('0') << setw(2) << 1 + ltm->tm_mon << "-"
       << 1900 + ltm->tm_year;
    return ss.str();
}

// Helper: Check if a transaction is still active
bool isIssued(const Transaction& t) {
    return t.returnDate == "NA";
}

// Helper: Check if overdue (assumes returnDate is "NA")
bool isOverdue(const string& issueDate, const string& today) {
    tm tm1{}, tm2{};
    istringstream(issueDate) >> get_time(&tm1, "%d-%m-%Y");
    istringstream(today) >> get_time(&tm2, "%d-%m-%Y");
    time_t t1 = mktime(&tm1);
    time_t t2 = mktime(&tm2);
    return difftime(t2, t1) > 14 * 24 * 3600; // 14 days in seconds
}

// Report 1: List of currently issued books
void reportIssuedBooks() {
    cout << "\n📘 Currently Issued Books:\n";
    bool found = false;
    for (const Transaction& t : transactions) {
        if (isIssued(t)) {
            cout << "Book ID: " << t.bookID << " | Member ID: " << t.memberID << " | Issued on: " << t.issueDate << "\n";
            found = true;
        }
    }
    if (!found) cout << "No books are currently issued.\n";
}

// Report 2: List of overdue books
void reportOverdueBooks() {
    cout << "\n⌛ Overdue Books:\n";
    string today = getCurrentDate();
    bool found = false;
    for (const Transaction& t : transactions) {
        if (isIssued(t) && isOverdue(t.issueDate, today)) {
            cout << "Book ID: " << t.bookID << " | Member ID: " << t.memberID
                 << " | Issued on: " << t.issueDate << " | Status: OVERDUE\n";
            found = true;
        }
    }
    if (!found) cout << "No overdue books.\n";
}

// Report 3: Most borrowed books
void reportMostBorrowedBooks() {
    unordered_map<string, int> freq;
    for (const Transaction& t : transactions) {
        freq[t.bookID]++;
    }

    vector<pair<string, int>> sorted;
    for (auto& [id, count] : freq) {
        sorted.emplace_back(id, count);
    }

    sort(sorted.begin(), sorted.end(), [](auto& a, auto& b) {
        return a.second > b.second;
    });

    cout << "\n🔝 Most Borrowed Books:\n";
    if (sorted.empty()) {
        cout << "No borrowing data available.\n";
        return;
    }

    for (int i = 0; i < min(5, (int)sorted.size()); ++i) {
        cout << i + 1 << ". Book ID: " << sorted[i].first << " | Times Borrowed: " << sorted[i].second << "\n";
    }
}

// Report 4: Member-wise borrowing history
void reportMemberHistory() {
    string memberID;
    cout << "Enter Member ID: ";
    getline(cin, memberID);

    cout << "\n📄 Borrowing History for Member ID: " << memberID << "\n";
    bool found = false;
    for (const Transaction& t : transactions) {
        if (t.memberID == memberID) {
            cout << "Book ID: " << t.bookID << " | Issued: " << t.issueDate << " | Returned: " << t.returnDate
                 << " | Fine: ₹" << t.fine << "\n";
            found = true;
        }
    }
    if (!found) cout << "No records found for this member.\n";
}

// Report 5: Total fine collected
void reportFineCollected() {
    double total = 0;
    for (const Transaction& t : transactions) {
        total += t.fine;
    }
    cout << "\n💰 Total Fine Collected: ₹" << total << "\n";
}

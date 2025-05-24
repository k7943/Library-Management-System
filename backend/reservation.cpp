#include <iostream>
#include <unordered_map>
#include <queue>
#include <fstream>
#include <sstream>
using namespace std;

unordered_map<string, queue<string>> reservations;

// Add a member to a book's waitlist
void reserveBook(const string& bookID, const string& memberID) {
    reservations[bookID].push(memberID);
    cout << "Member " << memberID << " added to waitlist for Book " << bookID << ".\n";
}

// View waitlist for a book
void viewReservationQueue(const string& bookID) {
    if (reservations.find(bookID) == reservations.end() || reservations[bookID].empty()) {
        cout << "No reservations for Book " << bookID << ".\n";
        return;
    }

    cout << "Waitlist for Book " << bookID << ":\n";
    queue<string> temp = reservations[bookID];
    int pos = 1;
    while (!temp.empty()) {
        cout << pos++ << ". " << temp.front() << "\n";
        temp.pop();
    }
}

// Remove the next member from reservation queue (after return)
string getNextInQueue(const string& bookID) {
    if (reservations.find(bookID) == reservations.end() || reservations[bookID].empty())
        return "";

    string nextMember = reservations[bookID].front();
    reservations[bookID].pop();
    return nextMember;
}

// Save reservations to file
void saveReservations(const string& filename) {
    ofstream file(filename);
    for (auto& entry : reservations) {
        string bookID = entry.first;
        queue<string> temp = entry.second;
        while (!temp.empty()) {
            file << bookID << "," << temp.front() << "\n";
            temp.pop();
        }
    }
    file.close();
}

// Load reservations from file
void loadReservations(const string& filename) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string bookID, memberID;
        getline(ss, bookID, ',');
        getline(ss, memberID, ',');
        reservations[bookID].push(memberID);
    }
    file.close();
}

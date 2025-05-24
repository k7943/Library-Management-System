#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

class Member {
public:
    string memberID;
    string name;
    string contact;
    double fineAmount;

    Member() {}

    Member(string id, string n, string c) {
        memberID = id;
        name = n;
        contact = c;
        fineAmount = 0.0;
    }

    void display() const {
        cout << "ID: " << memberID << "\nName: " << name << "\nContact: " << contact
             << "\nFine Due: ₹" << fineAmount << "\n\n";
    }

    string toCSV() const {
        return memberID + "," + name + "," + contact + "," + to_string(fineAmount);
    }

    static Member fromCSV(const string& line) {
        stringstream ss(line);
        string id, name, contact, fineStr;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, contact, ',');
        getline(ss, fineStr, ',');
        Member m;
        m.memberID = id;
        m.name = name;
        m.contact = contact;
        m.fineAmount = stod(fineStr);
        return m;
    }
};

vector<Member> members;

// Load members from CSV
void loadMembers(const string& filename) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        members.push_back(Member::fromCSV(line));
    }
    file.close();
}

// Save members to CSV
void saveMembers(const string& filename) {
    ofstream file(filename);
    for (const Member& m : members) {
        file << m.toCSV() << "\n";
    }
    file.close();
}

// Add a new member
void addMember() {
    string id, name, contact;

    cout << "Enter Member ID: "; getline(cin, id);
    cout << "Enter Name: "; getline(cin, name);
    cout << "Enter Contact Info: "; getline(cin, contact);

    members.emplace_back(id, name, contact);
    cout << "Member added successfully!\n";
}

// View all members
void viewMembers() {
    if (members.empty()) {
        cout << "No members available.\n";
        return;
    }
    for (const Member& m : members) {
        m.display();
    }
}

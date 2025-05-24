#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

class Book {
public:
    string bookID;
    string title;
    string author;
    string publisher;
    string category;
    int totalCopies;
    int availableCopies;

    Book() {}

    Book(string id, string t, string a, string p, string c, int total) {
        bookID = id;
        title = t;
        author = a;
        publisher = p;
        category = c;
        totalCopies = total;
        availableCopies = total;
    }

    void display() const {
        cout << "ID: " << bookID << "\nTitle: " << title << "\nAuthor: " << author
             << "\nPublisher: " << publisher << "\nCategory: " << category
             << "\nTotal Copies: " << totalCopies << "\nAvailable: " << availableCopies << "\n\n";
    }

    string toCSV() const {
        return bookID + "," + title + "," + author + "," + publisher + "," + category + "," +
               to_string(totalCopies) + "," + to_string(availableCopies);
    }

    static Book fromCSV(const string& line) {
        stringstream ss(line);
        string id, title, author, publisher, category, total, available;
        getline(ss, id, ',');
        getline(ss, title, ',');
        getline(ss, author, ',');
        getline(ss, publisher, ',');
        getline(ss, category, ',');
        getline(ss, total, ',');
        getline(ss, available, ',');

        Book b;
        b.bookID = id;
        b.title = title;
        b.author = author;
        b.publisher = publisher;
        b.category = category;
        b.totalCopies = stoi(total);
        b.availableCopies = stoi(available);
        return b;
    }
};

vector<Book> books;

// Load books from CSV
void loadBooks(const string& filename) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        books.push_back(Book::fromCSV(line));
    }
    file.close();
}

// Save books to CSV
void saveBooks(const string& filename) {
    ofstream file(filename);
    for (const Book& b : books) {
        file << b.toCSV() << "\n";
    }
    file.close();
}

// Add a new book
void addBook() {
    string id, title, author, publisher, category;
    int copies;

    cout << "Enter Book ID: "; getline(cin, id);
    cout << "Enter Title: "; getline(cin, title);
    cout << "Enter Author: "; getline(cin, author);
    cout << "Enter Publisher: "; getline(cin, publisher);
    cout << "Enter Category: "; getline(cin, category);
    cout << "Enter Total Copies: "; cin >> copies;
    cin.ignore();

    books.emplace_back(id, title, author, publisher, category, copies);
    cout << "Book added successfully!\n";
}

// View all books
void viewBooks() {
    if (books.empty()) {
        cout << "No books available.\n";
        return;
    }
    for (const Book& b : books) {
        b.display();
    }
}

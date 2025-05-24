#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

// Read lines from a CSV file
vector<string> readLinesFromFile(const string& filename) {
    vector<string> lines;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << "\n";
        return lines;
    }

    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            lines.push_back(line);
        }
    }
    file.close();
    return lines;
}

// Write lines to a CSV file (overwrites)
void writeLinesToFile(const string& filename, const vector<string>& lines) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not write to file " << filename << "\n";
        return;
    }

    for (const string& line : lines) {
        file << line << "\n";
    }
    file.close();
}

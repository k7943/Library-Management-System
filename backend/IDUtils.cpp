#include <string>
#include <iomanip>
#include <sstream>
#include <unordered_map>
using namespace std;

// Internal counters
unordered_map<string, int> idCounters = {
    {"BOOK", 1},
    {"MEMBER", 1}
};

// Generate ID like B001, M001 etc.
string generateID(const string& type) {
    stringstream ss;
    if (type == "BOOK") {
        ss << "B" << setfill('0') << setw(3) << idCounters["BOOK"]++;
    } else if (type == "MEMBER") {
        ss << "M" << setfill('0') << setw(3) << idCounters["MEMBER"]++;
    } else {
        ss << "X" << setfill('0') << setw(3) << 0;
    }
    return ss.str();
}

// Reset counters (optional for testing)
void resetIDCounters() {
    idCounters["BOOK"] = 1;
    idCounters["MEMBER"] = 1;
}

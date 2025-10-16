#include <bits/stdc++.h>
using namespace std;

// Knowledge Base: store parent relationships
map<string, vector<string>> parentOf;

// Function to add a parent-child fact
void addParent(string parent, string child) {
    parentOf[parent].push_back(child);
}

// Get children of a person
vector<string> getChildren(string parent) {
    return parentOf[parent];
}

// Get parents of a person
vector<string> getParents(string child) {
    vector<string> res;
    for (auto &p : parentOf) {
        for (auto &c : p.second) {
            if (c == child) res.push_back(p.first);
        }
    }
    return res;
}

// Get siblings of a person
vector<string> getSiblings(string person) {
    vector<string> res;
    vector<string> parents = getParents(person);
    for (string par : parents) {
        for (string c : parentOf[par]) {
            if (c != person) res.push_back(c);
        }
    }
    return res;
}

// Demo
int main() {
    // Building a small family tree
    addParent("John", "Alice");
    addParent("John", "Bob");
    addParent("Mary", "Alice");
    addParent("Mary", "Bob");
    addParent("Alice", "David");
    addParent("Alice", "Eva");

    // Query examples
    cout << "Children of John: ";
    for (string c : getChildren("John")) cout << c << " ";
    cout << "\n";

    cout << "Parents of Alice: ";
    for (string p : getParents("Alice")) cout << p << " ";
    cout << "\n";

    cout << "Siblings of Alice: ";
    for (string s : getSiblings("Alice")) cout << s << " ";
    cout << "\n";

    cout << "Siblings of Bob: ";
    for (string s : getSiblings("Bob")) cout << s << " ";
    cout << "\n";

    cout << "Children of Alice: ";
    for (string c : getChildren("Alice")) cout << c << " ";
    cout << "\n";

    return 0;
}

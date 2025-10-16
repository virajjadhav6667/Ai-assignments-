#include <bits/stdc++.h>
using namespace std;

struct Rule {
    vector<string> conditions;
    string conclusion;
};

bool backwardChaining(string goal, vector<string> facts, vector<Rule> rules, set<string>& visited) {
    if (find(facts.begin(), facts.end(), goal) != facts.end()) {
        cout << "Fact found: " << goal << endl;
        return true;
    }

    if (visited.count(goal)) return false;
    visited.insert(goal);

    for (auto &rule : rules) {
        if (rule.conclusion == goal) {
            bool allTrue = true;
            for (string cond : rule.conditions) {
                if (!backwardChaining(cond, facts, rules, visited)) {
                    allTrue = false;
                    break;
                }
            }
            if (allTrue) {
                cout << "Derived: " << goal << endl;
                return true;
            }
        }
    }
    return false;
}

int main() {
    vector<string> facts = {"A", "B"};  // Known facts

    vector<Rule> rules = {
        {{"A", "B"}, "C"},
        {{"C"}, "D"},
        {{"D"}, "E"}
    };

    string goal = "E";
    set<string> visited;

    if (backwardChaining(goal, facts, rules, visited))
        cout << "Goal " << goal << " achieved!" << endl;
    else
        cout << "Goal " << goal << " not achieved." << endl;

    return 0;
}

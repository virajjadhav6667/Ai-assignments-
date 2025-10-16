#include <bits/stdc++.h>
using namespace std;

struct Rule {
    vector<string> conditions;
    string conclusion;
};

bool forwardChaining(vector<string> facts, vector<Rule> rules, string goal) {
    set<string> factSet(facts.begin(), facts.end());
    bool addedNewFact = true;

    while (addedNewFact) {
        addedNewFact = false;

        for (auto &rule : rules) {
            bool allTrue = true;
            for (string cond : rule.conditions) {
                if (!factSet.count(cond)) {
                    allTrue = false;
                    break;
                }
            }

            if (allTrue && !factSet.count(rule.conclusion)) {
                factSet.insert(rule.conclusion);
                cout << "Derived: " << rule.conclusion << endl;
                addedNewFact = true;

                if (rule.conclusion == goal) {
                    cout << "Goal " << goal << " achieved!" << endl;
                    return true;
                }
            }
        }
    }
    return factSet.count(goal);
}

int main() {
    vector<string> facts = {"A", "B"};  // Known facts

    vector<Rule> rules = {
        {{"A", "B"}, "C"},
        {{"C"}, "D"},
        {{"D"}, "E"}
    };

    string goal = "E";

    if (!forwardChaining(facts, rules, goal))
        cout << "Goal " << goal << " not achieved." << endl;

    return 0;
}

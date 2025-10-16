#include <bits/stdc++.h>
using namespace std;

struct CSP {
    int variables; // number of variables
    int domainSize; // size of domain for each variable
    vector<vector<int>> constraints; // adjacency list (constraints)
    vector<int> assignment; // assigned values
    vector<vector<bool>> domain; // remaining domain values for forward checking

    CSP(int n, int d) {
        variables = n;
        domainSize = d;
        constraints.resize(n);
        assignment.assign(n, -1);
        domain.assign(n, vector<bool>(d, true));
    }

    void addConstraint(int u, int v) {
        constraints[u].push_back(v);
        constraints[v].push_back(u);
    }

    bool isConsistent(int var, int value) {
        for (int neighbor : constraints[var]) {
            if (assignment[neighbor] == value) return false;
        }
        return true;
    }

    bool forwardCheck(int var, int value) {
        for (int neighbor : constraints[var]) {
            if (assignment[neighbor] == -1) { // unassigned
                bool possible = false;
                for (int val = 0; val < domainSize; val++) {
                    if (val != value && domain[neighbor][val]) {
                        possible = true;
                    }
                }
                if (!possible) return false;
            }
        }
        return true;
    }

    bool backtrack(int var) {
        if (var == variables) return true; // all variables assigned

        for (int val = 0; val < domainSize; val++) {
            if (isConsistent(var, val) && domain[var][val]) {
                assignment[var] = val;

                // save old domain state
                auto oldDomain = domain;

                // forward check
                for (int neighbor : constraints[var]) {
                    domain[neighbor][val] = false;
                }

                if (forwardCheck(var, val) && backtrack(var + 1))
                    return true;

                // backtrack
                domain = oldDomain;
                assignment[var] = -1;
            }
        }
        return false;
    }

    void solve() {
        if (backtrack(0)) {
            cout << "Solution found:\n";
            for (int i = 0; i < variables; i++)
                cout << "Variable " << i << " = " << assignment[i] << "\n";
        } else {
            cout << "No solution exists.\n";
        }
    }
};

int main() {
    // Example: Graph coloring with 4 variables and 3 colors
    CSP csp(4, 3);

    // Constraints (edges)
    csp.addConstraint(0, 1);
    csp.addConstraint(0, 2);
    csp.addConstraint(1, 2);
    csp.addConstraint(2, 3);

    csp.solve();
    return 0;
}

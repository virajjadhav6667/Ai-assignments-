#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_set>
#include <algorithm>

using namespace std;

const vector<vector<int>> goal = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 0}
};

struct Puzzle {
    vector<vector<int>> state;
    int x, y; // Position of blank tile (0)
    string path; // Move path: U, D, L, R

    Puzzle(vector<vector<int>> s, int x, int y, string p = "") : state(s), x(x), y(y), path(p) {}

    // Convert board to a unique string key
    string get_key() const {
        string res;
        for (auto &row : state)
            for (int val : row)
                res += std::to_string(val);
        return res;
    }

    // Check if current puzzle is goal state
    bool is_goal() const {
        return state == goal;
    }

    // Generate all valid neighbors
    vector<Puzzle> get_neighbors() const {
        vector<Puzzle> neighbors;
        vector<pair<int, int>> moves = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        vector<char> directions = {'D', 'U', 'R', 'L'};

        for (int i = 0; i < 4; i++) {
            int nx = x + moves[i].first;
            int ny = y + moves[i].second;

            if (nx >= 0 && ny >= 0 && nx < 3 && ny < 3) {
                vector<vector<int>> new_state = state;
                swap(new_state[x][y], new_state[nx][ny]);
                neighbors.emplace_back(new_state, nx, ny, path + directions[i]);
            }
        }

        return neighbors;
    }
};

// ---------------- BFS ----------------
void bfs(Puzzle start) {
    queue<Puzzle> q;
    unordered_set<string> visited;

    q.push(start);
    visited.insert(start.get_key());

    while (!q.empty()) {
        Puzzle current = q.front();
        q.pop();

        if (current.is_goal()) {
            cout << "BFS: Goal found!\nMoves: " << current.path << "\n";
            return;
        }

        for (const Puzzle &neighbor : current.get_neighbors()) {
            string key = neighbor.get_key();
            if (visited.find(key) == visited.end()) {
                visited.insert(key);
                q.push(neighbor);
            }
        }
    }

    cout << "BFS: No solution found.\n";
}

// ---------------- DFS ----------------
void dfs(Puzzle start, int depth_limit = 50) {
    stack<Puzzle> st;
    unordered_set<string> visited;

    st.push(start);
    visited.insert(start.get_key());

    while (!st.empty()) {
        Puzzle current = st.top();
        st.pop();

        if (current.is_goal()) {
            cout << "DFS: Goal found!\nMoves: " << current.path << "\n";
            return;
        }

        if (current.path.length() > depth_limit)
            continue;

        for (const Puzzle &neighbor : current.get_neighbors()) {
            string key = neighbor.get_key();
            if (visited.find(key) == visited.end()) {
                visited.insert(key);
                st.push(neighbor);
            }
        }
    }

    cout << "DFS: No solution found within depth limit.\n";
}

// ---------------- MAIN ----------------
int main() {
    // Initial configuration (change as needed)
    vector<vector<int>> initial = {
        {1, 2, 3},
        {4, 6, 0},
        {7, 5, 8}
    };

    int x, y;
    // Find position of blank (0)
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (initial[i][j] == 0)
                x = i, y = j;

    Puzzle start(initial, x, y);

    bfs(start);
    dfs(start);

    return 0;
}

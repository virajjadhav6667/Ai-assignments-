#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, cost;
};

struct Node {
    int id, g, f;
    bool operator>(const Node& other) const {
        return f > other.f; // min-heap
    }
};

// Simple A* function
vector<int> aStar(int start, int goal,
                  vector<vector<Edge>>& graph,
                  vector<int>& heuristic) {
    priority_queue<Node, vector<Node>, greater<Node>> open;
    vector<int> gScore(graph.size(), INT_MAX);
    vector<int> parent(graph.size(), -1);
    vector<bool> closed(graph.size(), false);

    gScore[start] = 0;
    open.push({start, 0, heuristic[start]});

    while (!open.empty()) {
        Node current = open.top();
        open.pop();

        if (current.id == goal) { // goal found
            vector<int> path;
            for (int v = goal; v != -1; v = parent[v])
                path.push_back(v);
            reverse(path.begin(), path.end());
            return path;
        }

        if (closed[current.id]) continue;
        closed[current.id] = true;

        for (auto& e : graph[current.id]) {
            int gNew = gScore[current.id] + e.cost;
            if (gNew < gScore[e.to]) {
                gScore[e.to] = gNew;
                parent[e.to] = current.id;
                int f = gNew + heuristic[e.to];
                open.push({e.to, gNew, f});
            }
        }
    }
    return {}; // no path
}

int main() {
    // Example graph with 5 nodes (0..4)
    vector<vector<Edge>> graph(5);
    graph[0] = {{1, 1}, {2, 4}};
    graph[1] = {{2, 2}, {3, 5}};
    graph[2] = {{3, 1}};
    graph[3] = {{4, 3}};
    graph[4] = {};

    // Heuristic values (straight-line guesses)
    vector<int> heuristic = {7, 6, 2, 1, 0};

    int start = 0, goal = 4;
    vector<int> path = aStar(start, goal, graph, heuristic);

    if (!path.empty()) {
        cout << "Path: ";
        for (int i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i != path.size() - 1) cout << " -> ";
        }
        cout << endl;
    } else {
        cout << "No path found\n";
    }
    return 0;
}

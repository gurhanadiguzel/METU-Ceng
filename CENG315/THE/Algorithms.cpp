#include <cstring>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <vector>
using namespace std;

#define INF 9999
#define MAX_N 1000
typedef pair<int, int> pii;

// int V = 9, E = 14;
// vector<vector<pii>> adj(V);

// BASIC GRAPH ALGORITHMS
// Dept-First-Search
void DFS(int v, vector<int> adj[], bool visited[]) {
    visited[v] = true;
    cout << v << " ";
    for (int i = 0; i < adj[v].size(); i++) {
        if (!visited[adj[v][i]]) 
            DFS(adj[v][i], adj, visited);
    }
}
// Breath-First-Search
void BFS(int v, vector<int> adj[], bool visited[]) {
    queue<int> q;
    visited[v] = true;
    q.push(v);
    while (!q.empty()) {
        int curr = q.front();
        cout << curr << " ";
        q.pop();
        for (int i = 0; i < adj[curr].size(); i++) {
            if (!visited[adj[curr][i]]) {
                visited[adj[curr][i]] = true;
                q.push(adj[curr][i]);
            }
        }
    }
}
// Topological Sorting
void topologicalSortUtil(int v, vector<int> adj[], vector<bool> visited, stack<int>& Stack) {
    visited[v] = true;
    for (int i = 0; i < adj[v].size(); i++) {
        if (!visited[adj[v][i]])
            topologicalSortUtil(adj[v][i], adj, visited, Stack);
    }
    Stack.push(v);
}

void topologicalSort(vector<int> adj[], int V) {
    stack<int> Stack;
    vector<bool> visited(false,V);
    for (int i = 0; i < V; i++)
        if (!visited[i]) topologicalSortUtil(i, adj, visited, Stack);
    while (!Stack.empty()) {
        cout << Stack.top() << " ";
        Stack.pop();
    }
}

// MINIMUM SPANNING TREE
// Prim's Algorithm [Time Complexity: O(V2), Auxiliary Space: O(V)]
void primMST(vector<pii> adj[], int V) {
    vector<pii> adj[V];
    priority_queue<pii, vector<pii>, greater<pii>> pq;

    int src = 0;
    vector<int> key(V, INF);
    vector<int> parent(V, -1);
    vector<bool> inMST(V, false);

    pq.push({0, src});
    key[src] = 0;
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        inMST[u] = true;
        for (auto i = adj[u].begin(); i != adj[u].end(); i++) {
            int v = (*i).first;
            int weight = (*i).second;

            if (!inMST[v] && key[v] > weight) {
                key[v] = weight;
                pq.push({key[v], v});
                parent[v] = u;
            }
        }
    }
    // Print
    for (int i = 1; i < V; i++)
        cout << parent[i] << "-" << i << " " << key[i] << endl;
}

// SINGLE SOURCE SHORTEST PATH ALGORITHMS
// Dijkstra's Algorithm [Time Complexity: O(V2), Auxiliary Space: O(V)]
void dijkstra(vector<pii> adj[], int V, int src) {
    vector<pii> adj[V];
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    vector<int> dist(V, INF);
    pq.push({0, src});
    dist[src] = 0;
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        for (auto i = adj[u].begin(); i != adj[u].end(); i++) {
            int v = (*i).first;
            int weight = (*i).second;
            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
    // Print
    for (int i = 0; i < V; i++)
        cout << src << "-" << i << " " << dist[i] << endl;
}

// Bellman-Ford Algorithms [Time Complexity: O(V * E), Auxiliary Space: O(E)]
void bellmanFord(vector<pair<int, int>> adj[], int V, int src) {
    vector<pair<int, int>> adj[V];
    vector<int> dist(V, INF);
    dist[src] = 0;
    for (int i = 0; i < V - 1; i++) {
        for (int u = 0; u < V; u++) {
            for (auto j = adj[u].begin(); j != adj[u].end(); j++) {
                int v = (*j).first;
                int weight = (*j).second;
                if (dist[v] > dist[u] + weight) {
                    dist[v] = dist[u] + weight;
                }
            }
        }
    }
    // Check for negative cycle
    for (int u = 0; u < V; u++) {
        for (auto j = adj[u].begin(); j != adj[u].end(); j++) {
            int v = (*j).first;
            int weight = (*j).second;
            if (dist[v] > dist[u] + weight) {
                cout << "Negative cycle detected" << endl;
                return;
            }
        }
    }
    // Print
    for (int i = 0; i < V; i++)
        cout << src << "-" << i << " " << dist[i] << endl;
}

// All Pairs Shortest Paths algorithm
// Floyd-Warshall  [Time Complexity: O(V3),  Auxiliary Space: O(V2)]
void floydWarshall(vector<vector<int>>& adj, int V) {
    /*
    vector<vector<int>> adj = { {0, 3, INF, 7},
                                {8, 0, 2, INF},
                                {5, INF, 0, 1},
                                {2, INF, INF, 0}};
    */
    vector<vector<int>> dist(V, vector<int>(V));
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            dist[i][j] = adj[i][j];
        }
    }
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
    // Print
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF)
                cout << "INF ";
            else
                cout << dist[i][j] << " ";
        }
        cout << endl;
    }
}

// Network Flow algorithms
// EdmondsKarp Algorithm [Time Complexity: O(∣V∣⋅∣E∣2)], BFS
int n, s, t;
int capacity[MAX_N][MAX_N];  // capacity of each edge
int flow[MAX_N][MAX_N];      // current flow through each edge
vector<int> adj[MAX_N];      // adjacency list

vector<int> bfs() {
    vector<int> parent(n, -1);  // stores the augmenting path
    queue<int> q;
    q.push(s);
    parent[s] = -2;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (parent[v] == -1 && capacity[u][v] - flow[u][v] > 0) {
                parent[v] = u;
                q.push(v);

                if (v == t) return parent;  // augmenting path found
            }
        }
    }

    return parent;  // no augmenting path found
}

int edmonds_karp() {
    int max_flow = 0;

    while (true) {
        vector<int> parent = bfs();

        if (parent[t] == -1) return max_flow;  // no augmenting path found

        int bottleneck = INF;

        // find bottleneck
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            bottleneck = min(bottleneck, capacity[u][v] - flow[u][v]);
        }

        // update flow
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            flow[u][v] += bottleneck;
            flow[v][u] -= bottleneck;
        }

        max_flow += bottleneck;
    }
}

// String search algorithms
// FSA and Knuth-Morris-Frat Algorithm [Time Complexity: O(N+M), Auxiliary Space: O(M)]
vector<int> getLPS(string pattern) {
    // Longest Prefix Suffix
    int m = pattern.length();
    vector<int> lps(m, 0);
    int j = 0;
    for (int i = 1; i < m; i++) {
        while (j > 0 && pattern[i] != pattern[j]) {
            j = lps[j - 1];
        }
        if (pattern[i] == pattern[j]) {
            j++;
        }
        lps[i] = j;
    }
    return lps;
    // For the pattern “AABAACAABAA”, lps[] is [0, 1, 0, 1, 2, 0, 1, 2, 3, 4, 5]
    // For the pattern “AAACAAAAAC”, lps[] is [0, 1, 2, 0, 1, 2, 3, 3, 3, 4]
    // For the pattern “AAABAAA”, lps[] is [0, 1, 2, 0, 1, 2, 3]
}

void KMP(string text, string pattern) {
    vector<int> lps = getLPS(pattern);
    int n = text.length();
    int m = pattern.length();
    int j = 0;
    for (int i = 0; i < n; i++) {
        while (j > 0 && text[i] != pattern[j]) {
            j = lps[j - 1];
        }
        if (text[i] == pattern[j]) {
            j++;
        }
        if (j == m) {
            cout << "Found pattern at index " << i - m + 1 << endl;
            j = lps[j - 1];
        }
    }
}

// String compression
// Huffman coding Algorithm [Time complexity: O(nlogn)]

struct Node {
    char c;
    int freq;
    Node *left, *right;
    Node(char c, int freq) : c(c), freq(freq), left(nullptr), right(nullptr) {}
    Node(char c, int freq, Node* left, Node* right) : c(c), freq(freq), left(left), right(right) {}
};

struct Compare {
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq;
    }
};

void getCodes(Node* root, string str, vector<pair<char, string>>& codes) {
    if (!root) {
        return;
    }
    if (!root->left && !root->right) {
        codes.push_back({root->c, str});
        return;
    }
    getCodes(root->left, str + "0", codes);
    getCodes(root->right, str + "1", codes);
}

void compress(string text) {
    vector<int> freq(256, 0);
    for (auto c : text) {
        freq[c]++;
    }

    priority_queue<Node*, vector<Node*>, Compare> pq;
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            pq.push(new Node(i, freq[i]));
        }
    }

    while (pq.size() != 1) {
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();
        int sum = left->freq + right->freq;
        pq.push(new Node('\0', sum, left, right));
    }
    Node* root = pq.top();
    vector<pair<char, string>> codes;
    getCodes(root, "", codes);

    string compressedText = "";
    for (auto c : text) {
        for (auto code : codes) {
            if (code.first == c) {
                compressedText += code.second;
                break;
            }
        }
    }
    // Print
    cout << "Original Text: " << text << endl;
    cout << "Compressed Text: " << compressedText << endl;
}

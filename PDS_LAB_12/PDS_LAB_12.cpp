#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <limits>
#include <stack>

using namespace std;

const int INF = numeric_limits<int>::max();

void readGraph(const string& filename, vector<vector<pair<int, int>>>& adjList, int& n, int& m) {
    ifstream infile(filename);
    if (!infile.is_open()) {
        cerr << "Не вдалося відкрити файл!" << endl;
        return;
    }

    infile >> n >> m;
    adjList.assign(n, vector<pair<int, int>>());

    int v, u, w;
    for (int i = 0; i < m; ++i) {
        infile >> v >> u >> w;
        adjList[v].emplace_back(u, w);
    }

    infile.close();
}

vector<int> dijkstra(const vector<vector<pair<int, int>>>& adjList, int start, vector<int>& previous) {
    int n = adjList.size();
    vector<int> dist(n, INF);
    dist[start] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.emplace(0, start);

    previous.assign(n, -1);

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue;

        for (auto& edge : adjList[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.emplace(dist[v], v);
                previous[v] = u;
            }
        }
    }

    return dist;
}

void printShortestPath(int start, int end, const vector<int>& previous) {
    stack<int> path;
    int u = end;
    while (u != -1) {
        path.push(u);
        u = previous[u];
    }

    cout << "Найкоротший шлях від " << start << " до " << end << ": ";
    while (!path.empty()) {
        cout << path.top();
        path.pop();
        if (!path.empty()) cout << " -> ";
    }
    cout << endl;
}

void findShortestPath(const vector<vector<pair<int, int>>>& adjList, int start, int end) {
    vector<int> previous;
    vector<int> dist = dijkstra(adjList, start, previous);

    if (dist[end] == INF) {
        cout << "Немає шляху між вершинами " << start << " і " << end << "." << endl;
    }
    else {
        cout << "Найкоротша відстань від " << start << " до " << end << ": " << dist[end] << endl;
        printShortestPath(start, end, previous);
    }
}

void findShortestPathsFromVertex(const vector<vector<pair<int, int>>>& adjList, int start) {
    vector<int> previous;
    vector<int> dist = dijkstra(adjList, start, previous);

    cout << "Найкоротші відстані від вершини " << start << " до інших вершин:" << endl;
    for (int i = 0; i < dist.size(); ++i) {
        if (dist[i] == INF) {
            cout << "Вершина " << i << ": Немає шляху" << endl;
        }
        else {
            cout << "Вершина " << i << ": " << dist[i] << endl;
        }
    }
}

int main() {
    
    string inputFile = "123.txt";
    vector<vector<pair<int, int>>> adjList;
    int n, m;

    readGraph(inputFile, adjList, n, m);

    int start, end;
    cout << "Введіть початкову вершину: ";
    cin >> start;
    cout << "Введіть кінцеву вершину: ";
    cin >> end;

    findShortestPath(adjList, start, end);

    cout << "\nВведіть вершину для пошуку шляхів до всіх інших: ";
    cin >> start;

    findShortestPathsFromVertex(adjList, start);

    return 0;
}
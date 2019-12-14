#include <vector>
#include <iostream>
#include <queue>

using std::vector;
using std::queue;
using std::cout;
using std::cin;

struct IGraph {
    virtual ~IGraph() {}

    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;

    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};

class ListGraph : public IGraph {
public:
    ListGraph(int count);

    ListGraph(const IGraph &graph);

    virtual ~ListGraph();

    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) override;

    virtual int VerticesCount() const override;

    virtual vector<int> GetNextVertices(int vertex) const override;

    virtual vector<int> GetPrevVertices(int vertex) const override;

private:
    vector<vector<int>> adjacencyLists;
};

ListGraph::ListGraph(int count) :
        adjacencyLists(count) {
}

ListGraph::ListGraph(const IGraph &graph) :
        ListGraph(graph.VerticesCount()) {
    for (int i = 0; i < graph.VerticesCount(); i++)
        adjacencyLists[i] = graph.GetNextVertices(i);
}

ListGraph::~ListGraph() {
}

void ListGraph::AddEdge(int from, int to) {

    adjacencyLists[from].push_back(to);
    adjacencyLists[to].push_back(from);
}

int ListGraph::VerticesCount() const {
    return adjacencyLists.size();
}

vector<int> ListGraph::GetNextVertices(int vertex) const {
    return adjacencyLists[vertex];
}

vector<int> ListGraph::GetPrevVertices(int vertex) const {

    vector<int> result;
    for (int from = 0; from < adjacencyLists.size(); from++)
        for (int i = 0; i < adjacencyLists[from].size(); i++)
            if (adjacencyLists[from][i] == vertex)
                result.push_back(from);

    return result;
}


int search(const IGraph &graph, int vertex, int cel) {
    vector<int> count_path(graph.VerticesCount());
    vector<int> dist(graph.VerticesCount());
    queue<int> queue;
    queue.push(vertex);
    count_path[vertex] = 1;
    while (!queue.empty()) {
        int current = queue.front();
        queue.pop();
        if (current != cel) {
            vector<int> verticies = graph.GetNextVertices(current);
            for (auto &i: verticies) {
                if (!count_path[i]) {
                    queue.push(i);
                    count_path[i] = count_path[current];
                    dist[i] = dist[current] + 1;
                } else if (dist[i] == dist[current] + 1) {
                    count_path[i] += count_path[current];
                }
            }
        }
    }

    return count_path[cel];
}


void contest() {
    int N;
    std::cin >> N;
    int r;
    std::cin >> r;
    int from, to;
    ListGraph list(N + 1);
    for (int i = 0; i < r; i++) {
        std::cin >> from;
        std::cin >> to;
        list.AddEdge(from, to);
    }
    int vertex, cel;
    std::cin >> vertex;
    std::cin >> cel;
    int res = search(list, vertex, cel);
    std::cout << res;
}

int main() {
    contest();
    return 0;
}
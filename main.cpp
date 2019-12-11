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
    std::vector<int> dst(graph.VerticesCount() + 1);
    dst[0] = 0;
    int min_dist = 0;
    vector<bool> visited(graph.VerticesCount(), false);
    std::queue<int> qu;
    qu.push(vertex);
    visited[vertex] = true;
    int countOfPaths = 0;

    while (!qu.empty()) {
        int current = qu.front();
        qu.pop();
        if (current != cel) {
            vector<int> nextVertices = graph.GetNextVertices(current);
            for (int v : nextVertices) {
                if ((!visited[v] && v != cel)) {
                    qu.push(v);
                    visited[v] = true;
                    dst[v] = dst[current] + 1;
                }
                if (v == cel) {
                    if (min_dist == 0) min_dist = dst[current] + 1;
                    if (min_dist == dst[current] + 1)
                        countOfPaths++;
                }
            }
        }
    }
    return countOfPaths;
}


void contest() {
    int N;
    std::cin >> N;
    int r;
    std::cin >> r;
    int from, to;
    ListGraph list(N);
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

    //test();

    contest();

    //ListGraph g(5);
    //g.AddEdge(0, 1);
    //g.AddEdge(0, 2);
    //g.AddEdge(1, 2);
    //g.AddEdge(1, 3);
    //g.AddEdge(2, 3);
    //int res = search(g, 0, 3);
    //std::cout<<res;
    return 0;
}
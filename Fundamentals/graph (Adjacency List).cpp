#include <vector>
using namespace std;

int main() {

    int V = 5;

    vector<vector<int>> graph(V);

    graph[0].push_back(1);
    graph[0].push_back(2);
    graph[1].push_back(3);
    graph[2].push_back(4);

    return 0;
}
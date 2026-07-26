#include <iostram>
#include <queue>

using namespace std;

int main () {
vector<int> graph[100];
bool visited[100];

void bfs(int start) {

    queue<int> q;

    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        cout << node << " ";

        for (int next : graph[node]) {
            if (!visited[next]) {
                visited[next] = true;
                q.push(next);
            }
        }
    }
}

}
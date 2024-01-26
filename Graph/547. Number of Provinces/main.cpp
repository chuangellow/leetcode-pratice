#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    typedef struct vectex {
        int idx;
        int color; // 0: white, 1: gray, 2: black
    } vertex;
    void DFSVisit(int sourceIdx, vector<vertex>& vertices, vector<vector<int>>& isConnected, int n) {
        vertices[sourceIdx].color = 1;
        for (int i = 0; i < n; i++) {
            if (i == sourceIdx) continue;
            if (isConnected[sourceIdx][i]) {
                if (vertices[i].color == 0) {
                    DFSVisit(i, vertices, isConnected, n);
                }
            }
        }
        vertices[sourceIdx].color = 2;
        return;
    }
    int DFS(vector<vertex>& vertices, vector<vector<int>>& isConnected, int n) {
        int count = 0;
        for (int i = 0; i < n; i++) {
            if (vertices[i].color == 0) {
                DFSVisit(i, vertices, isConnected, n);
                count++;
            }
        }
        return count;
    }
    void BFS(int sourceIdx, vector<vertex>& vertices, vector<vector<int>>& isConnected, int n) {
        vertices[sourceIdx].color = 1;
        vertex source = vertices[sourceIdx];
        queue<vertex> nextVisit;
        nextVisit.push(source);
        while (nextVisit.size() != 0) {
            vertex u = nextVisit.front();
            nextVisit.pop();
            for (int i = 0; i < n; i++) {
                if (i == u.idx) continue;
                if (isConnected[u.idx][i]) {
                    if (vertices[i].color == 0) {
                        vertices[i].color = 1;
                        nextVisit.push(vertices[i]);
                    }
                }
            }
            vertices[u.idx].color = 2;
        }
        return;
    }
    int findNonVisited(vector<vertex>& vertices, int n) {
        for (int i = 0; i < n; i++) {
            if (vertices[i].color == 0) return i;
        }
        return -1;
    }
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        vector<vertex> vertices;
        for (int i = 0; i < n; i++) {
            vertex v = {i, 0};
            vertices.push_back(v);
        }
        return DFS(vertices, isConnected, n);
    }
};

int main(void) {
    int n;
    cin >> n;
    vector<vector<int>> isConnected(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> isConnected[i][j];
        }
    }
    Solution sol;
    cout << sol.findCircleNum(isConnected) << endl;
    return 0;
}
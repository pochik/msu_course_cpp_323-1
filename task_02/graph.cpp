#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int main(){
    int n, m, a, b;
    cin >> n >> m;
    //N - quantity of vertices, M - quantity of edges
    int graph[n][n];
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            graph[i][j] = -1;
        }
    }
    for (int i = 0; i < m; i++){
        cin >> a >> b;
        graph[a][b] = i;
        graph[b][a] = i;
    }
    cout << endl;

    //DNS to understand if the graph is connected or not
    bool visited[n];
    for (int i = 0; i < n; i++) visited[i] = 0;
    int root = 0;
    vector <int> stack;
    stack.push_back(root);
    while (stack.begin() != stack.end()){
        int now = stack[stack.size() - 1];
        //cout << now << " ";
        stack.pop_back();
        if (visited[now] == 1) continue;

        visited[now] = 1;
        for (int i = 0; i < n; i++){
            if (graph[now][i] != -1){
                stack.push_back(i);
            }
        }
    }

    for (int i = 0; i < n; i++)
        if (visited[i] == 0){
            cout << "disconnected graph";
            break;
        }

    /*

    cout << endl << endl;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }

    */

    ofstream fout;
    fout.open("output.json");

    fout << "{\n    \"vertices\": [\n";
    int edges[m][2];
    //for (int i = 0; i < m; i++) { edges[i][0] = -1; edges[i][1] = -1; }
    for (int i = 0; i < n; i++){
        fout << "      {\n        \"id\": " << i << ",\n        \"edge_ids\": [";
        bool first_semicolon = 1;
        for (int j = 0; j < n; j++){
            if (graph[i][j] != -1){
                if (first_semicolon == 0){
                    fout << ", " << graph[i][j];
                }
                else{
                    first_semicolon = 0;
                    fout << graph[i][j];
                }
                edges[graph[i][j]][0] = i;
                edges[graph[i][j]][1] = j;
            }
        }
        fout << "]\n      }, ";
    }
    fout << "\n        \"...\"\n    ],\n";


    fout << "    \"edges\": [";
    for (int i = 0; i < m; i++) {
        fout << "      {\n        \"id\": " << i << ",\n        \"vertex_ids\": ["
            << edges[i][0] << ", " << edges[i][1] << "]\n      }, ";
    }
    fout << "\n        \"...\"\n    ]\n}\n\n";
    fout.close();
    return 0;
}


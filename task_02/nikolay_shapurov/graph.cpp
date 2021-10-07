#include <array>
#include <fstream>
#include <iostream>
#include <vector>

class Graph {
 public:
  int num_vertices, num_edges;
  std::vector<std::vector<int>> data;

  Graph(int num_v, int num_e) {
    num_vertices = num_v;
    num_edges = num_e;
    for (int i = 0; i < num_v; i++) {
      std::vector<int> temp;
      data.push_back(temp);
      for (int j = 0; j < num_v; j++) {
        data[i].push_back(-1);
      }
    }
  }

  bool DNS() {
    bool visited[num_vertices];
    for (int i = 0; i < num_vertices; i++)
      visited[i] = 0;
    int root = 0;
    std::vector<int> stack;
    stack.push_back(root);
    while (stack.begin() != stack.end()) {
      int now = stack[stack.size() - 1];
      stack.pop_back();
      if (visited[now] == 1)
        continue;
      visited[now] = 1;
      for (int i = 0; i < num_vertices; i++) {
        if (data[now][i] != -1) {
          stack.push_back(i);
        }
      }
    }
    for (int i = 0; i < num_vertices; i++)
      if (visited[i] == 0) {
        return false;
      }
    return true;
  }

  void print() {
    for (int i = 0; i < num_vertices; i++) {
      for (int j = 0; j < num_vertices; j++) {
        std::cout << data[i][j] << " ";
      }
      std::cout << std::endl;
    }
  }
};

int main() {
  Graph MyGraph = Graph(14, 17);
  MyGraph.print();

  MyGraph.data[0][1] = 0;
  MyGraph.data[0][2] = 1;
  MyGraph.data[0][3] = 2;

  MyGraph.data[1][0] = 0;
  MyGraph.data[1][4] = 3;
  MyGraph.data[1][5] = 4;
  MyGraph.data[1][6] = 5;

  MyGraph.data[2][0] = 1;
  MyGraph.data[2][7] = 6;
  MyGraph.data[2][8] = 7;

  MyGraph.data[3][0] = 2;
  MyGraph.data[3][9] = 8;

  MyGraph.data[4][1] = 3;
  MyGraph.data[4][10] = 9;

  MyGraph.data[5][1] = 4;
  MyGraph.data[5][10] = 10;

  MyGraph.data[6][1] = 5;
  MyGraph.data[6][10] = 11;

  MyGraph.data[7][2] = 6;
  MyGraph.data[7][11] = 12;

  MyGraph.data[8][2] = 7;
  MyGraph.data[8][11] = 13;

  MyGraph.data[9][3] = 8;
  MyGraph.data[9][12] = 14;

  MyGraph.data[10][4] = 9;
  MyGraph.data[10][5] = 10;
  MyGraph.data[10][6] = 11;
  MyGraph.data[10][13] = 15;

  MyGraph.data[11][7] = 12;
  MyGraph.data[11][8] = 13;
  MyGraph.data[11][13] = 16;

  MyGraph.data[12][9] = 14;
  MyGraph.data[12][13] = 17;

  MyGraph.data[13][10] = 15;
  MyGraph.data[13][11] = 16;
  MyGraph.data[13][12] = 17;

  if (MyGraph.DNS() != 1)
    std::cout << "disconnected graph\n";

  std::ofstream fout;
  fout.open("output.json");

  fout << "{\n    \"vertices\": [\n";
  int edges[MyGraph.num_edges][2];
  for (int i = 0; i < MyGraph.num_vertices; i++) {
    fout << "     {\n        \"id\": " << i << ",\n        \"edge_ids\": [";
    bool first_semicolon = 1;
    for (int j = 0; j < MyGraph.num_vertices; j++) {
      if (MyGraph.data[i][j] != -1) {
        if (first_semicolon == 0) {
          fout << ", " << MyGraph.data[i][j];
        } else {
          first_semicolon = 0;
          fout << MyGraph.data[i][j];
        }
        edges[MyGraph.data[i][j]][0] = i;
        edges[MyGraph.data[i][j]][1] = j;
      }
    }
    if (i == MyGraph.num_vertices - 1) {
      fout << "]\n      }\n ";
    } else {
      fout << "]\n      },\n ";
    }
  }
  fout << "        \n    ],\n";

  fout << "\n    \"edges\": [\n";
  for (int i = 0; i < MyGraph.num_edges; i++) {
    if (i == MyGraph.num_edges - 1) {
      fout << "      {\n        \"id\": " << i << ",\n        \"vertex_ids\": ["
           << edges[i][0] << ", " << edges[i][1] << "]\n      } \n";
    } else {
      fout << "      {\n        \"id\": " << i << ",\n        \"vertex_ids\": ["
           << edges[i][0] << ", " << edges[i][1] << "]\n      }, \n";
    }
  }
  fout << "        \n    ]\n}\n\n";
  fout.close();

  return 0;
}

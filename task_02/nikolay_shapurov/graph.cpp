#include <array>
#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>

constexpr int INVALID_ID = -1;

class Graph {
 private:
  int num_vertices, num_edges;
  std::vector<std::vector<int>> data;

 public:
  Graph(int num_v, int num_e) {
    assert((num_v >= 0) &&
           "Invalid number of vertices. Must be positive integer.");
    assert((num_e >= 0) &&
           "Invalid number of edges. Must be positive integer.");

    num_vertices = num_v;
    num_edges = num_e;
    for (int i = 0; i < num_v; i++) {
      std::vector<int> temp;
      data.push_back(temp);
      for (int j = 0; j < num_v; j++) {
        data[i].push_back(INVALID_ID);
      }
    }
  }

  void add_edge(int edge_id, int vertex_id1, int vertex_id2) {
    assert((edge_id >= 0) && "Ivalid edge ID. Must be positive integer.");
    assert((vertex_id1 >= 0) &&
           "Invalid the first vertex ID. Must be positive integer.");
    assert((vertex_id2 >= 0) &&
           "Invalid the second vertex ID. Must be positive integer.");

    data[vertex_id1][vertex_id2] = edge_id;
    data[vertex_id2][vertex_id1] = edge_id;
  }

  void Print() {
    for (int i = 0; i < num_vertices; i++) {
      for (int j = 0; j < num_vertices; j++) {
        std::cout << data[i][j] << " ";
      }
      std::cout << std::endl;
    }
  }

  void PrintJSON() {
    std::ofstream fout;
    fout.open("output.json");

    fout << "{\n    \"vertices\": [\n";
    std::vector<std::vector<int>> edges;

    for (int i = 0; i <= num_edges; i++) {
      std::vector<int> tmp;
      edges.push_back(tmp);
      edges[i].push_back(0);
      edges[i].push_back(0);
    }

    for (int i = 0; i < num_vertices; i++) {
      fout << "     {\n        \"id\": " << i << ",\n        \"edge_ids\": [";
      bool first_semicolon = 1;
      for (int j = 0; j < num_vertices; j++) {
        if (data[i][j] != -1) {
          if (first_semicolon == 0) {
            fout << ", " << data[i][j];
          } else {
            first_semicolon = 0;
            fout << data[i][j];
          }
          edges[data[i][j]][0] = i;
          edges[data[i][j]][1] = j;
        }
      }
      if (i == num_vertices - 1) {
        fout << "]\n      }\n ";
      } else {
        fout << "]\n      },\n ";
      }
    }
    fout << "        \n    ],\n";

    fout << "\n    \"edges\": [\n";
    for (int i = 0; i < num_edges; i++) {
      if (i == num_edges - 1) {
        fout << "      {\n        \"id\": " << i
             << ",\n        \"vertex_ids\": [" << edges[i][0] << ", "
             << edges[i][1] << "]\n      } \n";
      } else {
        fout << "      {\n        \"id\": " << i
             << ",\n        \"vertex_ids\": [" << edges[i][0] << ", "
             << edges[i][1] << "]\n      }, \n";
      }
    }
    fout << "        \n    ]\n}\n\n";
    fout.close();
  }
};

int main() {
  Graph MyGraph = Graph(14, 17);
  MyGraph.Print();

  MyGraph.add_edge(0, 0, 1);
  MyGraph.add_edge(1, 0, 2);
  MyGraph.add_edge(2, 0, 3);

  MyGraph.add_edge(3, 1, 4);
  MyGraph.add_edge(4, 1, 5);
  MyGraph.add_edge(5, 1, 6);
  MyGraph.add_edge(6, 2, 7);
  MyGraph.add_edge(7, 2, 8);
  MyGraph.add_edge(8, 3, 9);

  MyGraph.add_edge(9, 4, 10);
  MyGraph.add_edge(10, 5, 10);
  MyGraph.add_edge(11, 6, 10);
  MyGraph.add_edge(12, 7, 11);
  MyGraph.add_edge(13, 8, 11);
  MyGraph.add_edge(14, 9, 12);

  MyGraph.add_edge(15, 10, 13);
  MyGraph.add_edge(16, 11, 13);
  MyGraph.add_edge(17, 12, 13);

  MyGraph.Print();

  MyGraph.PrintJSON();

  return 0;
}

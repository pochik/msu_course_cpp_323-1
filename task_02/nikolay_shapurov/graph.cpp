#include <iostream>
#include <vector>
#include <fstream>
#include <array>

class Graph{
public:

   int num_vertices, num_edges;
   std::vector<std::vector<int>> gr;

   Graph(int num_v, int num_e){
       num_vertices = num_v;
       num_edges = num_e;
       for (int i = 0; i < num_v; i++){
           std::vector<int> temp;
           gr.push_back(temp);
           for (int j = 0; j < num_v; j++){
               gr[i].push_back(-1);
           }
       }
   }

   bool DNS(){
       bool visited[num_vertices];
       for (int i = 0; i < num_vertices; i++) visited[i] = 0;
       int root = 0;
       std::vector <int> stack;
       stack.push_back(root);
       while (stack.begin() != stack.end()){
           int now = stack[stack.size() - 1];
           stack.pop_back();
           if (visited[now] == 1) continue;
           visited[now] = 1;
           for (int i = 0; i < num_vertices; i++){
               if (gr[now][i] != -1){
                   stack.push_back(i);
               }
           }
       }
       for (int i = 0; i < num_vertices; i++)
           if (visited[i] == 0){
               return false;
           }
       return true;
   }

   void print(){
       for (int i = 0; i < num_vertices; i++){
           for (int j = 0; j < num_vertices; j++){
               std::cout << gr[i][j] << " ";
           }
           std::cout << std::endl;
       }
   }

};

int main(){

    Graph G = Graph(14, 17);
    G.print();

    G.gr[0][1] = 0;
    G.gr[0][2] = 1;
    G.gr[0][3] = 2;
    
    G.gr[1][0] = 0;
    G.gr[1][4] = 3;
    G.gr[1][5] = 4;
    G.gr[1][6] = 5;

    G.gr[2][0] = 1;
    G.gr[2][7] = 6;
    G.gr[2][8] = 7;

    G.gr[3][0] = 2;
    G.gr[3][9] = 8;

    G.gr[4][1] = 3;
    G.gr[4][10] = 9;

    G.gr[5][1] = 4;
    G.gr[5][10] = 10;

    G.gr[6][1] = 5;
    G.gr[6][10] = 11;

    G.gr[7][2] = 6;
    G.gr[7][11] = 12;

    G.gr[8][2] = 7;
    G.gr[8][11] = 13;

    G.gr[9][3] = 8;
    G.gr[9][12] = 14;

    G.gr[10][4] = 9;
    G.gr[10][5] = 10;
    G.gr[10][6] = 11;
    G.gr[10][13] = 15;

    G.gr[11][7] = 12;
    G.gr[11][8] = 13;
    G.gr[11][13] = 16;

    G.gr[12][9] = 14;
    G.gr[12][13] = 17;

    G.gr[13][10] = 15;
    G.gr[13][11] = 16;
    G.gr[13][12] = 17;
   
    std::cout << G.DNS() << std::endl;

    std::ofstream fout;
    fout.open("output.json");

    fout << "{\n    \"vertices\": [\n";
    int edges[G.num_edges][2];
    for (int i = 0; i < G.num_vertices; i++){
        fout << "     {\n        \"id\": " << i << ",\n        \"edge_ids\": [";
        bool first_semicolon = 1;
        for (int j = 0; j < G.num_vertices; j++){
            if (G.gr[i][j] != -1){
                if (first_semicolon == 0){
                    fout << ", " << G.gr[i][j];
                }
                else{
                    first_semicolon = 0;
                    fout << G.gr[i][j];
                }
                edges[G.gr[i][j]][0] = i;
                edges[G.gr[i][j]][1] = j;
            }
        }
        if (i == G.num_vertices - 1){
            fout << "]\n      }\n ";
        }
        else{
            fout << "]\n      },\n ";
        }
    }
    fout << "        \n    ],\n";


    fout << "\n    \"edges\": [\n";
    for (int i = 0; i < G.num_edges; i++) {
        if (i == G.num_edges - 1){
            fout << "      {\n        \"id\": " << i << ",\n        \"vertex_ids\": ["
                << edges[i][0] << ", " << edges[i][1] << "]\n      } \n";
        }
        else{
            fout << "      {\n        \"id\": " << i << ",\n        \"vertex_ids\": ["
                << edges[i][0] << ", " << edges[i][1] << "]\n      }, \n";
        }
    }
    fout << "        \n    ]\n}\n\n";
    fout.close();
    
    return 0;
}


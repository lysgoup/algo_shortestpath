/*
Refernece
  Blog: 
    https://wooono.tistory.com/462
    https://makerejoicegames.tistory.com/104
    https://huilife.tistory.com/20
    https://boycoding.tistory.com/212
    https://life-with-coding.tistory.com/408
*/

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#include <climits>
#include <vector>
#include <iomanip>

using namespace std;
typedef struct _vertex{
  int distance;
  string from;
  string name;
}vertex;

struct compare{
  bool operator()(vertex &a, vertex &b){
    return a.distance > b.distance;
  }
};
priority_queue <vertex,vector<vertex>,compare> pq;

int get_vertex_num();
void Read_from_file(string *vertex_name[], string **edges);
void initialize_vertex(vertex *cities[], int num);
int dijkstra(vertex *cities[], string **edges, int source, int num);

int get_vertex_num(){
  ifstream file("hw6-1.txt");
  string line;
  int count = 0;
  if (file.is_open()) {
    string line;
    while (getline(file, line)) {
      count++;
    }
    file.close();
  } else {
    cout << "Failed to open the file." << endl;
  }
  return count;
}

void Read_from_file(vertex *cities[], string **edges){
  ifstream file("hw6-1.txt");
  if (file.is_open()) {
    string line;
    int i = 0;
    while (getline(file, line)) {
      istringstream ss(line);
      string word;
      ss >> word;
      cities[i]->name = word;
      int j=0;
      while (ss >> word) {
        edges[i][j] = word;
        j++;
      }
      i++;
    }
    file.close();
  } else {
      cout << "Failed to open the file." << endl;
  }
}

void initialize_vertex(vertex *cities[], int num){
  for(int i=0;i<num;i++){
    cities[i]->distance = INT_MAX;
    cities[i]->from = "\0";
  }
}

void Relax(string name, int source_distance, string weight){
  vector<vertex> updatedVertices;
  while (!pq.empty()) {
        vertex topVertex = pq.top();
        pq.pop();

        if (topVertex.name == name) {
          // cout << "check: " << topVertex.name << ":" << topVertex.distance << endl;
            if(topVertex.distance > (source_distance+stoi(weight))){
              // cout << "here" << endl;
              topVertex.distance = source_distance+stoi(weight);
              topVertex.from = name;
            };
          // cout << "check: " << topVertex.name << ":" << topVertex.distance << endl;
        }
        // cout << "check: " << topVertex.name << ":" << topVertex.distance << endl;
        updatedVertices.push_back(topVertex);
    }

    for (size_t i = 0; i < updatedVertices.size(); ++i) {
        pq.push(updatedVertices[i]);
    }
}

void dijkstra(int dis[], vertex *cities[], string **edges, int source, int num){
  initialize_vertex(cities,num);
  pq = priority_queue <vertex,vector<vertex>,compare>();
  cities[source]->distance = 0;
  for(int i=0;i<num;i++){
    pq.push(*cities[i]);
  }
  while(!pq.empty()){
    vertex delmin = pq.top();
    // cout << "pop: " << delmin.name << endl;
    pq.pop();
    int location = 0;
    while(location<num){
      if(cities[location]->name == delmin.name) break;
      location++;
    }
    dis[location] = delmin.distance;
    for(int j=0;j<num;j++){
      if(edges[location][j]!="INF" && (location!=j)){
        Relax(cities[j]->name,delmin.distance,edges[location][j]);
      }
    }
  }


  while(!pq.empty()){
    cout << pq.top().distance << endl;
    pq.pop();
  }
  while(!pq.empty()){
    cout << "check" << endl;
    pq.pop();
  }
}

int main(){
  int v = get_vertex_num();
  int source = 0;
  string *vertex_name[v];
  vertex *cities[v];
  string **edges;
  for (int i = 0; i < v; i++) {
    cities[i] = new vertex;
  }
  for (int i = 0; i < v; i++) {
    vertex_name[i] = new string;
  }
  edges = new string *[v];
  for(int i=0; i<v; i++){
    edges[i] = new string[v];
  }

  Read_from_file(cities, edges);
  int shortest_path[v][v];
  cout << "The followings are shortest distances between cities with Dijkstra's algorithm." << endl;
  cout << setw(10) << "";
  for (int i = 0; i < v; i++) {
    cout << setw(10) << cities[i]->name;
  }
  cout << endl;
  for(int i=0;i<v;i++){
    source = i;
    int dis_from_i[v];
    dijkstra(dis_from_i,cities,edges,i,v);
    for(int j=0;j<v;j++){
      shortest_path[i][j]=dis_from_i[j];
    }
  }
  for (int i = 0; i < v; i++) {
    cout << setw(10) << cities[i]->name;
    for (int j = 0; j < v; j++) {
    cout << setw(10) << shortest_path[i][j];
    }
    cout << endl;
  }


  cout << "The followings are shortest distances between cities with Floyd algorithm as follows." << endl;
  


  for (int i = 0; i < v; i++) {
    delete cities[i];
  }
  for (int i = 0; i < v; i++) {
    delete vertex_name[i];
  }
  for (int i = 0; i < v; i++) {
    delete edges[i];
  }
  delete edges;
  return 0;
}
#include <iostream> 
#include <fstream>
#include <sstream>
#include <limits.h> 
#include <string.h> 
#include <queue>
#include <list> 

#define INF INT_MAX

using namespace std; 

struct EdgeInfo{
	int start;
	int end;
	int capacity;
};

int num_V, num_E, sink;

bool bfs(int** res_graph, int s, int t, int parent[]) 
{ 
	bool gray[num_V]; 
	memset(gray, 0, sizeof(gray)); 
	queue <int> q; 
	q.push(s); 
	gray[s] = true; 
	parent[s] = -1; 
	while (!q.empty()){ 
		int u = q.front(); 
		q.pop(); 
		for (int v = 0; v < num_V; v++){ 
			if (gray[v] == false && res_graph[u][v] > 0) { 
				q.push(v); 
				parent[v] = u; 
				gray[v] = true; 
			} 
		} 
	} 
	return (gray[t] == true); 
} 

int edmons_karp(int** graph, int s, int t) 
{ 
	int u, v;  
	int** res_graph = new int*[num_V];
	for(int i = 0; i < num_V; i++)
		res_graph[i] = new int[num_V];

	for (u = 0; u < num_V; u++) 
		for (v = 0; v < num_V; v++) 
			res_graph[u][v] = graph[u][v]; 

	int parent[num_V];
	int max_flow = 0;
	while (bfs(res_graph, s, t, parent)){ 
		int path_flow = INT_MAX; 
		for (v = t; v != s; v=parent[v]){ 
			u = parent[v]; 
			path_flow = min(path_flow, res_graph[u][v]); 
		} 
		for (v = t; v != s; v = parent[v]){ 
			u = parent[v]; 
			res_graph[u][v] -= path_flow; 
			res_graph[v][u] += path_flow; 
		} 
		max_flow += path_flow; 
	}
	for (int i = 0; i < num_V; i++){
		delete[] res_graph[i];
	}
	delete[] res_graph;
	return max_flow; 
} 


void build_graph(int **graph, 
		list<int>& Warehouses, 
		list<int>& Stores, 
		list<int>& NodeCaps, 
		struct EdgeInfo edge[])
{
	list<int>::iterator itr;
	int index = 1;
	for(int i = 0; i < num_E; i++)
		graph[edge[i].start][num_V - sink + edge[i].end] = edge[i].capacity;
	for(itr = Warehouses.begin(); itr != Warehouses.end(); ++itr)
		graph[0][*itr] = INF;
	for(itr = Stores.begin(); itr != Stores.end(); ++itr)
		graph[*itr][sink - 1] = INF;
	if (!NodeCaps.empty()){
		for(itr = NodeCaps.begin(); itr != NodeCaps.end(); ++itr){
			graph[index + sink][index] = *itr;
			index++;
		}
	}
}

int main(int argc, char* argv[])
{
	ifstream fin;
	list<int> Warehouses, Stores, NodeCaps;
	int num_place, line = 0;

	fin.open(argv[1]);
	fin >> num_place;
	sink = num_place + 2;
	string str;
	while (getline(fin, str)){
		line ++;
		if (line == 3){
			istringstream token(str);
			int key;
			while(token >> key)
				Warehouses.push_back(key);
		}
		else if (line == 4){
			istringstream token(str);
			int key;
			while(token >> key)
				Stores.push_back(key);
		}
		else if (line == 6){
			istringstream token(str);
			int key;
			string key_str;
			for (int i = 0; i < num_place; i++){
				token >> key_str;
				if(key_str == "Inf"){
					NodeCaps.push_back(INF);
				}
				else{
					istringstream(key_str) >> key;
					NodeCaps.push_back(key);
				}
			}
		}
		else if (line == 7){
			break;
		}
	}
	fin >> num_E;
	EdgeInfo edge[num_E];
	for (int i = 0; i < num_E; i++){
		fin >> edge[i].start;
		fin >> edge[i].end;
		fin >> edge[i].capacity;
	}
	fin.close();

	if (NodeCaps.empty())
		num_V = sink;
	else
		num_V = 2 * sink;

	int** graph = new int*[num_V];
	for(int i = 0; i < num_V; i++)
		graph[i] = new int[num_V];
	for(int i = 0; i < num_V; i++){
		for(int j = 0; j < num_V; j++){
			graph[i][j] = 0;
		}
	}

	build_graph(graph, Warehouses, Stores, NodeCaps, edge);

	ofstream fout;
	fout.open(argv[2]);	
	fout << edmons_karp(graph, 0, sink - 1);
	fout.close(); 
	
	/*
	for(int i = 0; i < num_V; i++){
		for(int j = 0; j < num_V; j++){
			cout << graph[i][j] << " ";
	   }
		cout << endl;
	}
	*/

	//cout << "maxflow = " << edmons_karp(graph, 0, sink - 1) << endl;

	for (int i = 0; i < num_V; i++){
		delete[] graph[i];
	}
	delete[] graph;
	return 0;
}

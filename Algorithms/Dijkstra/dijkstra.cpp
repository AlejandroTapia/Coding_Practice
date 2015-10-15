#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;
/**
 * Author: Alejandro Tapia
 * 
 * Description: Small program containing a Graph class, its implementation and
 * the implementation of Dijkstra's algorithm to find the shortest path from one
 * node to another
 * 
 * */

class Graph {
	private: 
	map<char, vector<pair<char, int> > > graph;
	set<char> allNodes;
	
	public:
	Graph(char node);
	void insert (char parent, char child, int weight);
	void remove (char node);
	int getSize();
	map<char, vector<pair<char, int> > > getGraph();
	set<char> getAllNodes();
};

void printGraph(map<char, vector<pair<char, int> > > graph);
int findShortestPath(Graph theGraph, char start, char end);

int main() {
	Graph myGraph = Graph('a');
	// myGraph.insert('a', 'b', 10);
	// myGraph.insert('b', 'c', 3);
	// myGraph.insert('b', 'd', 6);
	// myGraph.insert('a', 'd', 20);
	// myGraph.insert('d', 'b', 1);
	
	// char start = 'a';
	// char end = 'c';
	
	// cout << "Shortest path from " << start << " to " << end << " is: " << 
	// findShortestPath(myGraph, start, end) <<endl;
	
	myGraph.insert('a', 'z', 100);
	myGraph.insert('b', 'z', 100);
	myGraph.insert('c', 'z', 100);
	myGraph.insert('c', 'd', 100);
	myGraph.insert('d', 'z', 1);
	myGraph.insert('a', 'd', 1);
	
	char start = 'a';
	char end = 'z';
	
	cout << "Shortest path from " << start << " to " << end << " is: " << 
	findShortestPath(myGraph, start, end) <<endl;
	
	
	//printGraph(myGraph.getGraph());
	
	return 0;
}

void printGraph(map<char, vector<pair<char, int> > > graph) {
	map<char, vector<pair<char, int> > >::iterator itr;
	
	for (itr = graph.begin(); itr != graph.end(); itr++) {
		cout << "Parent: " << itr->first <<endl;
		vector<pair<char, int> >::iterator itr2;
		int count = 1;
		for(itr2 = itr->second.begin(); itr2 != itr->second.end(); itr2++) {
			cout << "Child" << count << ": " << itr2->first << "  Distance: " 
			<< itr2->second << endl;
			count++;
		}
	}
}

struct compare {
	bool operator()(const pair<char, int>& l, const pair<char, int>& r) {
		return l.second > r.second;
	}
};

int findShortestPath(Graph theGraph, char start, char end) {
 	map<char, vector<pair<char, int> > > graph = theGraph.getGraph();
 	set<char> allNodes = theGraph.getAllNodes();
 	
	priority_queue<pair<char, int>, vector<pair<char, int> >, compare > theQueue;
	map<char, int> distance;
	map<char, bool> visited;
	set<char>::iterator itr;
	
	for(itr = allNodes.begin(); itr != allNodes.end(); itr++) {
		distance[*itr] = 999;
		visited[*itr] = false;
	}
	distance[start] = 0;
	visited[start] = true;
	
	pair<char, int> temp;
	temp.first = start;
	temp.second = 0;
	
	theQueue.push(temp);
	char current = start;
	
	while (!theQueue.empty()) {
		// cout << "Current: " << current <<endl;
		vector<pair<char, int> > neighbors = graph[current];
		vector<pair<char, int> >::iterator itr;
		
		for (itr = neighbors.begin(); itr != neighbors.end(); itr++) {
			// cout << itr->first << " distance before: " << distance[itr->first] <<endl;
			distance[itr->first] = min(distance[itr->first], (distance[current] + itr->second));
			// cout << itr->first << " distance after: " << distance[itr->first] <<endl;
			
			temp.first = itr->first;
			temp.second = distance[itr->first];
			
			if (!visited[itr->first]) {
				theQueue.push(temp);
			}
		}
		visited[current] = true;
		theQueue.pop();
		current = theQueue.top().first;
	}
	if (visited[end]) {
		return distance[end];
	} else if (theQueue.empty() && !visited[end]) {
		cout << "Can't get to destination" <<endl;
		return -999;
	}
}

Graph::Graph(char node) {
	this->graph[node];
	this->allNodes.insert(node);
}

void Graph::insert (char parent, char child, int weight) {
	pair<char, int> node;
	node.first = child;
	node.second = weight;
	
	this->graph[parent].push_back(node);
	this->allNodes.insert(parent);
	this->allNodes.insert(child);
}

map<char, vector<pair<char, int> > > Graph::getGraph() {
	return this->graph;
}

set<char> Graph::getAllNodes() {
	return this->allNodes;
}


//
// FILE:            Find_Shortest_Path.cpp
// IMPLEMENTED BY:  Lucien Maurice
// EMAIL:           Luciencmaurice@gmail.com
//
// HW 25.12

#include <iostream>
#include <fstream>
#include "MST.h"
#include "Edge.h"
#include "Tree.h"
#include "Graph.h"
#include "WeightedEdge.h"
#include "WeightedGraph.h"
#include "ShortestPathTree.h"

using namespace std;

void split(string s, vector<int>& tokens);

int main(int argc, const char* argv[]) {
    ifstream infile;
    string filename, s;
    int numberOfVertices, start, end;
    vector<WeightedEdge> edges;

    cout << "Enter a file name: ";
    getline(cin, filename);
    cout << "\nEnter two vertices (integer indexes): ";
    cin >> start >> end;
    infile.open(filename);
    infile >> numberOfVertices;
    getline(infile, s);
    while (getline(infile, s)) {
        vector<int> tokens;
        split(s, tokens);
        for (int i = 0; i < tokens.size(); i += 3) {
            edges.push_back(WeightedEdge(tokens[i], tokens[i + 1], tokens[i + 2]));
            edges.push_back(WeightedEdge(tokens[i + 1], tokens[i], tokens[i + 2]));
        }
    }
    infile.close();

    WeightedGraph<int> g(numberOfVertices, edges);
    cout << "The number of vertices is " << numberOfVertices << endl;
    g.printWeightedEdges();
    ShortestPathTree tree = g.getShortestPath(g.getIndex(start));
    vector<int> path = tree.getPath(g.getIndex(end));
    cout << "A path from " << start << " to " << end << ": ";
    for (int i = path.size() - 1; i >= 0; i--)
        cout << path[i] << " ";
    cout << endl;
    return 0;
}

void split(string s, vector<int>& tokens) {
    string temp = "";
    for (int i = 0; i < s.length(); i++) {
        if (isdigit(s[i]))
            temp += s[i];
        else {
            if (temp != "") {
                tokens.push_back(stoi(temp));
                temp = "";
            }
        }
    }
}

/*
* 
 Enter a file name: /Users/drdoo\Desktop\Current Classes\C++ Data Structures and Algorithms\Week 15 (12_7) CH 15 Weighted Graphs\Weighted Graph.txt

 Enter two vertices (integer indexes): 0 1
 The number of vertices is 6
 Vertex 0(0): (0, 1, 100) (0, 2, 3)
 Vertex 1(1): (1, 0, 100) (1, 3, 20)
 Vertex 2(2): (2, 0, 3) (2, 3, 40) (2, 4, 2)
 Vertex 3(3): (3, 1, 20) (3, 2, 40) (3, 4, 5) (3, 5, 5)
 Vertex 4(4): (4, 2, 2) (4, 3, 5) (4, 5, 9)
 Vertex 5(5): (5, 3, 5) (5, 4, 9)
 A path from 0 to 1: 0 2 4 3 1

 */

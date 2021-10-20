#ifndef WEIGHTEDGRAPH_H
#define WEIGHTEDGRAPH_H

#include "Graph.h"
#include "WeightedEdge.h"
#include "MST.h"
#include "ShortestPathTree.h"
#include <queue> // for priority_queue
#include <functional> // for greater

// hints:
// when you use .size(), compare with unsigned int
// for protected members, access with this->
// greater needs <functional>
// for function para, use const &, not just &

template <typename T>
class WeightedGraph : public Graph<T>
{
public:
  /** Construct an empty graph */
  WeightedGraph();

  /** Construct a graph from vertices and edges objects */
  WeightedGraph(vector<T> vertices, vector<WeightedEdge> &edges);

  /** Construct a graph with vertices 0, 1, ..., n-1 and
    *  edges in a vector */
  WeightedGraph(int numberOfVertices, vector<WeightedEdge> &edges);

  /** Print all edges in the weighted tree */
  void printWeightedEdges();

  /** Get a minimum spanning tree rooted at vertex 0 */
  MST getMinimumSpanningTree();

  /** Get a minimum spanning tree rooted at a specified vertex */
  MST getMinimumSpanningTree(int startingVertex);

  /** Find single-source shortest paths */
  ShortestPathTree getShortestPath(int sourceVertex);

private:
  /** Priority adjacency lists on edge weights */
  vector<priority_queue<WeightedEdge, vector<WeightedEdge>, greater<WeightedEdge> > > queues;

  /** Create adjacency lists as in an unweighted graph */
  void createAdjacencyLists(int numberOfVertices,
    vector<WeightedEdge> &edges);

  /** Create a vector of priority queues */
  void createQueues(int numberOfVertices,
  vector<WeightedEdge> &edges);

  /** Return true if v is in vector T */
  bool contains(vector<int> &T, int v);
};

const int INFINIT = 2147483647;

template <typename T>
WeightedGraph<T>::WeightedGraph()
{
}

template <typename T>
WeightedGraph<T>::WeightedGraph(vector<T> vertices, vector<WeightedEdge> &edges)
{
  // vertices is defined as protected in the Graph class
  this->vertices = vertices;

  // Create the adjacency list neighbors for the Graph class
  createAdjacencyLists(vertices.size(), edges);

  // Create the adjacency priority queues for weighted graph
  createQueues(vertices.size(), edges);
}

template <typename T>
WeightedGraph<T>::WeightedGraph(int numberOfVertices, vector<WeightedEdge> &edges)
{
  // vertices is defined as protected in the Graph class
  for (int i = 0; i < numberOfVertices; i++)
	  // I need this-> ??
	this->vertices.push_back(i); // vertices is {0, 1, 2, ..., n-1}

  // Create the adjacency list neighbors for the Graph class
  createAdjacencyLists(numberOfVertices, edges);

  // Create the adjacency priority queues for weighted graph
  createQueues(numberOfVertices, edges);
}

template <typename T>
void WeightedGraph<T>::createAdjacencyLists(int numberOfVertices, vector<WeightedEdge> &edges)
{
  // neighbors is defined as protected in the Graph class
  for (int i = 0; i < numberOfVertices; i++)
  {
	// I need this-> ?
    this->neighbors.push_back(vector<int>(0));
  }

  for (unsigned int i = 0; i < edges.size(); i++)
  {
    int u = edges[i].u;
    int v = edges[i].v;
    this->neighbors[u].push_back(v);
  }
}

template <typename T>
void WeightedGraph<T>::createQueues(int numberOfVertices, vector<WeightedEdge> &edges)
{
  for (int i = 0; i < numberOfVertices; i++)
  {
    queues.push_back(priority_queue<WeightedEdge,
    vector<WeightedEdge>, greater<WeightedEdge> >());
  }

  for (unsigned int i = 0; i < edges.size(); i++)
  {
    int u = edges[i].u;
    int v = edges[i].v;
    int weight = edges[i].weight;
    queues[u].push(WeightedEdge(u, v, weight));
  }
}

template <typename T>
void WeightedGraph<T>::printWeightedEdges()
{
  for (unsigned int i = 0; i < queues.size(); i++)
  {
    // Display all edges adjacent to vertex with index i
    cout << "Vertex " << i << ": ";

  // Get a copy of queues[i], so to keep original queue intact
  priority_queue<WeightedEdge, vector<WeightedEdge>,
    greater<WeightedEdge> > pQueue = queues[i];
    while (!pQueue.empty())
  {
      WeightedEdge edge = pQueue.top();
    pQueue.pop();
      cout << "(" << edge.u << ", " << edge.v << ", "
    << edge.weight << ") ";
    }
    cout << endl;
  }
}

template <typename T>
MST WeightedGraph<T>::getMinimumSpanningTree()
{
  return getMinimumSpanningTree(0);
}

template <typename T>
MST WeightedGraph<T>::getMinimumSpanningTree(int startingVertex)
{
  vector<int> T;
  // T initially contains the startingVertex;
  T.push_back(startingVertex);

  unsigned int numberOfVertices = this->vertices.size(); // Number of vertices
  vector<int> parent(numberOfVertices); // Parent of a vertex
  // Initially set the parent of all vertices to -1
  for (unsigned int i = 0; i < parent.size(); i++)
    parent[i] = -1;
  int totalWeight = 0; // Total weight of the tree thus far

  // Clone the queue, so as to keep the original queue intact
  vector<priority_queue<WeightedEdge, vector<WeightedEdge>,
    greater<WeightedEdge> > > queues = this->queues;

  // All vertices are found?
  while (T.size() < numberOfVertices)
  {
    // Search for the vertex with the smallest edge adjacent to
    // a vertex in T
    int v = -1;
    int smallestWeight = INFINIT;
    for (unsigned int i = 0; i < T.size(); i++)
    {
      int u = T[i];
      while (!queues[u].empty() && contains(T, queues[u].top().v))
      {
        // Remove the edge from queues[u] if the adjacent
        // vertex of u is already in T
        queues[u].pop();
      }

      if (queues[u].empty())
        continue; // Consider the next vertex in T

      // Current smallest weight on an edge adjacent to u
      WeightedEdge edge = queues[u].top();
      if (edge.weight < smallestWeight)
      {
        v = edge.v;
        smallestWeight = edge.weight;
        // If v is added to the tree, u will be its parent
        parent[v] = u;
      }
    } // End of for

    T.push_back(v); // Add a new vertex to the tree
    totalWeight += smallestWeight;
  } // End of while

  return MST(startingVertex, parent, T, totalWeight);
}

template <typename T>
bool WeightedGraph<T>::contains(vector<int> &T, int v)
{
  for (unsigned int i = 0; i < T.size(); i++)
  {
    if (T[i] == v) return true;
  }

  return false;
}

template <typename T>
ShortestPathTree WeightedGraph<T>::getShortestPath(int sourceVertex)
{
  // T stores the vertices whose path found so far
  vector<int> T;
  // T initially contains the sourceVertex;
  T.push_back(sourceVertex);

  // vertices is defined in the Graph class
  unsigned int numberOfVertices = this->vertices.size();

  // parent[v] stores the previous vertex of v in the path
  vector<int> parent(numberOfVertices);
  parent[sourceVertex] = -1; // The parent of source is set to -1

  // costs[v] stores the cost of the path from v to the source
  vector<int> costs(numberOfVertices);
  for (unsigned int i = 0; i < costs.size(); i++)
  {
    costs[i] = INFINIT; // Initial cost set to infinity
  }

  costs[sourceVertex] = 0; // Cost of source is 0

  // Clone the queue, so as to keep the original queue intact
  vector<priority_queue<WeightedEdge, vector<WeightedEdge>,
    greater<WeightedEdge> > > queues = this->queues;

  // Expand verticesFound
  while (T.size() < numberOfVertices)
  {
    int v = -1; // Vertex to be determined
    int smallestCost = INFINIT; // Set to infinity
    for (unsigned int i = 0; i < T.size(); i++)
    {
      int u = T[i];
      while (!queues[u].empty() && contains(T, queues[u].top().v))
        queues[u].pop(); // Remove the vertex in verticesFound

      if (queues[u].empty())
        continue; // Consider the next vertex in T

      WeightedEdge e = queues[u].top();
      if (costs[u] + e.weight < smallestCost)
      {
        v = e.v;
        smallestCost = costs[u] + e.weight;
        // If v is added to the tree, u will be its parent
        parent[v] = u;
      }
    } // End of for

    T.push_back(v); // Add a new vertex to the set
    costs[v] = smallestCost;
  } // End of while

  // Create a ShortestPathTree
  return ShortestPathTree(sourceVertex, parent, T, costs);
}

#endif

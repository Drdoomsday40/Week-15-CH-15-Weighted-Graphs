#include <iostream>
#include <string>
#include <vector>
#include "WeightedGraph.h"
#include "WeightedEdge.h"
using namespace std;

/** Print paths from all vertices to the source */
template <typename T>
void printAllPaths(ShortestPathTree &tree, vector<T> vertices)
{
  cout << "All shortest paths from " <<
    vertices[tree.getRoot()] << " are:" << endl;
  for (unsigned int i = 0; i < vertices.size(); i++)
  {
    cout << "To " << vertices[i] << ": ";

    // Print a path from i to the source
    vector<int> path = tree.getPath(i);
    for (int i = path.size() - 1; i >= 0; i--)
    {
      cout << vertices[path[i]] << " ";
    }

    cout << "(cost: " << tree.getCost(i) << ")" << endl;
  }
}

int main()
{
  // Vertices for graph in Figure 24.1
  string vertices[] = {"Seattle", "San Francisco", "Los Angeles",
    "Denver", "Kansas City", "Chicago", "Boston", "New York",
    "Atlanta", "Miami", "Dallas", "Houston"};

  // Edge array for graph in Figure 24.1
  int edges[][3] = {
    {0, 1, 807}, {0, 3, 1331}, {0, 5, 2097},
    {1, 0, 807}, {1, 2, 381}, {1, 3, 1267},
    {2, 1, 381}, {2, 3, 1015}, {2, 4, 1663}, {2, 10, 1435},
    {3, 0, 1331}, {3, 1, 1267}, {3, 2, 1015}, {3, 4, 599},
      {3, 5, 1003},
    {4, 2, 1663}, {4, 3, 599}, {4, 5, 533}, {4, 7, 1260},
      {4, 8, 864}, {4, 10, 496},
    {5, 0, 2097}, {5, 3, 1003}, {5, 4, 533},
      {5, 6, 983}, {5, 7, 787},
    {6, 5, 983}, {6, 7, 214},
    {7, 4, 1260}, {7, 5, 787}, {7, 6, 214}, {7, 8, 888},
    {8, 4, 864}, {8, 7, 888}, {8, 9, 661},
      {8, 10, 781}, {8, 11, 810},
    {9, 8, 661}, {9, 11, 1187},
    {10, 2, 1435}, {10, 4, 496}, {10, 8, 781}, {10, 11, 239},
    {11, 8, 810}, {11, 9, 1187}, {11, 10, 239}
  };
  const int NUMBER_OF_EDGES = 46; // 46 edges in Figure 24.1

  // Create a vector for vertices
  vector<string> vectorOfVertices(12);
  copy(vertices, vertices + 12, vectorOfVertices.begin());

  // Create a vector for edges
  vector<WeightedEdge> edgeVector;
  for (int i = 0; i < NUMBER_OF_EDGES; i++)
    edgeVector.push_back(WeightedEdge(edges[i][0],
    edges[i][1], edges[i][2]));

  WeightedGraph<string> graph1(vectorOfVertices, edgeVector);
  ShortestPathTree tree = graph1.getShortestPath(5);
  printAllPaths<string>(tree, graph1.getVertices());

  // Create a graph for Figure 24.3(a)
  int edges2[][3] =
  {
    {0, 1, 2}, {0, 3, 8},
    {1, 0, 2}, {1, 2, 7}, {1, 3, 3},
    {2, 1, 7}, {2, 3, 4}, {2, 4, 5},
    {3, 0, 8}, {3, 1, 3}, {3, 2, 4}, {3, 4, 6},
    {4, 2, 5}, {4, 3, 6}
  }; // 14 edges in Figure 24.3(a)

  const int NUMBER_OF_EDGES2 = 14; // 14 edges in Figure 24.3(a)

  vector<WeightedEdge> edgeVector2;
  for (int i = 0; i < NUMBER_OF_EDGES2; i++)
    edgeVector2.push_back(WeightedEdge(edges2[i][0],
    edges2[i][1], edges2[i][2]));

  WeightedGraph<int> graph2(5, edgeVector2); // 5 vertices in graph2
  ShortestPathTree tree2 = graph2.getShortestPath(3);
  printAllPaths<int>(tree2, graph2.getVertices());
  system("pause");
  return 0;
}

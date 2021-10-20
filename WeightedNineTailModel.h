#ifndef WEIGHTEDNINETAILMODEL_H
#define WEIGHTEDNINETAILMODEL_H

#include "NineTailModel.h"
#include "WeightedGraph.h"

using namespace std;

class WeightedNineTailModel : public NineTailModel
{
public:
  /** Construct a model for the Nine Tail problem */
  WeightedNineTailModel();

  /** Get the number of the flips from the target to u */
  int getNumberOfFlips(int u);

private:
  /** ShortestPathTree rooted at the target node 511 */
  ShortestPathTree spTree;

  /** Return a vector of Edge objects for the graph */
  /** Create edges among nodes */
  vector<WeightedEdge> getEdges();

  /** Get the number of flips from u to v */
  int getNumberOfFlips(int u, int v);
};

WeightedNineTailModel::WeightedNineTailModel()
{
  // Create edges
  vector<WeightedEdge> edges = getEdges();

  // Build a graph
  WeightedGraph<int> graph(NUMBER_OF_NODES, edges);

  // Build a shortest path tree rooted at the target node
  spTree = graph.getShortestPath(511);

  // The functions in NineTailModel use the tree property
  tree = spTree;
}

vector<WeightedEdge> WeightedNineTailModel::getEdges()
{
  vector<WeightedEdge> edges;

  for (int u = 0; u < NUMBER_OF_NODES; u++)
  {
    vector<char> node = getNode(u);
    for (int k = 0; k < 9; k++)
    {
      if (node[k] == 'H')
      {
        int v = getFlippedNode(node, k);
        int numberOfFlips = getNumberOfFlips(u, v);
        // Add edge (v, u) for a legal move from node u to node v
        // with weight numberOfFlips
        edges.push_back(WeightedEdge(v, u, numberOfFlips));
      }
    }
  }

  return edges;
}

int WeightedNineTailModel::getNumberOfFlips(int u, int v)
{
  vector<char> node1 = getNode(u);
  vector<char> node2 = getNode(v);

  int count = 0; // Count the number of different cells
  for (unsigned int i = 0; i < node1.size(); i++)
    if (node1[i] != node2[i]) count++;

  return count;
}

int WeightedNineTailModel::getNumberOfFlips(int u)
{
  return spTree.getCost(u);
}
#endif

#ifndef NINETAILMODEL_H
#define NINETAILMODEL_H

#include "Graph.h"
#include "Edge.h"

using namespace std;

const int NUMBER_OF_NODES = 512;

class NineTailModel
{
public:
  /** Construct a model for the Nine Tail problem */
  NineTailModel();

  /** Return the index of the node */
  int getIndex(vector<char> node);

  /** Return the node for the index */
  vector<char> getNode(int index);

  /** Return the shortest path of vertices from the specified
   *  node to the root */
  vector<int> getShortestPath(int nodeIndex);

  /** Print a node to the console */
  void printNode(const vector<char> &node);

protected:
  Tree tree;

  /** Return a vector of Edge objects for the graph */
  /** Create edges among nodes */
  vector<Edge> getEdges();

  /** Return the index of the node that is the result of flipping
   *  the node at the specified position */
  int getFlippedNode(vector<char> node, int position);

  /** Flip a cell at the specified row and column */
  void flipACell(vector<char> &node, int row, int column);
};

NineTailModel::NineTailModel()
{
  // Create edges
  vector<Edge> edges = getEdges();

  // Build a graph
  Graph<int> graph(NUMBER_OF_NODES, edges);

  // Build a BFS tree rooted at the target node
  tree = graph.bfs(511);
}

vector<Edge> NineTailModel::getEdges()
{
  vector<Edge> edges;

  for (int u = 0; u < NUMBER_OF_NODES; u++)
  {
    vector<char> node = getNode(u);
    for (int k = 0; k < 9; k++)
    {
      if (node[k] == 'H')
      {
        int v = getFlippedNode(node, k);
        // Add edge (v, u) for a legal move from node u to node v
        edges.push_back(Edge(v, u));
      }
    }
  }

  return edges;
}

int NineTailModel::getFlippedNode(vector<char> node, int position)
{
  int row = position / 3;
  int column = position % 3;

  flipACell(node, row, column);
  flipACell(node, row - 1, column);
  flipACell(node, row + 1, column);
  flipACell(node, row, column - 1);
  flipACell(node, row, column + 1);

  return getIndex(node);
}

void NineTailModel::flipACell(vector<char> &node,
  int row, int column)
{
  if (row >= 0 && row <= 2 && column >= 0 && column <= 2)
  { // Within boundary
    if (node[row * 3 + column] == 'H')
      node[row * 3 + column] = 'T'; // Flip from H to T
    else
      node[row * 3 + column] = 'H'; // Flip from T to H
  }
}

int NineTailModel::getIndex(vector<char> node)
{
  int result = 0;

  for (int i = 0; i < 9; i++)
    if (node[i] == 'T')
      result = result * 2 + 1;
    else
      result = result * 2 + 0;

  return result;
}

vector<char> NineTailModel::getNode(int index)
{
  vector<char> result(9);

  for (int i = 0; i < 9; i++) {
    int digit = index % 2;
    if (digit == 0)
      result[8 - i] = 'H';
    else
      result[8 - i] = 'T';
    index = index / 2;
  }

  return result;
}

vector<int> NineTailModel::getShortestPath(int nodeIndex)
{
  return tree.getPath(nodeIndex);
}


void NineTailModel::printNode(const vector<char> &node)
{
  for (int i = 0; i < 9; i++)
    if (i % 3 != 2)
      cout << node[i];
    else
      cout << node[i] << endl;

  cout << endl;
}

#endif

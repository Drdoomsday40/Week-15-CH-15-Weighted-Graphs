#ifndef SHORTESTPATHTREE_H
#define SHORTESTPATHTREE_H

#include "Tree.h"

class ShortestPathTree : public Tree
{
public:
  /** Create an empty ShortestPathTree */
  ShortestPathTree()
  {
  }

  /** Construct a tree with root, parent, searchOrders,
    * and cost */
  ShortestPathTree(int root, vector<int> parent, vector<int>
    searchOrders, vector<int> costs)
    : Tree(root, parent, searchOrders)
  {
    this->costs = costs;
  }

  /** Return the cost for the path from the source to vertex v. */
  int getCost(int v)
  {
    return costs[v];
  }

private:
  vector<int> costs;
};
#endif

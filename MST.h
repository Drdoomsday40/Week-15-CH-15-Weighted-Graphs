#ifndef MST_H
#define MST_H

#include "Tree.h"

class MST : public Tree
{
public:
  /** Create an empty MST */
  MST()
  {
  }

  /** Construct a tree with root, parent, searchOrders,
    * and total weight */
  MST(int root, vector<int> parent, vector<int> searchOrders,
    int totalWeight) : Tree(root, parent, searchOrders)
  {
    this->totalWeight = totalWeight;
  }

  /** Return the total weight of the tree */
  int getTotalWeight()
  {
    return totalWeight;
  }

private:
  int totalWeight;
};
#endif

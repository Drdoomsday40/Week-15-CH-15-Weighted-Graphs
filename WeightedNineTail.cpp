#include <iostream>
#include <vector>
#include "WeightedNineTailModel.h"
using namespace std;

int main()
{
  // Prompt the user to enter nine coins H and T's
  cout << "Enter an initial nine coin H and T's: " << endl;
  vector<char> initialNode(9);

  for (int i = 0; i < 9; i++)
    cin >> initialNode[i];

  cout << "The steps to flip the coins are " << endl;
  WeightedNineTailModel model;
  vector<int> path =
    model.getShortestPath(model.getIndex(initialNode));

  for (unsigned int i = 0; i < path.size(); i++)
    model.printNode(model.getNode(path[i]));

  cout << "The number of flips is " <<
    model.getNumberOfFlips(model.getIndex(initialNode)) << endl;
  system("pause");
  return 0;
}

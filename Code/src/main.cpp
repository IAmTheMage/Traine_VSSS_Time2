#include "../include/Utils.h"
#include <iostream>
using namespace std;


int main()
{
  Point2f pos1 = {5, 7}, pos2 = {1, 13};
  float dist = Utils::getDist(pos1, pos2);

  cout << "A distancia eh: " << dist << endl;
  return 0;
}
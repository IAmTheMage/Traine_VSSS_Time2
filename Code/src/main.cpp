#include "../include/Utils.h"
#include <iostream>
using namespace std;

int main() {
    Point2f pos1 = {16, 15}, pos2 = {19, 9};
    float theta = Utils::getAngle(pos2, pos1);
    cout << theta << endl;
}
/**
  * Partner1:
  * Name: Jiaqi Fan
  * PID: A12584051
  * Partner2:
  * Name: Xuanru Zhu
  * PID: A91064234
  * Date: 3/13/2017
  * PA4
  */
// this is edge.cpp file for building graph
// edge contain the shared movie about the two actors
// also the weight is also inside edge

#include "Edge.h"

using namespace std;
//operator < to check the weight of two actors
bool Edge::operator<(const Edge& other) const{
  if(weight != other.weight){
    return weight > other.weight;
  }
  else{
    return false;
  }
}

//call 
Edge::~Edge(){

}

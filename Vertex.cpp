/**
  * Partner1:
  * Name: Jiaqi Fan
  * PID: A12584051
  * Partner2:
  * Name: Xuanru Zhu
  * PID: A91064234
  * Date: 3/02/2017
  * PA4
  */
// this is vertex.cpp file for buiding graph
// vertex contain the information about the actor

#include "Vertex.h"

using namespace std;

//dectructor used to clean the edge
Vertex::~Vertex(){
  for(int i = 0; i < edges.size(); i++){
    delete edges[i];
  }
  for(auto iter = weighted_edges.begin(); 
		  iter != weighted_edges.end(); iter++){
    delete iter->second;
  }
}

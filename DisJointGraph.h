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
// this is DisJointGraph.h file used for actor connection
// this file contain method/ helper method for writing actor connections

#ifndef DISJOINTGRAPH_H
#define DISJOINTGRAPH_H

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include "Vertex.h"
#include "Edge.h"

using namespace std;

class DisJointGraph {
protected:
  //handle magic number
  int infinity = -1;
  //the oldest and newest 
  int oldest = infinity;
  int newest = infinity;
  //hashmaop for store actors
  std::unordered_map<std::string, Vertex*> actors;
  //hashmap for graph
  std::unordered_map<int, std::unordered_map<std::string,
	  	    vector<Vertex*>*>*> graphBuild;
public:
  //constructor
  DisJointGraph(void);
  //desctructor
  ~DisJointGraph(); 
 /** You can modify this method definition as you wish
  *
  * Load the graph from a tab-delimited file 
  * of actor->movie relationships.
  * in_filename - input filename 
  * return true if file was loaded sucessfully, false otherwise
  */
  bool loadFromFile(const char* in_filename);
  /**
   * getter for get the oldest
   * return the oldest
   */
  int getOldest();
  /**
   * getter for get the newest
   * return the newest
   */
  int getNewest();
  /**
   * getter for get the actor nodes that we builded
   * return the actors graph
   */
  std::unordered_map<std::string, Vertex*>& getGraph();
  /**
   * getter for the whole graph
   * return the whole graph
   */
  std::unordered_map<int, std::unordered_map<std::string,
	  	    vector<Vertex*>*>*>& getBuild();

};

#endif // DISJOINTGRAPH_H

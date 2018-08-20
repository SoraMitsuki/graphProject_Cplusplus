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
// this is ActorGraph.h file for actually building graph
// This file is meant to exist as a container for starter code that you can 
// use to read the input file format
// defined in movie_casts.tsv.

#ifndef ACTORGRAPH_H
#define ACTORGRAPH_H

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include "Vertex.h"
#include "Edge.h"
// Maybe include some data structures here

using namespace std;

class EdgePairComp {
public:
  /*
   * operator function that compare the edge 1 and edge 2
   * PARAM@: two pairs of edge
   * return: true if edge 2 is greater than edge 1
   */
  bool operator()(std::pair<Vertex*, Edge*> edge_1, 
		  std::pair<Vertex*, Edge*> edge_2) const{
    return *(edge_1.second) < *(edge_2.second);
  }
};

class ActorGraph {
protected:
  
    // Maybe add class data structure(s) here
    std::unordered_map<std::string, Vertex*> actors;
    std::unordered_map<std::string, vector<Vertex*>*> graphBuild;

public:
    ActorGraph(void);

    // Maybe add some more methods here

    //destructor
    ~ActorGraph();

    /** You can modify this method definition as you wish
     *
     * Load the graph from a tab-delimited file 
     * of actor->movie relationships.
     * in_filename - input filename
     * use_weighted_edges - if true, compute edge 
     * weights as 1 + (2015 - movie_year), 
     * otherwise all edge weights will be 1
     
     * return true if file was loaded sucessfully, false otherwise
     */
    bool loadFromFile(const char* in_filename, bool use_weighted_edges);

    /** getGraph() method
     * this function take no param
     * return the actors map
     */
    std::unordered_map<std::string, Vertex*>& getGraph();
  
};


#endif // ACTORGRAPH_H

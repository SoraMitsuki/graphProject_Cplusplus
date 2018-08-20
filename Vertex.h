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
// this is vertex.h file for building graph
// vertex contain the information about the actor

#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <limits>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include "Edge.h"

using namespace std;


class Vertex{

public:
  //the name of actor
  std::string actor;
  //the connection bewteen other actor
  std::unordered_map<std::string, Edge*> weighted_edges;
  vector<Edge*> edges;
  int dist; // the distance from the source
  Edge* prev; // the recorded edge to the vertex previous in the path
  // the connection between actors in actors connection
  std::unordered_set<Vertex*> connection;
  Vertex* connect = NULL;
  int size = 1;
  bool done;
  //constrractor for makeing a vertex
  Vertex(std::string actor, int dist = -1, Edge* prev = 0, bool done = false):
  actor(actor), dist(dist), prev(prev), done(done) { }

  ~Vertex();
};
#endif // VERTEX_H

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
// this is edge.h file for building graph
// edge contain the shared movie about the two actors
// also the weight is also inside edge

#ifndef EDGE_H
#define EDGE_H

#include <iostream>
#include <limits>
#include <vector>
#include <queue>

class Vertex;

using namespace std;


class Edge{

public:
  //the movie that two actors share
  std::string movie;
  //this is the year of movie
  int movie_year;
  //two vertexs which are the two actors
  Vertex* vertex;
  //the weight of the edge
  int weight;
  //constructor for creating a edge
  Edge(std::string movie, int movie_year, Vertex* vertex, int weight):
  movie(movie), movie_year(movie_year), vertex(vertex), weight(weight) { }
  //operator less than override
  bool operator<(const Edge& other) const;
   
  ~Edge();
};

#endif // EDGE_H

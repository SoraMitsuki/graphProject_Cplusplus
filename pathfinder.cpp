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
// this is pathfinder.cpp file for find the shortest path between 2 actors
// this file was created from scretch used to find the shortest path for
// weighted and unweighted graph.

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include "ActorGraph.h"

/**
 * findWPath method used to find the weighted path and return it
 * this method take 3 arguments
 * param 1: the actor1 need to find 
 * param 2: the coactor that have the same movie with actor1
 * param 3: the graph that we build while loadFromFile
 * return: the path string
 */
std::string findWPath(std::string actor_1, std::string actor_2,
		     ActorGraph& graph){
  //use priority queue to begin seach
  std::priority_queue<std::pair<Vertex*, Edge*>, 
  std::vector<std::pair<Vertex*, Edge*>>, EdgePairComp> explore;
  //handle magic number
  int Infinity = -1;
  //get the graph that we build
  auto actors = graph.getGraph();
  //find the first actor print error message when not found
  auto iter = actors.find(actor_1);
  if(iter == actors.end()){
    return "Cannot find the first actor";
  }
  //find the second actor print error message when not found
  Vertex* start = iter->second;
  iter = actors.find(actor_2);
  if(iter == actors.end()){
    return "Cannot find the second actor";
  }
  //set a destination
  Vertex* dest = iter->second;
  start->dist = 0;
  //the pair to start
  std::pair<Vertex*, Edge*> startPair(start, 0);
  explore.push(startPair);
  //used to mark the visited path
  std::pair<Vertex*, Edge*> visited;
  std::pair<Vertex*, Edge*> toExplore;
  //ucsed to recycle the edge
  vector<Edge*> toDelete;
  vector<Vertex*> reset;
  reset.push_back(start);
  //start to find the path
  while(!explore.empty()){
    //mark the visited path
    visited = explore.top();
    explore.pop();
    //check if reaches destination
    if((visited.first)->done == false){
      (visited.first)->done = true;
      //if reached dest break
      if(visited.first == dest){
        break;
      }
      //loop through the graph
      for(auto iter = (visited.first)->weighted_edges.begin(); 
		      iter != (visited.first)->weighted_edges.end();
		      iter++){
	//calculate the distance
        int c = (visited.first)->dist + iter->second->weight;
	//if the current dist is less than node's dist and node's dist = -1
        if(c < iter->second->vertex->dist ||
	  iter->second->vertex->dist == Infinity){
	  //set the new dist
          iter->second->vertex->dist = c;
	  //set prev for the actor node
          iter->second->vertex->prev = new Edge(iter->second->movie,
	  //break line to handle onver 80 charactes
	  iter->second->movie_year, visited.first, c);
	  //enqueue the pairs
          std::pair<Vertex*, Edge*> toEnQueue(iter->second->vertex, 
	  iter->second->vertex->prev); //handle 80 characters
          explore.push(toEnQueue);
	  //add nodes to reset
          reset.push_back(iter->second->vertex);
	  //add path tp toDelete
          toDelete.push_back(iter->second->vertex->prev);
        }
      }
    }
  }
  //delete all the edges in toDelete
  if(visited.first != dest){
    for(int i = 0; i < toDelete.size(); i++){
      delete toDelete[i];
    }
    //reset the actor nodes-> done, dist, prev
    for(int j = 0; j < reset.size(); j++){
      reset[j]->done = false;
      reset[j]->dist = Infinity;
      reset[j]->prev = 0;
    }
    //no connection found reutrn error message
    return "No Connection";
  }
  else{
    Edge* prevE;
    Vertex* toExplore = dest;
    //set the format of output file
    std::string path = "(" + toExplore->actor + ")";
    do{
      //the format of output file
      prevE = toExplore->prev;
      path = "(" + prevE->vertex->actor + ")" + "--[" + prevE->movie +
              "#@" + std::to_string(prevE->movie_year) + "]-->" + path;
      toExplore = prevE->vertex;
    }while(toExplore->prev);
    //delete all the edges in toDelete
    for(int i = 0; i < toDelete.size(); i++){
      delete toDelete[i];
    }
    //reset the actor nodes done, dist and prev
    for(int j = 0; j < reset.size(); j++){
      reset[j]->done = false;
      reset[j]->dist = Infinity;
      reset[j]->prev = 0;
    }
    return path;
  } 
}

/**
 * findPath method used to find the shortest path and return it
 * this method take 3 arguments
 * param 1: the actor1 need to find 
 * param 2: the coactor that have the same movie with actor1
 * param 3: the graph that we build while loadFromFile
 * return: the path string
 */
std::string findUPath(std::string actor_1, std::string actor_2,
		     ActorGraph& graph){
  //create a queue used for explore
  queue<Vertex*> explore;
  int infinity = -1;
  //find the first actor, if not find print error message
  std::unordered_map<std::string, Vertex*>& actors = graph.getGraph();
  auto iter = actors.find(actor_1);
  if(iter == actors.end()){
    return "Cannot find the first Actor";
  }
  //find the second actor, if not find print error message
  Vertex* start = iter->second;
  iter = actors.find(actor_2);
  if(iter == actors.end()){
    return "Cannot find the second Actor";
  }
  //the is the destination vertex
  Vertex* dest = iter->second;
  start->dist = 0;
  start->done = true;
  explore.push(start); 
  //this is used to mark the visited vertex
  Vertex* visited;
  Vertex* toExplore;
  //for free the prev edge malloc
  vector<Edge*> toDelete;
  //for reset the vertex
  vector<Vertex*> reset;
  reset.push_back(start);
  //loop until the graph is not empty
  while(!explore.empty()){
    //start with the front
    visited = explore.front();
    explore.pop();
    //loop throught the edge size find all the path
    for(int i = 0; i < visited->edges.size(); i++){
      toExplore = visited->edges[i]->vertex;
      //if not done keep searching
      if(toExplore->done == false){
        toExplore->dist = visited->dist + 1;
        toExplore->prev = new Edge(visited->edges[i]->movie, 
			visited->edges[i]->movie_year, visited, 1);
	//push the previous to the toDelete
        toDelete.push_back(toExplore->prev);
	//mark true
        toExplore->done = true;
        explore.push(toExplore);
        reset.push_back(toExplore);
      }
      if(toExplore == dest){
        break;
      }
    }
    //if the explore reach the destination break
    if(toExplore == dest){
      break;
    }
  }
  //if the expore does not reach the destination
  if(toExplore != dest){
    //delete the edge vector and print no connection between the 2 actors
    for(int i = 0; i < toDelete.size(); i++){
      delete toDelete[i];
    }
    // to reset each vertex to the original graph
    for(int j = 0; j < reset.size(); j++){
      reset[j]->done = false;
      reset[j]->dist = -1;
      reset[j]->prev = 0;
    }
    return "No Connection";
  }
  else{
    Edge* prevE;
    //the format of the output file
    std::string path = "(" + toExplore->actor + ")";
    do{
      prevE = toExplore->prev;
      //print out the two actors and the movie name, movie year
      path = "(" + prevE->vertex->actor + ")" + "--[" + prevE->movie + 
	      "#@" + std::to_string(prevE->movie_year) + "]-->" + path;
      //reset toExplore and find again
      toExplore = prevE->vertex;
    }while(toExplore->prev);
    //delete the edge
    for(int i = 0; i < toDelete.size(); i++){
      delete toDelete[i];
    }
    // to reset each vertex to the original graph
    for(int j = 0; j < reset.size(); j++){
      reset[j]->done = false;
      reset[j]->dist = -1;
      reset[j]->prev = 0;
    }
    return path;
  }
}
/**
 * main method that need to be called
 * this method should have 4 argumnets
 * argv[1] = the file that contain movie actor information
 * argc[2] = the graph is weighted or unweighted
 * argv[3] = the file contain pair of actors
 * argv[4] = the output file that print out all the movie shared
 * between actor1 and actor2 
 */
int main(int argc, char** argv){
  //handle the magic number
  int args = 5;
  int arg_2 = 2;
  int arg_3 = 3;
  int arg_4 = 4;
  //this is decided weither is weighted or not
  bool weighted = false;
  //used to skip the header
  bool have_header = false;
  std::string path;
  //check for the input file
  ifstream testFile(argv[arg_3]);
  if(argc != args){
    std::cout << "Invalid number of input" << std::endl;
    return -1;
  }
  //create a graph
  ActorGraph graph;
  //when we want it unweighted
  if(*argv[arg_2] == 'u'){
    weighted = false;
  }
  //when we want it weighted
  else if(*argv[arg_2] == 'w'){
    weighted = true;
  }
  else{ //else invalid input
    std::cout << "Invalid Input" << std::endl;
    return -1;
  }
  //create the graph
  graph.loadFromFile(argv[1], weighted);
  //open the output file
  ofstream outFile(argv[arg_4]);
  //while the input file is not empty
  while(testFile){
    string s;
    //break when end of file
    if(!getline(testFile, s)){
      break;
    }
    //output the header into the output file
    if(!have_header){
      // skip the header
      outFile << "(actor)--[movie#@year]-->(actor)--..." << endl;
      have_header = true;
      continue;
    }
    
    istringstream ss(s);
    vector<string> record;
    //while the ss is not empty
    while(ss){
      string next;
      //read the line until hit tab put in next
      if(!getline(ss, next, '\t')){
        break;  
      }
      record.push_back(next);
    }
    if(record.size() != 2){
      // we should have exactly 2 colums
      continue;
    }
    //get the actor 1 and actor 2
    string actor_1(record[0]);
    string actor_2(record[1]);
    //call helper method to find the path
    if(weighted){
      path = findWPath(actor_1, actor_2, graph); 
    }
    else{
      path = findUPath(actor_1, actor_2, graph);
    }
    //output the path into the outfile
    outFile << path << endl;
  } 
  return 0;
}

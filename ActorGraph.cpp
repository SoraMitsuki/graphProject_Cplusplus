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
// this is ActorGraph.cpp file for actually building graph
// This file is meant to exist as a container for starter code that you can 
// use to read the input file format
// defined in movie_casts.tsv.
 
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "ActorGraph.h"

using namespace std;

ActorGraph::ActorGraph(void) {}
/** 
 * Load the graph from a tab-delimited file 
 * of actor->movie relationships.
 * in_filename - input filename
 * use_weighted_edges - if true, compute edge 
 * weights as 1 + (2015 - movie_year), 
 * otherwise all edge weights will be 1  
 * return true if file was loaded sucessfully, false otherwise
 */
bool ActorGraph::loadFromFile(const char* in_filename, bool use_weighted_edges){
  // Initialize the file stream
  ifstream infile(in_filename);
  //the number of edges
  int EDGES = 0;
  //used to skip the header of the infile
  bool have_header = false;
  // keep reading lines until the end of file is reached
  while(infile){
    string s;
    // get the next line
    if(!getline( infile, s )) break;
    if(!have_header) {
      // skip the header
      have_header = true;
      continue;
    }
    istringstream ss( s );
    //record hold the information in one line
    vector<string> record;
    while(ss){
      string next;
      // get the next string before hitting a tab character and put in next
      if(!getline( ss, next, '\t' )) break;
        record.push_back( next );
      }
      if(record.size() != 3) {
        // we should have exactly 3 columns
        continue;
      }
      //actor name is the first
      string actor_name(record[0]);
      //movie title is the second element in record
      string movie_title(record[1]);
      //movie year is the third element
      int movie_year = stoi(record[2]);
      //combine the year and the movie title
      string movie = record[1] + record[2];    
      // we have an actor/movie relationship, now what?
      if(actors.find(record[0]) == actors.end()){
	//create new vertex on the actor and put in vector actors
        Vertex* actor = new Vertex(record[0]);
        actors.insert({actor_name, actor});
      }
      //when the movie of the two actors are same
      if(graphBuild.find(movie) == graphBuild.end()){
	//create a coactors that have the same movie with the prev
        vector<Vertex*>* coActors = new vector<Vertex*>;
        std::unordered_map<std::string, Vertex*>::const_iterator 
		iter = actors.find(actor_name);
	//insert the coactor into the graph
        coActors->push_back(iter->second);
        graphBuild.insert({movie, coActors});
      }
      //when movie of the two actors are not same
      else{
	//create empty map to hold the movie that we found
        std::unordered_map<std::string, vector<Vertex*>*>::const_iterator 
		coActor_iter = graphBuild.find(movie);
	//empty map to hold the actor name
        std::unordered_map<std::string, Vertex*>::const_iterator 
		actor_iter = actors.find(actor_name);
	//create a new actor node
        Vertex* newActor = actor_iter->second;
	//loop through the coactor and create new edge
        for(int i = 0; i < coActor_iter->second->size(); i++){
	  //if it is weighted
          if(use_weighted_edges){
            std::string actorName = ((*(coActor_iter->second)))[i]->actor;
	    //weighted is 1 + 2015 - movie year
            int old = 1 + (2015 - movie_year);
	    //start find the weighted actor
            auto edge_iter = newActor->weighted_edges.find(actorName);
            if(edge_iter == newActor->weighted_edges.end()){
	      //if the actor found create two new edges 
	      //based on actor and movie year
              Edge* edge_1 = new Edge(movie_title, movie_year, newActor, old);
              Edge* edge_2 = new Edge(movie_title, movie_year, 
			     (*(coActor_iter->second))[i], old);
              EDGES += 2;
	      //add the edge and actor to the actor node
              newActor->weighted_edges.insert({actorName, edge_2});
	      //break the line it is over 80 characters
              ((*(coActor_iter->second))[i])->
	      weighted_edges.insert({actor_name, edge_1});
            }
	    //if current weight is less than the node weight
            else if(old < edge_iter->second->weight){
	      //delete the edge provent from memory leak
              delete  ((newActor->weighted_edges).find(actorName))->second;
              (newActor->weighted_edges).erase(actorName);
	      //delete the coactor edge also
              delete  (((*(coActor_iter->second))[i])->
		      weighted_edges.find(actor_name))->second;
              ((*(coActor_iter->second))[i])->weighted_edges.erase(actor_name);
	      //create two new edges 
              Edge* edge_1 = new Edge(movie_title, movie_year, newActor, old);
              Edge* edge_2 = new Edge(movie_title, movie_year, 
			     (*(coActor_iter->second))[i], old);
	      //and insert them into the actor node
              newActor->weighted_edges.insert({actorName, edge_2});
              ((*(coActor_iter->second))[i])->
	      weighted_edges.insert({actor_name, edge_1});
            }
            else{
              continue;
            }
          }
          else{
	    //if not the case create 2 new edges
            Edge* edge_1 = new Edge(movie_title, movie_year, newActor, 1);
            Edge* edge_2 = new Edge(movie_title, movie_year, 
			   (*(coActor_iter->second))[i], 1);
	    //push edge into the actor vertex
            ((*(coActor_iter->second))[i])->edges.push_back(edge_1);
            newActor->edges.push_back(edge_2);
          }
        }
        coActor_iter->second->push_back(newActor);
      }
  }
  //fail to read the infile 
  if(!infile.eof()) {
    cerr << "Failed to read " << in_filename << "!\n";
    return false;
  }
  //close the infile
  infile.close();
  //output the detail about the graph
  std::cout << actors.size() << ";" << graphBuild.size() 
	    << ";" << EDGES << endl;

  return true;
}

/** getGraph() method
 * this function take no param
 * return the actors map
 */
std::unordered_map<std::string, Vertex*>& ActorGraph::getGraph(){
  return actors;
}

//desctructor for clear the graph preventing from memory leak
ActorGraph::~ActorGraph(){
  //loop through the vector actors and clean
  for(std::unordered_map<std::string, Vertex*>::const_iterator 
      iter = actors.begin(); iter != actors.end(); iter++){
    delete iter->second;
  }
  //loop through vector graphBuild and clean
  for(std::unordered_map<std::string, vector<Vertex*>*>::const_iterator 
      iter = graphBuild.begin(); iter != graphBuild.end(); iter++){
    delete iter->second;
  }
}

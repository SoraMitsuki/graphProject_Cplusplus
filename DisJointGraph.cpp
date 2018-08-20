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
// this is DisJointGraph.cpp file used for actor connection
// this file contain method/ helper method for writing actor connection

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "DisJointGraph.h"

using namespace std;

DisJointGraph::DisJointGraph(void) {}
/**
 * Load the graph from a tab-delimited file 
 * of actor->movie relationships.
 * in_filename - input filename 
 * return true if file was loaded sucessfully, false otherwise
 */
bool DisJointGraph::loadFromFile(const char* in_filename) {
  //initiazlizr the file stream
  ifstream infile(in_filename);
  //if the file cannot open print error message
  if(!infile.is_open()){
    std::cout << "Cannot open the input file" << std::endl;
    return false;
  }
  //check the have header for first time
  bool have_header = false;
  //keep reading line until end of file
  while(infile){
    string s;
    //get the next line
    if(!getline( infile, s)) break;
    //first line is header and skip after
    if(!have_header) {
      have_header = true;
      continue;
    }
    istringstream ss( s );
    //make a record vector 
    vector<string> record;
    while(ss){
      string next;
      //get the string before hitting a tab
      if(!getline(ss, next, '\t')) break;
        record.push_back(next);
      }
      int num = 3;
      //record should be 3
      if(record.size() != num){
      continue;
    }
    //actor name is first
    string actor_name(record[0]);
    //movir title is second
    string movie_title(record[1]);
    //get the movie year
    int movie_year = stoi(record[2]);
    if(actors.find(record[0]) == actors.end()){
      Vertex* actor = new Vertex(record[0]);
      actors.insert({actor_name, actor});
    }
    //when the movir of the two actors are same
    if(graphBuild.find(movie_year) == graphBuild.end()){
      //create empoty map to hold them
      std::unordered_map<std::string, vector<Vertex*>*>* movies = 
	      new std::unordered_map<std::string, vector<Vertex*>*>;
      vector<Vertex*>* coActors = new vector<Vertex*>;
      //make a new actor node
      Vertex* actor = (actors.find(actor_name))->second;
      //add to coactor
      coActors->push_back(actor);
      movies->insert({movie_title, coActors});
      //insear the movie name and movie year
      graphBuild.insert({movie_year, movies});
      //set the oldest movie year
      if(oldest == infinity || movie_year < oldest){
        oldest = movie_year;
      }
      //set the newest movie year
      if(newest == infinity || movie_year > newest){
        newest = movie_year;
      }
    }
    else{
      //find the the current movie year's movie
      auto movies = (graphBuild.find(movie_year))->second;
      if(movies->find(movie_title) == movies->end()){
	//set the coActors to new vertex
        vector<Vertex*>* coActors = new vector<Vertex*>;
        Vertex* actor = (actors.find(actor_name))->second;
	//push to coActor vector
        coActors->push_back(actor);
	//insert the title and year
        movies->insert({movie_title, coActors});
      }
      else{
	//set coActors and push actor to coActor
        auto coActors = (movies->find(movie_title))->second;
        Vertex* actor = (actors.find(actor_name))->second;
        coActors->push_back(actor);
      }
    } 
  }
  //error message for fail to read
  if(!infile.eof()) {
    cerr << "Failed to read " << in_filename << "!\n";
    return false;
  }
  infile.close();
  return true;
}
  /**
   * getter for get the oldest
   * return the oldest
   */
  int DisJointGraph::getOldest(){
    return oldest;
  }
  /**
   * getter for get the newest
   * return the newest
   */
  int DisJointGraph::getNewest(){
    return newest;
  }

/**
 * getter for the whole graph
 * return the whole graph
 */
  std::unordered_map<int, std::unordered_map<std::string, 
  vector<Vertex*>*>*>& DisJointGraph::getBuild(){
    return graphBuild;
  }
  /**
   * getter for get the actor nodes that we builded
   * return the actors graph
   */
  std::unordered_map<std::string, Vertex*>& DisJointGraph::getGraph(){
    return actors;
  }
  //destructor to clean the graph prevent from memory leak
  DisJointGraph::~DisJointGraph(){
    for(auto iter = actors.begin(); iter != actors.end(); iter++){
      delete iter->second;
    }
    //from graphbuild begin to end and delete all
    for(auto iter = graphBuild.begin(); iter != graphBuild.end(); iter++){
      for(auto iter_2 = (iter->second)->begin(); iter_2 !=
		        (iter->second)->end(); iter_2++){
        delete iter_2->second;
      }
      delete iter->second;
    }
  }

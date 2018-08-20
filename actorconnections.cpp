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
// this is actorconnections.cpp file for find the connection 
// between 2 actors. there are two types of find implemented
// ufind - use disjoint graph
// bfs - regular bfs search

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include "DisJointGraph.h"
/**
 * find the actor that we need
 * return the actor node
 */
Vertex* Find(Vertex* actor){
  Vertex* sentinel = actor;
  vector<Vertex*> reDirect;
  //while the actor's connect is not null
  while(sentinel->connect != NULL){
    //add to redierct
    reDirect.push_back(sentinel);
    //set to the new connect
    sentinel = sentinel->connect;
  }
  //set the redirect to sentinel
  for(int i = 0; i < reDirect.size(); i++){
    reDirect[i]->connect = sentinel;
  }
  return sentinel;
}
/**
 * helper mthod for Union find
 * param: first actor and second actor
 * return true find otherwise false
 */
bool Union(Vertex* actor_1, Vertex* actor_2){
  //find the two actors first
  Vertex* sentinel_1 = Find(actor_1);
  Vertex* sentinel_2 = Find(actor_2);
  //if those two actors are same return false
  if(sentinel_1 == sentinel_2){
    return false;
  }
  //if the first size is greater than second one
  if(sentinel_1->size > sentinel_2->size){
    //set the value fo second connect to first one
    sentinel_2->connect = sentinel_1;
    //increase the first one size
    sentinel_1->size = sentinel_1->size + sentinel_2->size;
  }
  //if the first is smaller than second one repeat the process
  else if(sentinel_1->size < sentinel_2->size){
    sentinel_1->connect = sentinel_2;
    sentinel_2->size = sentinel_2->size + sentinel_1->size;
  }
  //if they are equal
  else{
    sentinel_2->connect = sentinel_1;
    sentinel_1->size = sentinel_1->size + sentinel_2->size;
  }
  return true;
} 
/**
 * union find for actor connections the runtime should be constant
 * PARAM: actor pairs that we read from file and the graph that we builded
 * return the outputs in the output file
 */
vector<std::string> unionFind(vector<std::pair<std::string, 
		std::string>>& pairs, DisJointGraph& graph){
  //get the actor graph
  auto actors = graph.getGraph();
  //get the build graph
  auto build = graph.getBuild();
  vector<std::string> connections(pairs.size());
  //make a found boolean vector
  vector<bool> found(pairs.size(), false);
  //handle magic numbers
  int numFound = 0;
  int year;
  //compare current year to oldest until hit newest
  for(year = graph.getOldest(); year != (graph.getNewest() + 1); year++){
    if(build.find(year) == build.end()){
      //find the year
      continue;
    }
    //get the movies
    auto movies = (build.find(year))->second;
    for(auto iter = movies->begin(); iter != movies->end(); iter++){
      vector<Vertex*>* coActors = iter->second;
      for(int i = 0; i < (coActors->size() - 1); i++){
        Union((*coActors)[i], (*coActors)[i + 1]);
      }
    }
    //loop thorugh the connections size
    for(int i = 0; i < connections.size(); i++){
      if(found[i] == true){
        continue;
      }
      //find the actor pair
      auto actor1 = actors.find(pairs[i].first);
      if(actor1 == actors.end()){
        //if cannot find the first actor
        connections[i] = "Cannot find the first actor";
	//set found to true
        found[i] = true;
        numFound++;
        continue;
      }
      auto actor2 = actors.find(pairs[i].second);
      if(actor2 == actors.end()){
	//if cannot find the first actor
        connections[i] = "Cannot find the second actor";
        found[i] = true;
	//increase the numFund
        numFound++;
        continue;
      }
      //if the first and second actor are same
      if(actor1->second->actor == actor2->second->actor){
        connections[i] = "Same name actor, cannot find himself/herself";
	//set verctor found to true and numFound increase
        found[i] = true;
        numFound++;
        continue;
      }
      //both actors are found
      if(Find(actor1->second) == Find(actor2->second)){
	//set the year
        std::string sYear = std::to_string(year);
	//format of output
        connections[i] = pairs[i].first + "\t" + 
		pairs[i].second + "\t" + sYear;
        found[i] = true;
        numFound++;
      }
      //if numFound equal pair size break
      if(numFound == pairs.size()){
        break;
      }
    }
    if(numFound == pairs.size()){
      break;
    }
  }
  if(numFound == pairs.size()){
    //if they are equal return connections
    return connections;
  }
  for(int i = 0; i < found.size(); i++){
    if(found[i] == false){
      //output the pairs and 9999 for year
      connections[i] = pairs[i].first + "\t" + 
	      pairs[i].second + "\t" + "9999";
    }
  }
  return connections;
} 
/**
 * bfs find for actor connections the runtime should be slower than uFind
 * PARAM: actor pairs that we read from file and the graph that we builded
 * return the outputs in the output file
 */
vector<std::string> bfsFind(vector<std::pair<std::string, 
		std::string>>& pairs, DisJointGraph& graph){
  //get the actors and the graph
  auto actors = graph.getGraph(); 
  auto build = graph.getBuild();
  //make a connection vector
  vector<std::string> connections(pairs.size());
  //make a found vector
  vector<bool> found(pairs.size(), false);
  int numFound = 0;
  int year;
  //loop from oldest year to newest 
  for(year = graph.getOldest(); year != (graph.getNewest() + 1); year++){
    if(build.find(year) == build.end()){
      continue;
    }
    //find the movie
    auto movies = (build.find(year))->second;
    //loop from the beginning to the end of the movie list
    for(auto iter = movies->begin(); iter != movies->end(); iter++){
      //the coActor is the iteratoer second element
      vector<Vertex*>* coActors = iter->second;
      for(int i = 0; i < coActors->size(); i++){
        for(int c = 0; c < coActors->size(); c++){
          if(i != c){
	    //if i and c not equal set the coActors to to current coActos
            if((*coActors)[i]->connection.find((*coActors)[c]) == 
			    (*coActors)[i]->connection.end()){
	      //handled more than 80 characters
              (*coActors)[i]->connection.insert((*coActors)[c]);
            }
          }
        }
      }
    }
    //loop through connection size
    for(int i = 0; i < connections.size(); i++){
      if(found[i] == true){
        continue;
      }
      //find the actor1
      auto actor1 = actors.find(pairs[i].first);
      if(actor1 == actors.end()){
	//when we can not find the first actor
        connections[i] = "Cannot find the first actor";
	//set verctor found to true and numFound increase
        found[i] = true;
        numFound++;
        continue;
      }
      //find the actor2
      auto actor2 = actors.find(pairs[i].second);
      if(actor2 == actors.end()){
	//when we can not find the second actor
        connections[i] = "Cannot find the second actor";
	//set verctor found to true and numFound increase
        found[i] = true;
        numFound++;
        continue;
      }
      //if actor1 and 2 are same person
      if(actor1->second->actor == actor2->second->actor){
        connections[i] = "Same name actor, cannot find himself/herself";
	//set verctor found to true and numFound increase
        found[i] = true;
        numFound++;
        continue;
      }
      //to explore
      Vertex* toExplore;
      queue<Vertex*> explore;
      //set the actor1 done to true
      actor1->second->done = true;
      explore.push(actor1->second);
      vector<Vertex*> resetBool;
      //used to reset done
      resetBool.push_back(actor1->second);
      while(!explore.empty()){
        toExplore = explore.front();
        explore.pop();
	//loop through the conenction 
        for(auto iter = toExplore->connection.begin(); iter != 
			toExplore->connection.end(); iter++){
	  //find the actor2 and put ot output
          if(*iter == actor2->second){
            std::string sYear = std::to_string(year);
            connections[i] = pairs[i].first + "\t" + 
		    pairs[i].second + "\t" + sYear;
	    //set verctor found to true and numFound increase
            found[i] = true;
            numFound++;
            break;
          }
	  //is done is false then set to true
          if((*iter)->done == false){
            (*iter)->done = true;
	    //add to explore vector
            explore.push(*iter);
            resetBool.push_back(*iter);
          }
        }
        if(found[i] == true){
          break;
        }
      }
      //basically the same logic from above ufind
      for(int i = 0; i < resetBool.size(); i++){
        resetBool[i]->done = false;
      }
      //if the number of found equal to pair size
      if(numFound == pairs.size()){
        break;
      }
    }
    //which means the searched through the whole list
    if(numFound == pairs.size()){
      break;
    }
  }
  if(numFound == pairs.size()){
    return connections;
  }
  //if not found put year as 9999
  for(int i = 0; i < found.size(); i++){
    if(found[i] == false){
      connections[i] = pairs[i].first + "\t" + 
	      pairs[i].second + "\t" + "9999";
    }
  }
  //return the connections
  return connections;
}

/**
 * main method that need to be called
 * this method should have 4 argumnets
 * argv[1] = the file that contain movie actor information
 * argc[2] = the file contain paior of actors
 * argv[3] = the outpur file
 * argv[4] = wether uFind or bfs 
 */

int main(int argc, char** argv){
  //handle the magic number
  int args = 5;
  int arg_2 = 2;
  int arg_3 = 3;
  int arg_4 = 4;
  //this is decided weither is weighted or not
  bool uFind = false;
  //used to skip the header
  bool have_header = false;
  vector<std::string> connections;
  //check for the input file
  ifstream testFile(argv[arg_2]);
  if(argc != args){
    if(argc != arg_4){
      //check for invalid arguments
      std::cout << "Invalid number of input" << std::endl;
      return -1;
    }
  }
  //handle the case when there are only 3 argv
  if(argc == arg_4){
    uFind = true;
  }
  //if ufind is entered at 4th argument
  else if(std::string(argv[arg_4]) == "ufind"){
    uFind = true;
  }
  //if bfs is entered 4th argument
  else if(std::string(argv[arg_4]) == "bfs"){
    uFind = false;
  }
  else{ //other wise invalid input
    std::cout << "Invalid input" << std::endl;
    return -1;
  }

  //create a graph
  DisJointGraph graph;
  graph.loadFromFile(argv[1]);
  vector<std::pair<std::string, std::string>> test_pairs;
  //open the output file
  ofstream outFile(argv[arg_3]);
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
      outFile << "Actor1\tActor2\tYear" << endl;
      have_header = true;
      continue;
    }
    
    istringstream ss(s);
    vector<std::string> record;
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
    //create a pair based on the 2 actors
    std::pair<std::string, std::string> names (record[0], record[1]);
    test_pairs.push_back(names);
  }
  //use uFind to find 
  if(uFind){
    connections = unionFind(test_pairs, graph);
  }
  //use bfs to find
  else{
    connections = bfsFind(test_pairs, graph);
  }
  //output the connections to the output file
  for(int i = 0; i < connections.size(); i++){
    outFile << connections[i] << endl;
  }
  return 0;
}

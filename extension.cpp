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
// this is extension.cpp used to print out the
// mutual friends of 2 people entered into the commandline
// if no mutual friend error message will be print

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>

using namespace std;
/** 
 * Load the graph from a tab-delimited file 
 * of two friends reltionships
 * in_filename - input filename
 * return true if file was loaded sucessfully, false otherwise
 */
vector<vector<int>*>* loadFromFile(const char* in_filename) {
  //create a vector of int to hold the information
  vector<vector<int>*>* graph = new vector<vector<int>*>;
  //start to read the file
  ifstream inFile(in_filename);
  if(!inFile.is_open()){
    //if can not open the file print error message
    std::cout << "Cannot open the input file" << std::endl;
    return graph;
  }
  while(inFile){
    string s;
    //if file is empty break
    if(!getline(inFile, s)){
      break;
    }
    istringstream ss(s);
    vector<string> record;
    //while the ss is not empty
    while(ss){
      string next;
      //read the line until hit tab put in next
      if(!getline(ss, next, ' ')){
        break;
      }
      record.push_back(next);
    }
    if(record.size() != 2){
    // we should have exactly 2 colums
      continue;
    }
    //get the friend 1 and friend 2
    string s_id_1(record[0]);
    string s_id_2(record[1]);
    //create 2 ids used to find the friend
    int id_1 = std::stoi(s_id_1);
    int id_2 = std::stoi(s_id_2);
    while(graph->size() < id_1){
      //find the first friend and add to graph
      vector<int>* friends = new vector<int>;
      graph->push_back(friends);
    }
    if(graph->size() == id_1){
      //find the friends 2 and add to graph
      vector<int>* friends = new vector<int>;
      friends->push_back(id_2);
      graph->push_back(friends);
    }
    else{
      (*graph)[graph->size() - 1]->push_back(id_2);
    }
  }
  return graph;
}
/**
 * used to find their mutual friends
 * PARAM: friend_1 as an int
 * PARAM: friend_2 as an int
 * PARAM: graph that we build based on the input file
 * return the vector with mutual friends in it
 */
vector<int> mutualFriends(int id_1, int id_2, vector<vector<int>*>& graph){
  //create a vector to hold mutual friends
  vector<int> mutuals;
  int infinity_1 = -1;
  int infinity_2 = -2;
  // if the user id 1 doesn't exist
  if(id_1 >= graph.size() || graph[id_1]->size() == 0){
    mutuals.push_back(infinity_1);
    return mutuals;
  }
  // if the user id 2 doesn't exist
  if(id_2 >= graph.size() || graph[id_2]->size() == 0){
    mutuals.push_back(infinity_2);
    return mutuals;
  }
  //search through the graph and find the mutual friends
  for(int i = 0; i < graph[id_1]->size(); i++){
    for(int c = 0; c < graph[id_2]->size(); c++){
      if((*graph[id_1])[i] == (*graph[id_2])[c]){
	//if mutual friends found add to the vector
        mutuals.push_back((*graph[id_1])[i]);
        break;
      }
    }
  }
  return mutuals;
}

/**
 * main method used to run the program this main method take 3 arguments
 * argv[1] is the input data file with friends
 * argv[2] is the first friend
 * argv[3] is the second friend
 * output all the mutual friends on terminal
 */
int main(int argc, char** argv){
  //handle magic number
  int num_arg = 4;
  int arg_2 = 2;
  int arg_3 = 3;
  int infinity_1 = -1; // check for exist of user 1
  int infinity_2 = -2; // check for exist of user 2
  //check for the numer of arguments
  if(argc != num_arg){
    std::cout << "Invalid number of input" << std::endl;
    return -1;
  }
  //the second argv is friend_1
  string s_id_1(argv[arg_2]);
  //the third argv is friend_2
  string s_id_2(argv[arg_3]);
  //convert to int
  int id_1 = std::stoi(s_id_1);
  int id_2 = std::stoi(s_id_2);
  //if same person entered twice
  if(id_1 == id_2){
    std::cout << "This is the same person" << std::endl;
    return 0;
  }
  //call load from file to build the graph
  vector<vector<int>*>* graph = loadFromFile(argv[1]);
  if(graph->size() == 0){
    delete graph;
    return -1;
  }
  //create a int vector to hold all the mutual friends
  vector<int> mutuals = mutualFriends(id_1, id_2, *graph);
  if(mutuals.empty()){
    //if it is empty then no mutual friend
    std::cout << "They don't have any mutual friends" << std::endl;
  }
  else if(mutuals[0] == infinity_1){
    // if the user 1 doesn't exist
    std::cout << "User " << id_1 << " doesn't exist." << std::endl;
  }
  else if(mutuals[0] == infinity_2){
    // if the user 2 doesn't exist
    std::cout << "User " << id_2 << " doesn't exist." << std::endl;
  }
  else{
    //else print all the mutual friends on terminal
    std::cout << "Their mutual friends are: ";
    for(int i = 0; i < mutuals.size(); i++){
      std::cout << mutuals[i] << " ";
    }
    std::cout << std::endl;
  }
  //delete graph prevent from memory leak
  for(int i = 0; i < graph->size(); i++){
    delete (*graph)[i];
  }
  delete graph;
  return 0;
}

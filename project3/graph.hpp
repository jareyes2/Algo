#ifndef GRAPH
#define GRAPH

#include <map>
#include <iterator>
#include <string>
#include <vector>
#include <iostream> 
#include <fstream>
#include <sstream>
#include <queue>

int makeGraph();
std::vector<int> Vertex(int, std::vector<int>);
int sum(std::vector<int>v);
bool fill(int max_size, int amount);
bool empty(int current_amount);
bool pour(int current, int add_to_bucket, int other_bucket_max);

#endif /*GRAPH*/

#ifndef SPTRIE_H_
#define SPTRIE_H_

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <numeric>
#include <sstream>
#include <algorithm>
#include <queue>
#include <tuple>
#include <fstream>

using namespace std;

tuple<
	vector<string>,
	vector<int>,
	vector<int>,
	int, 
	int> Min_Trie_Heuristic(vector<string> S_INPUT);

    int build_and_output(tuple<vector<string>,vector<int>,vector<int>,int,int> HEU,
                        string FILENAME = "output.txt"); // "C:/Users/mauri/Documents/GitHub/ADA_FINAL_PROJECT/output.txt"


#endif
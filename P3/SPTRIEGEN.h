#ifndef SPTRIEGEN_H_
#define SPTRIEGEN_H_

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
#include <stack>

using namespace std;


struct targ{
    int i;
    int j;
    int targetr;
    char c;
    vector<targ> sons;
};

struct targ_{ // easier reconstruction
    int i;
    int j;
    int targetr;
    char c;
    vector<targ_*> sons;
};

void printres_GEN_file(vector<targ> in, string FILENAME = "output.txt");

void printres_ANY_file(vector<targ_*> in, string FILENAME = "output.txt");

void printres_ANY_console(vector<targ_*> in);

// READ FROM OUTPUTS, IN CASE TRIE CAME FROM P1, THE PERMUTATION FOR EVERY ROOT TO LEAF IS THE SAME
// (can basically read it into targ_ structure as well)
vector<vector<targ_*>> readres_ANY_file(string FILENAME = "output.txt");

void print_CLEAR(string FILENAME = "output.txt");

vector<char> search_string(string chars, int ind_X, vector<targ_*> data);

tuple<int, vector<targ>> OPT_REC (int i, int j, vector<string> S_);
tuple<int, vector<targ>> OPT_MEMO (int i, int j, vector<string> S_);
tuple<int, vector<targ>> OPT_DP (int i, int j, vector<string> S_);

#endif
#ifndef READ_PROLOG_H_
#define READ_PROLOG_H_

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
    #include <utility>
    
    using namespace std;

    void filler(string &filler, string line_to_read, int n);

    pair<string,string> parseline(string line);
    vector<pair<string,vector<string>>> readFile(string path = "input.prolog");

#endif
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

vector<pair<string,vector<string>>> readFile(string path){
    vector<pair<string,vector<string>>> output;
    ifstream file;
    file.open(path);

    while(!file.eof()){
        int cnt = 0;
        string line;
        getline(cin,line);

        for(int i = 0; i < line.length(); i++){
            string trie;
            string cadena;
            vector<string> rulez;
            if (line[i] != '('){
                trie.push_back(line[i]);
                if (output[cnt].first != trie){
                    cnt++;
                    pair<string,vector<string>> neu = make_pair(trie, rulez);
                    output.push_back(neu);
                }
            } 
            if (line[i] == '('){
                for (int j = i+1; j < line.length() - i; j++){
                    if (line[j] != ')'){
                        cadena.push_back(line[j]);
                        rulez.push_back(cadena);
                        //
                    }
                }
            }
        }




    }



}
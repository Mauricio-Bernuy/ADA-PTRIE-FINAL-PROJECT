#include "read_prolog.h"


void filler( string &filler, string line_to_read, int n){
    if (line_to_read[n] == ' '){
        int j = n+1;
        int len = line_to_read.length();
        for (j; j < len; j++){
            filler.push_back(line_to_read[j]);
        }
    }
}


pair<string,string> parseline(string line){
    stringstream line_s(line);
    string temp;

    getline(line_s, temp, ' ');
    string rule = temp;
    getline(line_s, temp);
    string lin = temp;

    return make_pair(rule,lin);
    
}

vector<pair<string,vector<string>>> readFile(string path){
    vector<pair<string,vector<string>>> output;
    ifstream file;
    file.open(path);
    while(!file.eof() && file.is_open()){
        vector<string> rulez;    
        int cnt = 0;
        string line;
        while(getline(file,line)){
            string trie;
            string cadena;
            int cnt_cad = 0;
            //while(line[cnt_cad] != '('){ // ' '
            while(line[cnt_cad] != ' '){ 
                trie.push_back(line[cnt_cad]);
                cnt_cad++;
            }
            
            filler(cadena, line, cnt_cad);
            
            if (output.empty()){
                pair<string,vector<string>> neu;
                neu.first = trie;
                neu.second.push_back(cadena);
                output.push_back(neu);
            } else if (output[cnt].first == trie){
                output[cnt].second.push_back(cadena);
            }else if (output[cnt].first != trie){
                cnt++;
                pair<string,vector<string>> neu;
                neu.first = trie;
                neu.second.push_back(cadena);
                output.push_back(neu);
            }
        }
    }
    file.close();
    return output;
}
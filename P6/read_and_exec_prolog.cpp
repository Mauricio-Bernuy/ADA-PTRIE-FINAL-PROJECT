#include "../P3/SPTRIEGEN.h"
#include "../P1/SPTRIE.h"
#include "../P6/read_prolog.h"

vector<tuple<string, int, vector<targ_ *>>> trie_reader(string FILE){
    auto read = readres_ANY_file(FILE + ".obj");
    ifstream names;
    names.open(FILE + ".aux");
    vector<tuple<string, int, vector<targ_ *>>> result;
    int r = 0;
    for (auto x : read){
        string info;
        getline(names,info);
        stringstream splitter(info);
        getline(splitter, info, ':');
        string name = info;
        getline(splitter, info, ':');
        int edges = stoi(info);
        #ifdef PRINTING
        cout<<"Trie: " << name <<", edges: " << edges << "\n";
        printres_ANY_console(x);
        #endif
        result.push_back(make_tuple(name,edges,read[r]));
        r++;
    }

    names.close();
    return result;
}

// EXECUTER - QUERY PROCESSING
// structure -> ./execute.x i-trie o-response < queries.prolog
int main(int argc, char** argv){

    vector<string> arguments;
    for (int i = 1; i < argc; i++)
        arguments.push_back(argv[i]);

    bool setinfile,setoutfile;
    string infile,outfile;
    for (auto s : arguments){
        if (s[0] == 'i' && s[1] == '-'){ //input
            s = s.substr(2,s.length());
            infile = s;
            setinfile = true;
        }
        else if (s[0] == 'o' && s[1] == '-'){ //output
            s = s.substr(2,s.length());
            outfile = s;
            setoutfile = true;
        }
        else{
            cerr << "ERROR: wrong argument\n";
            return -1;
        }
    }
    
    if (!setinfile) infile = "trie";
    if (!setoutfile) outfile = "response";
    
    auto loaded_tries = trie_reader(infile);
    ofstream output;
    output.open(outfile + ".out");
    output.close();

    string ln;
    while (getline(cin,ln)){
        auto query = parseline(ln);
        int position = query.second.find('X');
        #ifdef PRINTING
        cout << "rule: " <<  query.first << ", string: "<< query.second <<", Xpos: " << position << "\n";
        #endif

        vector<char> result;
        for (auto set : loaded_tries){
            auto rule = get<0>(set);
            if (rule == query.first){
                result = search_string(query.second,position,get<2>(set));
                break;
            }
        }
        bool comma = false;
        ofstream output;
        output.open(outfile + ".out", ios::app);
        if (result.empty()){
            cout << "X = {}"; 
            output << "X = {}"; 
        }
        else{
            for (auto c : result){
                if (!comma)
                    comma = true;
                else{
                    cout <<", ";
                    output <<", ";
                }
                cout << "X = " << c; 
                output << "X = " << c; 
            }
        }
        
        cout << "\n"; 
        output << "\n"; 
        output.close();
    }

}

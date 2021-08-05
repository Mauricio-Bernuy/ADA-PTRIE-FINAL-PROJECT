#include "../P3/SPTRIEGEN.h"
#include "../P1/SPTRIE.h"
#include "../P6/read_prolog.h"

#include <algorithm>

enum WORKMODE {HEU,REC,MEMO,DP};

//#define PRINTING

// COMPILER

// structure -> ./compile.x --WORKMODE i-input o-trie
int main(int argc, char** argv){
    WORKMODE WM;
    
    vector<string> arguments;
    for (int i = 1; i < argc; i++)
        arguments.push_back(argv[i]);

    bool setflag,setinfile,setoutfile;
    string infile,outfile;
    for (auto s : arguments){
        if (s[0] == '-'){
            if (s == "--heuristic"){
                WM = HEU;
                setflag = true;
            }
            else if (s == "--recursive"){
                WM = REC;
                setflag = true;
            }
            else if (s == "--memoized"){
                WM = MEMO;
                setflag = true;
            }
            else if (s == "--dynprog"){
                WM = DP;
                setflag = true;
            }
            else{
                cerr << "ERROR: invalid flag\n"<<
                "\tflags: --heuristic --recursive --memoized --dynprog";
                return -1;
            }    
        }
        else if (s[0] == 'i' && s[1] == '-'){ //input
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

    if (!setflag){
        cerr << "ERROR: missing flag\n" <<
        "\tflags: --heuristic --recursive --memoized --dynprog";
        return -1;
    }

    if (!setinfile) infile = "input";
    if (!setoutfile) outfile = "trie";


    auto in = readFile(infile + ".prolog");
    ofstream names;
    
    names.open(outfile + ".aux");
    print_CLEAR(outfile +".obj");

    for (auto prolog : in){
        names << prolog.first << ":";
        int edges;
        tuple<int, std::vector<targ>> T;
        switch(WM){
            case HEU:
                edges = build_and_output(Min_Trie_Heuristic(prolog.second),outfile + ".obj");
            break;
            case REC:
                T = OPT_REC(1,prolog.second.size(),prolog.second);
                edges = get<0>(T);
                printres_GEN_file(get<1>(T), outfile + ".obj");
            break;
            case MEMO:
                T = OPT_MEMO(1,prolog.second.size(),prolog.second);
                edges = get<0>(T);
                printres_GEN_file(get<1>(T), outfile + ".obj");
            break;
            case DP:
                T = OPT_DP(1,prolog.second.size(),prolog.second);
                edges = get<0>(T);
                printres_GEN_file(get<1>(T), outfile + ".obj");
            break;
        } 
        names << edges << "\n";
    }
    names.close();

    return 0;

}
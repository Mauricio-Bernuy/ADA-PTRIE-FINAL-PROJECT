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

#define DEBUG_PRINTS 0

ofstream myfile;

vector<string> S;

// vector<vector<bool>*> K_MEM_cols (5, nullptr);
// vector<vector<vector<bool>*>> K_MEM (5, K_MEM_cols);
vector<vector<vector<bool>*>> K_MEM;

vector<bool> K_GEN(int i, int j){
    int m = S[0].length();
    vector<bool> check(m,true);

    string last_S = S[i-1]; 
    for (int x = i; x <= j-1; x++){
        for (int c = 0; c < m; c++){
            if (S[x][c] != last_S[c]){
                check[c] = false;
            }
        }
    }
    return check;
}

vector<bool> K_GEN_MEMO(int i, int j){
    if (K_MEM[i][j] != nullptr){
        return *K_MEM[i][j];
    }
    int m = S[0].length();
    vector<bool> check(m,true);

    string last_S = S[i-1]; 
    for (int x = i; x <= j-1; x++){
        for (int c = 0; c < m; c++){
            if (S[x][c] != last_S[c]){
                check[c] = false;
            }
        }
    }
    vector<bool> * copy = new vector<bool>;
    *copy = check;  
    K_MEM[i][j] = copy;
    return check;
}

vector<int> K(int i, int j){
    auto kgen = K_GEN(i,j);
    int m = S[0].length();

    vector<int> ret;
    for (int a = 0; a < m; a++){
        if (kgen[a] == true){
            ret.push_back(a);
            if (DEBUG_PRINTS) cout << ret.back() << ", ";
        }
    }
    if (DEBUG_PRINTS) cout << "\n";
    return ret;
}

vector<int> K_MEMO(int i, int j){
    auto kgen = K_GEN_MEMO(i,j);
    int m = S[0].length();

    vector<int> ret;
    for (int a = 0; a < m; a++){
        if (kgen[a] == true){
            ret.push_back(a);
            if (DEBUG_PRINTS) cout << ret.back() << ", ";
        }
    }
    if (DEBUG_PRINTS) cout << "\n";
    return ret;
}

vector<int> R(int i, int j){
    auto kgen = K_GEN(i,j);
    int m = S[0].length();

    vector<int> ret;
    for (int a = 0; a < m; a++){
        if (kgen[a] == false){
            ret.push_back(a);
            if (DEBUG_PRINTS) cout << ret.back() << ", ";
        }
    }
    if (DEBUG_PRINTS) cout << "\n";
    return ret;
}

vector<int> R_MEMO(int i, int j){
    auto kgen = K_GEN_MEMO(i,j);
    int m = S[0].length();

    vector<int> ret;
    for (int a = 0; a < m; a++){
        if (kgen[a] == false){
            ret.push_back(a);
            if (DEBUG_PRINTS) cout << ret.back() << ", ";
        }
    }
    if (DEBUG_PRINTS) cout << "\n";
    return ret;
}

vector<string> S_line (int i, int j){
    auto kgen = K_GEN_MEMO(i,j);
    int m = S[0].length();
    int plus = 1;
    if (i == j) plus = 0;
    vector<string> ret(j - i + plus);

    for (int a = 0; a < m; a++){
        if (kgen[a] == false){
            for (int r = i; r <= j; r++){
                ret[r-i].push_back(S[r-1][a]);
            }
        }
    }
    
    if (DEBUG_PRINTS){
        for (int r = 0; r < ret.size(); r++){
            cout << ret[r] << ", ";
        }
        cout << "\n";
    }
    return ret;
}

// vector< vector<vector<int>>* > C_MEM_col (5, nullptr);
// vector<vector< vector<vector<int>>* >> C_MEM_col2 (5, C_MEM_col);
// vector<vector<vector< vector<vector<int>>* >>> C_MEM (5, C_MEM_col2);
vector<vector<vector< vector<vector<int>>* >>> C_MEM;

vector<vector<int>> C(int i,int j,int r){
    vector<vector<int>> res;

    if (DEBUG_PRINTS){
        for (int c = i-1; c <= j-1; c++){
            auto x = S[c][r];
            cout << x << ", ";
        }
    }

    int beginpos,endpos;
    beginpos = i;
    endpos = i;    
    
    while (endpos <= j && beginpos <= j){
        if (S[beginpos-1][r] == S[endpos-1][r]){
            endpos++;
            if (endpos > j) 
                res.push_back({beginpos,endpos-1});
        }
        else{
            res.push_back({beginpos,endpos-1});
            beginpos = endpos;                  
        }
    }

    if (DEBUG_PRINTS){
        for (int d = 0; d < res.size(); d++){
            cout << "("<< res[d][0] << ", " << res[d][1] << ") ";
        }
        cout << "\n";
    }

    return res;
}

vector<vector<int>> C_MEMO(int i,int j,int r){
    if (C_MEM[i][j][r] != nullptr){
        return *C_MEM[i][j][r];
    }

    vector<vector<int>> res;

    if (DEBUG_PRINTS){
        for (int c = i-1; c <= j-1; c++){
            auto x = S[c][r];
            cout << x << ", ";
        }
    }
    
    int beginpos,endpos;
    beginpos = i;
    endpos = i;    
    
    while (endpos <= j && beginpos <= j){
        if (S[beginpos-1][r] == S[endpos-1][r]){
            endpos++;
            if (endpos > j) 
                res.push_back({beginpos,endpos-1});
        }
        else{
            res.push_back({beginpos,endpos-1});
            beginpos = endpos;                  
        }
    }

    if (DEBUG_PRINTS){
        for (int d = 0; d < res.size(); d++){
            cout << "("<< res[d][0] << ", " << res[d][1] << ") ";
        }
        cout << "\n";
    }

    vector<vector<int>> * copy = new vector<vector<int>>;
    *copy = res;  
    C_MEM[i][j][r] = copy;
    return res;
}

void get_all(int i, int j, int PRINTMODE = 0){
    int m = S[0].length();

    if (PRINTMODE == 0 || PRINTMODE == 1){
        printf("K:\n");

        for (int j_ = i; j_ <= j; j_++){
            for (int i_ = i; i_ <= j_; i_++){
                printf("\tK(%d,%d): {",i_,j_);
                auto k = K(i_,j_);
                for (auto x : k)
                    printf("%d,",x);
                printf("}\n");
            }
        }
    }

    if (PRINTMODE == 0 || PRINTMODE == 2){
        printf("R:\n");

        for (int j_ = i; j_ <= j; j_++){
            for (int i_ = i; i_ <= j_; i_++){
                printf("\tR(%d,%d): {",i_,j_);
                auto r = R(i_,j_);
                for (auto x : r)
                    printf("%d,",x);
                printf("}\n");
            }
        }
    }

    if (PRINTMODE == 0 || PRINTMODE == 3){
        printf("C:\n");

        for (int j_ = i; j_ <= j; j_++){
            for (int i_ = i; i_ <= j_; i_++){
                auto r = R(i_,j_);
                for (auto r_ : r){
                    printf("\tC(%d,%d,%d): {",i_,j_,r_);

                    auto c = C(i_,j_,r_);
                    for (auto x : c)
                        printf("(%d,%d), ",x[0],x[1]);
                    printf("}\n");
                }
            }
        }
    }
}

struct targ{
    int i;
    int j;
    int targetr;
    vector<targ> sons;
    bool addremaining = false;
};

tuple<int, vector<targ>> OPT_line (int i, int j){ 
    if (i == j){
        vector<targ> empty;
        tuple<int, vector<targ>> xd = make_tuple(0, empty);
        return xd;
    }

    int min = INT_MAX;
    vector<targ> targs;
    int targetr = 0;

    auto R_ = R(i,j);
    for (auto r : R_){
        auto C_ = C(i,j,r);

        int sum = 0;
        vector<targ> accum;

        for (auto ijprime : C_){
            auto iprime = ijprime[0];
            auto jprime = ijprime[1];
            
            auto x = OPT_line(iprime,jprime);

            auto cur = get<0>(x) + K(iprime,jprime).size() - K(i,j).size();
            sum += cur;
            
            // MERGE SITUATION - in case there's more than one K for the prime indexes

            if (K(iprime,jprime).size() > 1){
                if (DEBUG_PRINTS) printf("(%d, %d) merge situation\n", iprime,jprime);
                auto kay = K(iprime,jprime);
                auto kayfull = K(i,j);
                vector<targ> trg_ = get<1>(x);
                vector<targ> temp;
                vector<targ> * next = &temp;
                
                for (int k_ : kay){
                    if (k_ != r && !(find(kayfull.begin(),kayfull.end(), k_) != kayfull.end())){
                        vector<targ> empty;
                        next->push_back(targ{iprime,jprime, k_,empty});
                        next = &(*next)[0].sons; 
                    }
                }
                *next = trg_;
                x = make_tuple(get<0>(x), temp);
            }

            // REMAINDER SITUATION - if the nodes left to insert in that tree can be placed in any order that satisfies the S it roots to.

            if (get<0>(x) == 0){
                int edges_left = K(iprime,jprime).size() - K(i,j).size() - 1;
                if (DEBUG_PRINTS) cout<< iprime << "," << jprime <<" - edges left: " << edges_left <<"\n";
                
                if (edges_left > 0){                                                // add these to the trie arbitrarly
                    vector<targ> empty;
                    vector<targ> a = {targ{iprime, jprime, -1, empty, true}};       // addremaining = true, once the vertex produces only one child, 
                                                                                            //                the order of insertion does not really matter at all. 
                                                                                            // targetr = edges_left, might be useful!
                    x = make_tuple(get<0>(x), a);
                }
            }

            accum.push_back(targ{iprime,jprime,r,get<1>(x)});
        }

        // will end up with min edge value for the subproblem

        if (sum < min){
            min = sum;
            targs = accum;
            targetr = r;
        }
    }

    tuple<int, vector<targ>> retrn = make_tuple(min,targs);
    if (DEBUG_PRINTS) printf("OPT(%d,%d) -> min: %d, vector<targ>.size(): %d \n",i,j,min,targs.size());
    return retrn;
}

// vector<tuple<int, vector<targ>>*> OPT_LINE_M_col (5, nullptr);
// vector<vector<tuple<int, vector<targ>>*>> OPT_LINE_M(5, OPT_LINE_M_col);
vector<vector<tuple<int, vector<targ>>*>> OPT_LINE_M;

tuple<int, vector<targ>> OPT_line_MEMO (int i, int j){ 
    if ((OPT_LINE_M[i][j]) != nullptr){
        printf("OPT_line_MEMO HIT\n");
        return *OPT_LINE_M[i][j];
    }

    if (i == j){
        vector<targ> empty;
        tuple<int, vector<targ>> xd = make_tuple(0, empty);
        return xd;
    }
    
    int min = INT_MAX;
    vector<targ> targs;
    int targetr = 0;

    auto R_ = R_MEMO(i,j);
    for (auto r : R_){
        auto C_ = C_MEMO(i,j,r);

        int sum = 0;
        vector<targ> accum;

        for (auto ijprime : C_){
            auto iprime = ijprime[0];
            auto jprime = ijprime[1];
            tuple<int, vector<targ>> x;
            tuple<int, vector<targ>> * ptr;

            /*if ((OPT_LINE_M[iprime][jprime]) == nullptr){
                tuple<int, vector<targ>> * copy = new tuple<int, vector<targ>>;
                tuple<int, vector<targ>> a = OPT_line_MEMO(iprime,jprime);
                *copy = a;
                OPT_LINE_M[iprime][jprime] = copy;
            }*/
            
            // x = *OPT_LINE_M[iprime][jprime];
            x = OPT_line_MEMO(iprime,jprime);

            auto cur = get<0>(x) + K_MEMO(iprime,jprime).size() - K_MEMO(i,j).size();
            sum += cur;
            
            // MERGE SITUATION - in case there's more than one K for the prime indexes

            if (K_MEMO(iprime,jprime).size() > 1){
                if (DEBUG_PRINTS) printf("(%d, %d) merge situation\n", iprime,jprime);
                auto kay = K_MEMO(iprime,jprime);
                auto kayfull = K_MEMO(i,j);
                vector<targ> trg_ = get<1>(x);
                vector<targ> temp;
                vector<targ> * next = &temp;
                
                for (int k_ : kay){
                    if (k_ != r && !(find(kayfull.begin(),kayfull.end(), k_) != kayfull.end())){
                        vector<targ> empty;
                        next->push_back(targ{iprime,jprime, k_,empty});
                        next = &(*next)[0].sons; 
                    }
                }
                *next = trg_;
                x = make_tuple(get<0>(x), temp);
            }

            // REMAINDER SITUATION - if the nodes left to insert in that tree can be placed in any order that satisfies the S it roots to.
            // maybe can apply merge situation stuff to complete the trie

            if (get<0>(x) == 0){
                get_all(1, S.size(), 1);
                int edges_left = K_MEMO(iprime,jprime).size() - K_MEMO(i,j).size() - 1;
                if (DEBUG_PRINTS) cout << iprime << "," << jprime <<" - edges left: " << edges_left <<"\n";
                
                if (edges_left > 0){                                                // add these to the trie arbitrarly
                    vector<targ> empty;
                    vector<targ> a = {targ{iprime, jprime, -1, empty, true}};       // addremaining = true, once the vertex produces only one child, 
                                                                                            //                the order of insertion does not really matter at all. 
                                                                                            // targetr = edges_left, might be useful!
                    x = make_tuple(get<0>(x), a);
                }
            }

            accum.push_back(targ{iprime,jprime,r,get<1>(x)});
        }

        // will end up with min edge value for the subproblem

        if (sum < min){
            min = sum;
            targs = accum;
            targetr = r;
        }
    }

    tuple<int, vector<targ>> retrn = make_tuple(min,targs);

    if (DEBUG_PRINTS) printf("OPT(%d,%d) -> min: %d, vector<targ>.size(): %d \n",i,j,min,targs.size());
    
    tuple<int, vector<targ>> * copy =  new tuple<int, vector<targ>>;
    *copy = retrn;  
    OPT_LINE_M[i][j] = copy;

    return retrn;
}

tuple<int, vector<targ>> OPT (int i, int j){

    auto line = OPT_line(i,j);
    auto a = K_GEN(i,j);
    int cnt = 0;
    int fcnt = 0;
    vector<targ> res;
    vector<targ> temp;
    vector<targ> * next = &temp;

    // OPT_line TO OPT - we have to complete the trie with the K(i,j) common rows connecting to the root (if there are any).

    for (bool b : a){
        if (b){
            next->push_back(targ{i,j,cnt}); 
            next = &(*next)[0].sons; 
            fcnt++;
        }
        cnt++;
    }

    *next = get<1>(line);
    return make_tuple(get<0>(line) + fcnt,temp);
}

tuple<int, vector<targ>> OPT_MEMO (int i, int j){
    int m = S[0].length();
    vector<tuple<int, vector<targ>>*> OPT_LINE_M_col_ (j + 1, nullptr);
    vector<vector<tuple<int, vector<targ>>*>> OPT_LINE_M_ (j + 1, OPT_LINE_M_col_);    
    OPT_LINE_M = OPT_LINE_M_;

    vector< vector<vector<int>>* > C_MEM_col_ (m+1, nullptr);
    vector<vector< vector<vector<int>>* >> C_MEM_col2_ (j + 1, C_MEM_col_);
    vector<vector<vector< vector<vector<int>>* >>> C_MEM_ (j + 1, C_MEM_col2_);
    C_MEM = C_MEM_;

    vector<vector<bool>*> K_MEM_cols_ (j + 1, nullptr);
    vector<vector<vector<bool>*>> K_MEM_ (j + 1, K_MEM_cols_);
    K_MEM = K_MEM_;

    for (int f = 0; f <= j; f++) {
        tuple<int, vector<targ>> * copy = new tuple<int, vector<targ>>;
        tuple<int, vector<targ>> val = make_tuple(0, vector<targ>{});
        *copy = val;
        OPT_LINE_M[f][f] = copy;
    }

    auto line = OPT_line_MEMO(i,j);
    auto a = K_GEN_MEMO(i,j);
    int cnt = 0;
    int fcnt = 0;
    vector<targ> temp;
    vector<targ> * next = &temp;

    // OPT_line TO OPT - we have to complete the trie with the K(i,j) common rows connecting to the root (if there are any).

    for (bool b : a){
        if (b){
            next->push_back(targ{i,j,cnt}); 
            next = &(*next)[0].sons; 
            fcnt++;
        }
        cnt++;
    }

    *next = get<1>(line);

    // PRINT EACH MEMO PARA VER


    return make_tuple(get<0>(line) + fcnt,temp);
}

void printres(vector<targ> in){ // pre-fix printing
    if (in.empty()){
        printf("(REACHED LEAF)\n");
        myfile << "(REACHED LEAF)\n";
        return;
    }
    for (auto t : in){
        printf("# starting (%d,%d,%d)\n", t.i, t.j, t.targetr); 
        myfile << "# starting (" << t.i <<"," << t.j << "," << t.targetr << ")\n";
        
        if (t.addremaining){
            printf("(%d,%d -> %d remaining order arbitrary, but should provide a valid string) \n", t.i, t.j, t.targetr); 
            myfile <<"(" << t.i <<"," << t.j << " -> " << t.targetr << " remaining order arbitrary, but should provide a valid string) \n";
        }
        else{
            printf("(%d,%d,%d -> %c) \n", t.i, t.j, t.targetr, S[t.i-1][t.targetr]);
            myfile <<"(" << t.i <<"," << t.j <<"," << t.targetr << " -> " << S[t.i-1][t.targetr] << ") \n";
        }
        printres(t.sons);
        printf("# ending (%d,%d,%d)\n", t.i, t.j, t.targetr); 
        myfile << "# ending (" << t.i <<"," << t.j << "," << t.targetr << ")\n";
    }
    return;
}

int main(){
    myfile.open ("output.txt");
// tests
    //S.clear();
    //S = {   "cbb","dcb", "dcc"   };
/*
    K(1,1);
    K(1,2);
    K(1,3);
    K(2,2);
    K(2,3);
    K(3,3);

    R(1,1);
    R(1,2);
    R(1,3);
    R(2,2);
    R(2,3);
    R(3,3);

    S_line(1,1);
    S_line(1,2);
    S_line(1,3);
    S_line(2,2);
    S_line(2,3);
    S_line(3,3);


    C(1,3,0);
    C(1,3,1);
    C(1,3,2);  
    C(1,2,0);
    C(1,2,1);
    C(2,3,2);
  
*/
   
    
    //S = {"aaa", "bab", "cab"};

    S = {   "aaa",
            "bab",
            "cab",
            "cbb",
            "dcb",
            "dcc"   };

    //S = {"aaasa", "baare", "bacxs", "cbbae"};

    //S = {"aaa", "bab", "cab"};

    //get_all(1,S.size());

    auto a = OPT(1,S.size());
    printf("\nObtained Min-Trie-Gen with %d edges.\n\n", get<0>(a));
    myfile << "Obtained Min-Trie-Gen with " << get<0>(a) << " edges.\n\n";
    printres(get<1>(a));

    auto b = OPT_MEMO(1,S.size());
    printf("\nObtained Min-Trie-Gen-MEMO with %d edges.\n\n", get<0>(b));
    myfile << "Obtained Min-Trie-Gen-MEMO with " << get<0>(b) << " edges.\n\n";
    printres(get<1>(b));
    
    myfile.close();
    
    //system("python3 tree.py");
}
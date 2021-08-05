
#include "SPTRIEGEN.h"

using namespace std;

#define DEBUG_PRINTS 0

vector<string> S; // global string object

// MEMOIZATION MATRICES

vector<vector<vector<bool>*>> K_MEM;
vector<vector<tuple<int, vector<targ>>*>> OPT_LINE_M;

// AUXILIARY FUNCTIONS

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
        #ifdef PRINTING
        printf("->K_MEM[%d][%d] HIT\n", i,j);
        #endif
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
    #ifdef PRINTING
    printf("<-K_MEM[%d][%d] STORE\n", i,j);
    #endif
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

// OPT CONSTRUCTION

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
                #ifdef PRINTING
                printf("(%d, %d) merge situation\n", iprime,jprime);
                #endif
                auto kay = K(iprime,jprime);
                auto kayfull = K(i,j);
                vector<targ> trg_ = get<1>(x);
                vector<targ> temp;
                vector<targ> * next = &temp;
                
                for (int k_ : kay){
                    if (k_ != r && !(find(kayfull.begin(),kayfull.end(), k_) != kayfull.end())){
                        vector<targ> empty;
                        next->push_back(targ{iprime,jprime, k_, S[iprime-1][k_], empty});
                        next = &(*next)[0].sons; 
                    }
                }
                *next = trg_;
                x = make_tuple(get<0>(x), temp);
            }

            accum.push_back(targ{iprime,jprime,r,S[iprime-1][r],get<1>(x)});
        }

        // will end up with min edge value for the subproblem

        if (sum < min){
            min = sum;
            targs = accum;
            targetr = r;
        }
    }

    tuple<int, vector<targ>> retrn = make_tuple(min,targs);
    #ifdef PRINTING
    printf("OPT_line(%d,%d) -> min: %d, vector<targ>.size(): %d \n",i,j,min,targs.size());
    #endif
    return retrn;
}

tuple<int, vector<targ>> OPT_line_MEMO (int i, int j){ 
    if ((OPT_LINE_M[i][j]) != nullptr){
        #ifdef PRINTING
        printf("->OPT_line_M[%d][%d] HIT\n", i,j);
        #endif
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
        auto C_ = C(i,j,r);

        int sum = 0;
        vector<targ> accum;

        for (auto ijprime : C_){
            auto iprime = ijprime[0];
            auto jprime = ijprime[1];
            tuple<int, vector<targ>> x;
            tuple<int, vector<targ>> * ptr;

           
            x = OPT_line_MEMO(iprime,jprime);

            auto cur = get<0>(x) + K_MEMO(iprime,jprime).size() - K_MEMO(i,j).size();
            sum += cur;
            
            // MERGE SITUATION - in case there's more than one K for the prime indexes

            if (K_MEMO(iprime,jprime).size() > 1){
                #ifdef PRINTING
                printf("(%d, %d) merge situation\n", iprime,jprime);
                #endif
                auto kay = K_MEMO(iprime,jprime);
                auto kayfull = K_MEMO(i,j);
                vector<targ> trg_ = get<1>(x);
                vector<targ> temp;
                vector<targ> * next = &temp;
                
                for (int k_ : kay){
                    if (k_ != r && !(find(kayfull.begin(),kayfull.end(), k_) != kayfull.end())){
                        vector<targ> empty;
                        next->push_back(targ{iprime,jprime, k_, S[iprime-1][k_], empty});
                        next = &(*next)[0].sons; 
                    }
                }
                *next = trg_;
                x = make_tuple(get<0>(x), temp);
            }

            accum.push_back(targ{iprime,jprime,r,S[iprime-1][r],get<1>(x)});
        }

        // will end up with min edge value for the subproblem

        if (sum < min){
            min = sum;
            targs = accum;
            targetr = r;
        }
    }

    tuple<int, vector<targ>> retrn = make_tuple(min,targs);
    
    #ifdef PRINTING
    printf("OPT_line_MEMO(%d,%d) -> min: %d, vector<targ>.size(): %d \n",i,j,min,targs.size());
    #endif

    tuple<int, vector<targ>> * copy =  new tuple<int, vector<targ>>;
    *copy = retrn;  
    OPT_LINE_M[i][j] = copy;
    #ifdef PRINTING
    printf("<-OPT_line_M[%d][%d] STORE\n", i,j);
    #endif
    return retrn;
}

tuple<int, vector<targ>> OPT_REC (int i, int j, vector<string> S_){
    S = S_;
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
            next->push_back(targ{i,j,cnt,S[i-1][cnt]}); 
            next = &(*next)[0].sons; 
            fcnt++;
        }
        cnt++;
    }
    *next = get<1>(line);
    S.clear();

    return make_tuple(get<0>(line) + fcnt,temp);
}

tuple<int, vector<targ>> OPT_MEMO (int i, int j, vector<string> S_){
    S = S_;
    int m = S[0].length();
    vector<tuple<int, vector<targ>>*> OPT_LINE_M_col_ (j + 1, nullptr);
    vector<vector<tuple<int, vector<targ>>*>> OPT_LINE_M_ (j + 1, OPT_LINE_M_col_);    
    OPT_LINE_M = OPT_LINE_M_;

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

    // OPT_line TO OPT - we have to complete the trie with the K(i,j) 
    // common rows connecting to the root (if there are any).

    for (bool b : a){
        if (b){
            next->push_back(targ{i,j,cnt,S[i-1][cnt]}); 
            next = &(*next)[0].sons; 
            fcnt++;
        }
        cnt++;
    }
    *next = get<1>(line);
    S.clear();
    K_MEM.clear();
    OPT_LINE_M.clear();

    return make_tuple(get<0>(line) + fcnt,temp);
}

void get_all(int i = 1, int j = S.size(), int PRINTMODE = 0){
    int m = S[0].length();

    if (PRINTMODE == 0 || PRINTMODE == 1){
        #ifdef PRINTING
        printf("K_GEN_MEMO:\n");
        #endif
        for (int j_ = i; j_ <= j; j_++){
            for (int i_ = i; i_ <= j_; i_++){
                #ifdef PRINTING
                printf("\tK_GEN_MEMO(%d,%d): {\n",i_,j_);
                #endif
                auto k = K_GEN_MEMO(i_,j_);
                #ifdef PRINTING
                for (auto x : k)
                    printf("%d,",x);
                printf("}\n");
                #endif
            }
        }
    }

    if (PRINTMODE == 0 || PRINTMODE == 2){
        #ifdef PRINTING
        printf("K:\n");
        #endif
        for (int j_ = i; j_ <= j; j_++){
            for (int i_ = i; i_ <= j_; i_++){
                #ifdef PRINTING
                printf("\tK(%d,%d): {\n",i_,j_);
                #endif
                auto k = K_MEMO(i_,j_);
                #ifdef PRINTING
                for (auto x : k)
                    printf("%d,",x);
                printf("}\n");
                #endif
            }
        }
    }

    if (PRINTMODE == 0 || PRINTMODE == 3){
        #ifdef PRINTING
        printf("R:\n");
        #endif
        for (int j_ = i; j_ <= j; j_++){
            for (int i_ = i; i_ <= j_; i_++){
                #ifdef PRINTING
                printf("\tR(%d,%d): {",i_,j_);
                #endif
                auto r = R(i_,j_);
                #ifdef PRINTING
                for (auto x : r)
                    printf("%d,",x);
                printf("}\n");
                #endif
            }
        }
    }

    if (PRINTMODE == 0 || PRINTMODE == 4){
        #ifdef PRINTING
        printf("OPT_line_MEMO:\n");
        #endif
        for (int j_ = i; j_ <= j; j_++){
            for (int i_ = i; i_ <= j_; i_++){
                #ifdef PRINTING
                printf("\tOPT_line_MEMO(%d,%d): {\n",i_,j_);
                #endif
                auto OPT_L = OPT_line_MEMO(i_,j_);
                #ifdef PRINTING
                printf("\tcount: %d,",get<0>(OPT_L));
                printf("\tchild count: %d", get<1>(OPT_L).size());
                printf("\t}\n");
                #endif
            }
        }
    }

    if (PRINTMODE == 0 || PRINTMODE == 5){
        #ifdef PRINTING
        printf("C:\n");
        #endif

        for (int j_ = i; j_ <= j; j_++){
            for (int i_ = i; i_ <= j_; i_++){
                auto r = R(i_,j_);
                for (auto r_ : r){
                    #ifdef PRINTING
                    printf("\tC(%d,%d,%d): {",i_,j_,r_);
                    #endif

                    auto c = C(i_,j_,r_);
                    #ifdef PRINTING
                    for (auto x : c)
                        printf("(%d,%d), ",x[0],x[1]);
                    printf("}\n");
                    #endif
                }
            }
        }
    }
}

tuple<int, vector<targ>> OPT_DP (int i, int j, vector<string> S_){
    S = S_;
    int m = S[0].length();

    vector<tuple<int, vector<targ>>*> OPT_LINE_M_col_ (j + 1, nullptr);
    vector<vector<tuple<int, vector<targ>>*>> OPT_LINE_M_ (j + 1, OPT_LINE_M_col_);    
    OPT_LINE_M = OPT_LINE_M_;

    vector<vector<bool>*> K_MEM_cols_ (j + 1, nullptr);
    vector<vector<vector<bool>*>> K_MEM_ (j + 1, K_MEM_cols_);
    K_MEM = K_MEM_;

    for (int f = 0; f <= j; f++) {
        tuple<int, vector<targ>> * copy = new tuple<int, vector<targ>>;
        tuple<int, vector<targ>> val = make_tuple(0, vector<targ>{});
        *copy = val;
        OPT_LINE_M[f][f] = copy;
    }

    // steps to calculate BOTTOM-UP: (make a separate function later)
    get_all(1,S.size(), 1); // THIS HAS TO BE K_GEN
    get_all(1,S.size(), 4); // CALCULATES OPT's
    

    #ifdef PRINTING
    printf("Finished Bottom-Up calculations\n");
    #endif
    
    auto line = OPT_line_MEMO(i,j);
    auto a = K_GEN_MEMO(i,j);
    int cnt = 0;
    int fcnt = 0;
    vector<targ> temp;
    vector<targ> * next = &temp;

    // OPT_line TO OPT - we have to complete the trie with the K(i,j) common rows connecting to the root (if there are any).

    for (bool b : a){
        if (b){
            next->push_back(targ{i,j,cnt,S[i-1][cnt]}); 
            next = &(*next)[0].sons; 
            fcnt++;
        }
        cnt++;
    }
    *next = get<1>(line);
    S.clear();
    K_MEM.clear();
    OPT_LINE_M.clear();

    return make_tuple(get<0>(line) + fcnt,temp);
}

// OUTPUT FUNCTIONS

void printres_info(vector<targ> in){ // pre-fix printing, more verbose
    if (in.empty()){
        printf("(REACHED LEAF)\n");
        return;
    }
    for (auto t : in){

        printf("# starting (%d,%d,%d)\n", t.i, t.j, t.targetr); 
        printf("(%d,%d,%d -> %c) \n", t.i, t.j, t.targetr, t.c);
        printres_info(t.sons);
        printf("# ending (%d,%d,%d)\n", t.i, t.j, t.targetr); 
    }
    return;
}

// output SPTRIEGEN to ENCODING

void printres_GEN(vector<targ> in, ofstream &out, bool file = 1){ // pre-fix printing
    if (in.empty()){
        return;
    }
    for (auto t : in){
        if (!file) printf("S(%d,%d,%d,%c)\n", t.i, t.j, t.targetr, t.c); 
        if (file) out << "S(" << t.i <<"," << t.j << "," << t.targetr << "," << t.c <<")\n";
        
        printres_GEN(t.sons, out, file);

        if (!file) printf("E(%d,%d,%d,%c)\n", t.i, t.j, t.targetr, t.c); 
        if (file) out << "E(" << t.i <<"," << t.j << "," << t.targetr << "," << t.c <<")\n";
    }
    return;
}

void printres_GEN_file(vector<targ> in, string FILENAME){
    ofstream out;
    out.open(FILENAME, ios::app);
    printres_GEN(in,out);
    out << "-\n";
    out.close();
}

// OUTPUT ENCODED TRIE

void printres_ANY_console(vector<targ_*> in){ // pre-fix printing ptr version
    if (in.empty()){
        return;
    }
    for (auto t : in){
        printf("S(%d,%d,%d,%c)\n", t->i, t->j, t->targetr, t->c);
        
        printres_ANY_console(t->sons);

        printf("E(%d,%d,%d,%c)\n", t->i, t->j, t->targetr, t->c); 
    }
    return;
}

void printres_ANY(vector<targ_*> in, ofstream &out, bool file = 1){ // pre-fix printing ptr version
    if (in.empty()){
        return;
    }
    for (auto t : in){
        if (!file) printf("S(%d,%d,%d,%c)\n", t->i, t->j, t->targetr, t->c); 
        if (file) out << "S(" << t->i <<"," << t->j << "," << t->targetr << "," << t->c <<")\n";
        
        printres_ANY(t->sons, out, file);

        if (!file) printf("E(%d,%d,%d,%c)\n", t->i, t->j, t->targetr, t->c); 
        if (file) out << "E(" << t->i <<"," << t->j << "," << t->targetr << "," << t->c <<")\n";
    }
    return;
}

void printres_ANY_file(vector<targ_*> in, string FILENAME){
    ofstream out;
    out.open(FILENAME, ios::app);
    printres_ANY(in,out);
    out << "-\n";
    out.close();
}

// READ ENCODED TRIE

vector<vector<targ_*>> readres_ANY_file(string FILENAME){
    vector<vector<targ_*>> tries;
    ifstream input;
    input.open(FILENAME);

    vector<targ_*> result;
    stack<targ_*> OPSTACK;

    newobj:
    targ_* ROOT = new targ_;
    *ROOT = (targ_{-1,-1, -1, 'R', result});

    OPSTACK.push(ROOT);
    targ_* iter;

    while (!OPSTACK.empty()){
        iter = OPSTACK.top();
        string line;
        getline(input,line);

        if (line.length() > 0){
            if (line[0] == 'S'){
                string temp;
                line.erase(0,2);
                line.pop_back();

                stringstream line_s(line);
                
                getline(line_s, temp, ',');
                int i = stoi(temp);
                getline(line_s, temp, ',');
                int j = stoi(temp);
                getline(line_s, temp, ',');
                int r = stoi(temp);
                getline(line_s, temp, ',');
                char c = temp[0];

                targ_ * a = new targ_{i, j, r, c};

                iter->sons.push_back(a);
                OPSTACK.push(a);
            }

            else if (line[0] == 'E'){
                OPSTACK.pop();
            }
            else if (line[0] == '-'){
                tries.push_back(ROOT->sons);
                goto newobj;
            }
        }
        else break;
    }
    input.close();
    return tries;
}

// CLEAR ENCODE FILE

void print_CLEAR(string FILENAME){
    ofstream out;
    out.open(FILENAME);
    out.close();
}

// SEARCH IN ENCODED TRIE

bool valid_path(string chars, vector<targ_*> data){
    vector <targ_*> * iter = &data;
    vector <targ_*> * next;
    while (true){
        bool found = false;
        if (iter->empty()){
            break;
        }
        for (auto t : *iter){
            auto r = t->targetr;
            if (t->c == chars[r]){
                next = &t->sons;
                found = true;
                break;
            }
        }
        if (!found){
            return false;
        }        
        iter = next;

    }
    return true;
}

vector<char> search_string(string chars, int ind_X, vector<targ_*> data){
    vector<bool> found(chars.length(), false);
    vector<char> empty;
    if (data.empty()  || chars.empty())
        return empty;

    vector<char> result;
    
    vector <targ_*> * iter = &data;
    vector <targ_*> * next;
    bool finished = false;
    while (!finished){
        bool found = false;
        for (auto t : *iter){
            auto r = t->targetr;
            if (r == ind_X){
                found = true;
                for (auto t_ : *iter){
                    auto success = valid_path(chars,t_->sons);
                    if (success){
                        result.push_back(t_->c);
                    }
                }
                finished = true;
                break;
            }
            else if (t->c == chars[r]){   
                next = &t->sons;
                found = true;
                break;
            }
        }
        if (!found){
            finished = true;
        }

        iter = next;
    }
        
    return result;
}

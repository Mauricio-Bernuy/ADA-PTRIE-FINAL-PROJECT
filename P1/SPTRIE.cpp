#include "SPTRIE.h"

bool ENABLE_STRING_PRINTS = 1;

// Trie structure and nodes
class Node
{
public:    
    bool is_leaf;
    string value = "";
    map<char, Node> child;
    Node(const string& val = "") : value(val), is_leaf(false) {}
    
    void add(char c)
    {
        if (value == "")
            child[c] = Node(string(1, c));
        else
            child[c] = Node(value + c);
    }
};

class Trie
{
private:
  Node head;
public:
	int edges = 0;
  	Trie() : head() {}

	Trie(tuple<
	vector<string>,
	vector<int>,
	vector<int>,
	int, 
	int> BUILDER) : head() {
		auto S = get<0>(BUILDER);
		auto p_insert = get<1>(BUILDER);
		auto p_read = get<2>(BUILDER);
		auto M = get<3>(BUILDER);
		auto N = get<4>(BUILDER);

		vector<string> S_INSERT;
		for (string word : S){
			string new_word;
			new_word.clear();
			for (auto i : p_insert){
				new_word.push_back(word[i]);
			}
			S_INSERT.push_back(new_word);
			insert(new_word);
		}
		//preorder_HEU_file(p_insert);
	}
  
  string find(const string& word)
  {
    Node* node = &head;
    for (auto&& ch : word) {
      if (node->child.find(ch) == node->child.end()) return "";
      node = &node->child[ch];
    }
    return node->value;
  }

  void insert(const string& word)
  {
    Node* node = &head;
    for (auto&& ch : word) {
      if (node->child.find(ch) == node->child.end()) {node->add(ch); edges++;}
      node = &node->child[ch];
    }
    node->is_leaf = true;
  }

	void preorder(){
		int cnt = 0; 
		cout << "Trie: ";
		print_preorder(&head, cnt);
		cout << "\nAristas: "<< edges <<"\n";
	}

	void print_preorder(Node* node, int &count){
    if (node == NULL)
			return;
		
    cout << node->value << " ";

		for (map<char,Node>::iterator it=node->child.begin(); it!=node->child.end(); ++it)
			print_preorder(&it->second, count);
	}

	void preorder_HEU_file(vector<int> p,string FILENAME){
		int cnt = 0; 
		int depth = 0;
		ofstream out;
		out.open(FILENAME, ios::app);
		print_preorder_HEU_file(&head, cnt, depth, p,out);
		out << "-\n";
		out.close();
	}

	void print_preorder_HEU_file(Node* node, int &count, int depth, vector<int> p, ofstream &out){
		if (node == NULL)
			return;
		if (node == &(this->head)){
			for (map<char,Node>::iterator it=node->child.begin(); it!=node->child.end(); ++it){
				print_preorder_HEU_file(&it->second, count, depth,p,out);
			}
		}
		else{
			#ifdef PRINTING
			printf("S(%d,%d,%d,%c)\n", 0, 0, p[depth], node->value[node->value.length()-1]); 
			#endif
			out << "S(" << 0 <<"," << 0 << "," << p[depth] << "," << node->value[node->value.length()-1] <<")\n";	

			for (map<char,Node>::iterator it=node->child.begin(); it!=node->child.end(); ++it){
				print_preorder_HEU_file(&it->second, count, depth + 1,p,out);
			}
				
			#ifdef PRINTING
			printf("E(%d,%d,%d,%c)\n", 0, 0, p[depth], node->value[node->value.length()-1]); 
			#endif
			out << "E(" << 0 <<"," << 0 << "," << p[depth] << "," << node->value[node->value.length()-1] <<")\n";	
		}
	}
};

// heuristic MIN SPTRIE generation
tuple<
	vector<string>,
	vector<int>,
	vector<int>,
	int, 
	int> Min_Trie_Heuristic(vector<string> S_INPUT){

	// set M,N
    int N = S_INPUT.size();
    int M = S_INPUT[0].length();
    
	// store the max value and character of each column
	vector<int> value(M,0);
	vector<char> character(M);

	// store the accumulated count of each character found
	map<char, int> char_accumulated_count;
	
	// iterating by cols
	for(auto i = 0; i < M; i++){
		map<char, int> column_instances;

		// iterating by rows
		for(auto j = 0; j < N; j++){
			char current = S_INPUT[j][i];
			column_instances[current] = column_instances[current] + 1;
		}

		// obtain largest character stored in this column iteration
		map<char,int>::iterator max
        = max_element(column_instances.begin(),column_instances.end(),[] 
					(const pair<char,int>& a, const pair<char,int>& b)->bool{return a.second < b.second;});
		
		// store character and its max current values
		character[i] = max->first;
		value[i] = max->second;

		// add to the accumulated count of each character
		char_accumulated_count[max->first] = char_accumulated_count[max->first] + max->second;
	}

	// vector of increasing indexes
	vector<int> p(M);
    iota(begin(p), end(p), 0);
	
	// create p_insert and sort the permutation based on 
	// largest column value or its character's accumulated count
	auto p_insert = p;
	sort(p_insert.begin(),p_insert.end(), [&](int i,int j)
	{
		if (value[i] == value[j]){
			return 	char_accumulated_count[character[i]] > 
					char_accumulated_count[character[j]];
		}
		else return value[i] > value[j];
	} );

	// create p_read and let it inverse the p_insert permutation
    auto p_read = p;
	for(int i = 0; i < M; i++){
        p_read[p_insert[i]] = p[i]; 
    }

	return make_tuple(S_INPUT, p_insert,p_read,M,N);
}

// build trie structure
Trie build(tuple<vector<string>,vector<int>,vector<int>,int,int> HEU,string FILENAME){
	Trie SPTRIE(HEU);
	return SPTRIE;
}

// build trie structure and output to FILENAME
int build_and_output(tuple<vector<string>,vector<int>,vector<int>,int,int> HEU,string FILENAME){
	Trie SPTRIE(HEU);
	SPTRIE.preorder_HEU_file(get<1>(HEU),FILENAME);
	return SPTRIE.edges;
}

// int main(int argc, char** argv){

// 	// aaaa,baca,caca,cdcd | aaa,baa,bac,cbb
// 	if (argc > 1){
// 		string a = argv[1];
// 		if (a == "noprint")
// 			ENABLE_STRING_PRINTS = 0;
// 	}

// 	std::cout <<"insertar cadenas(separadas por comas): ";
// 	std::string input;
// 	std::cin >> input;
// 	std::vector<std::string> keys;
// 	std::stringstream ss(input);

// 	while (ss.good()) {
// 		std::string key;
// 		getline(ss, key, ',');
// 		keys.push_back(key);
// 	}

//   cout << "Cadenas a probar: ";
// 	for (auto key : keys) {
// 		if(ENABLE_STRING_PRINTS) std::cout << key <<", ";
// 	}
// 	std::cout << '\n';

//     /*Trie T_OG;
	
// 	for (auto in : keys) {
// 		T_OG.insert(in);
// 	}

// 	T_OG.preorder();
	
//     std::cout << "_______________________\n\n";
// */
// 	auto output = Min_Trie_Heuristic(keys);
// 	build_and_output(output);
// 	build_and_output(output);
// 	build_and_output(output);
// 	// Trie T;
	
// 	// for (auto out : output) {
// 	// 	T.insert(out);
// 	// }

// 	// T.preorder();

//     // cout << "Cadenas resultantes: ";
// 	// for (auto w : output){
// 	// 	if(ENABLE_STRING_PRINTS) std::cout << w <<", ";
// 	// }
// }
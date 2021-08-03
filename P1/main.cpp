#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <numeric>
#include <sstream>
#include <algorithm>
#include <queue>

using namespace std;

bool ENABLE_STRING_PRINTS = 1;

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
		
    if(ENABLE_STRING_PRINTS) cout << node->value << " ";

		for (map<char,Node>::iterator it=node->child.begin(); it!=node->child.end(); ++it)
			print_preorder(&it->second, count);
	}
};

vector<string> min_trie(vector<string> S_INPUT){
    int N = S_INPUT.size();
    int M = S_INPUT[0].length();

    vector<int> p(M);
    iota(begin(p), end(p), 0);
    
	int value[M] = {0};
	char character[M] = "";
	map<char, int> char_accumulated_count;
	
	for(auto i = 0; i < M; i++){
		map<char, int> column_instances;

		for(auto j = 0; j < N; j++){
			char current = S_INPUT[j][i];
			column_instances[current] = column_instances[current] + 1;
		}
		
		map<char,int>::iterator max
        = max_element(column_instances.begin(),column_instances.end(),[] 
					(const pair<char,int>& a, const pair<char,int>& b)->bool{return a.second < b.second;});
		
		character[i] = max->first;
		value[i] = max->second;
		char_accumulated_count[max->first] = char_accumulated_count[max->first] + max->second;
	}

	auto applied_p = p;
	sort(applied_p.begin(),applied_p.end(), [&](int i,int j)
	{
		if (value[i] == value[j]){
			return char_accumulated_count[character[i]] > char_accumulated_count[character[j]];
		}
		else return value[i] > value[j];
	} );

    auto p_result = p;
	cout << "Permutación obtenida: [";
	for(int i = 0; i < M; i++){
        p_result[applied_p[i]] = p[i]; 
    }
    for(int i = 0; i < M; i++)
        cout << p_result[i]<<',';
    cout << "]\n";

	vector<string> S_OUTPUT;
	for (string word : S_INPUT){
		string new_word;
		new_word.clear();
		for (auto i : applied_p){
			new_word.push_back(word[i]);
		}
		S_OUTPUT.push_back(new_word);
	}
	
	return S_OUTPUT;
}

int main(int argc, char** argv){

	// aaaa,baca,caca,cdcd | aaa,baa,bac,cbb
	if (argc > 1){
		string a = argv[1];
		if (a == "noprint")
			ENABLE_STRING_PRINTS = 0;
	}

	std::cout <<"insertar cadenas(separadas por comas): ";
	std::string input;
	std::cin >> input;
	std::vector<std::string> keys;
	std::stringstream ss(input);

	while (ss.good()) {
		std::string key;
		getline(ss, key, ',');
		keys.push_back(key);
	}



  cout << "Cadenas a probar: ";
	for (auto key : keys) {
		if(ENABLE_STRING_PRINTS) std::cout << key <<", ";
	}
	std::cout << '\n';

    Trie T_OG;
	
	for (auto in : keys) {
		T_OG.insert(in);
	}

	T_OG.preorder();
	
    std::cout << "_______________________\n\n";

	vector<string> output = min_trie(keys);
	
	Trie T;
	
	for (auto out : output) {
		T.insert(out);
	}

	T.preorder();

    cout << "Cadenas resultantes: ";
	for (auto w : output){
		if(ENABLE_STRING_PRINTS) std::cout << w <<", ";
	}
}
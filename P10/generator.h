#ifndef GENERATOR_H_
#define GENERATOR_H_

#include <iostream>
#include <string.h> 
#include <vector>
#include <random>
#include <algorithm>
#include <fstream>

std::vector<std::string> stringGenerator (int N, int M){
    std::vector<std::string> store(N,std::string(M, '-'));
    std::string word;
    static const char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
	for (int j = 0; j < M; ++j){
		for (int i = 0; i < N; ++i) {
			word += alphabet[rand() % (sizeof(alphabet)-1)];
		}
		std::sort(word.begin(), word.end());
		for (int i = 0; i < N; ++i) {
			store[i][j] = word[i];
		}
        word.clear();
	}
  return store;
}

void generateStrings (int N, int M, std::string name){
    std::ofstream myfile;
    // myfile.open ("generate.prolog");
    // myfile.close();
    myfile.open ("generate.prolog",std::ios::app);
    
    auto matrix = stringGenerator(N, M);
    for (auto string: matrix){
        std::cout << name << ' ' << string << '\n';
        myfile << name << ' ' << string << '\n';
    }
}

#endif
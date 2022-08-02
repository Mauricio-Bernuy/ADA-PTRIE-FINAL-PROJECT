### Diseño e implementación de algoritmos de construcción óptima para la Estructura de Datos PTrie, mediante Heurística Voráz, Recurrencia, Memoización y Programación Dinámica utilizando C++

# Essay (click to open file)
[<img src="https://i.imgur.com/QEfMZqS.jpg">](https://github.com/Mauricio-Bernuy/ADA_FINAL_PROJECT/blob/main/Monograf%C3%ADa%2C%20Proyecto%20ADA.pdf)

# build

g++ -g P6\read_and_exec_prolog.cpp P1\SPTRIE.cpp P3\SPTRIEGEN.cpp P6\read_prolog.cpp -o execute.plg 


g++ -D TIMINGS -g P6\trie_generator.cpp P1\SPTRIE.cpp P3\SPTRIEGEN.cpp P6\read_prolog.cpp -o compile.plg       

# execute

./compile.plg --WORKMODE i-input o-trie
              --heuristic --recursive --memoized --dynprog
              

./execute.plg i-trie o-response < queries.prolog

# execute on one line

compile.plg --dynprog i-input o-trie && execute.plg i-trie o-response < queries.prolog

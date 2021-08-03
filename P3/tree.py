import pydot 
# pip install pydot # sudo apt install graphviz




graph = pydot.Dot('my_graph', graph_type='graph', bgcolor='white')

def peek_line(f):
    pos = f.tell()
    line = f.readline()
    f.seek(pos)
    return line

#a = open("output.txt","rt")

count = 0


trie = []

with open("output.txt","rt") as a:
  x = a.readline()
  while x:
    if (x[0] == '#'):
        b = x.split(' ')
        if (b[1] == "starting"):
            #if (peek_line(a)):
                
            print("it is estarting!")
            xx = peek_line(a)
            xx = xx.replace('(',"")
            xx = xx.replace(") \n","")
            c = xx.split(" -> ")
            xxx = c[0].split(',')
            xxx_ = c[1]

            if (len(xxx) == 3):
                print("yay")
                print(xxx,xxx_)
                trie.append( ( int(xxx[2]),xxx_))

            elif (len(xxx) == 2):
                print("arbitrary")
                trie.append("...")
            
        elif (b[1] == "ending"):
            print("it is ending!")
        #print(a)

    elif (x == '(REACHED LEAF)\n'):
        print("it got to a leaf!")
        trie.append('|')
    
    x = a.readline()
    count = count + 1
    
print("\n\n\n\n\n")
print(trie)

#def printer(trie_, i, next):
truecnt = 0
index = 0
lastlabel = ""
if (trie[0] != "..."):
   lastlabel = trie[0][0]
while(1):
    #print("lastlabel:",lastlabel)

    if (trie[index + 1] == '|'):
        print("root token")
        for i in range(index, 0, -1):
            print(i)
            if (trie[i][0] == lastlabel):
                print("found ", i) 
                index = i       
                
    elif (trie[index + 1] == "..."):
        #print(trie[index + 1])
        graph.add_node(pydot.Node(truecnt+1, label = "...", shape='circle'))
        #lastlabel = ""
    else:
        graph.add_node(pydot.Node(truecnt+1, label = trie[index+1][0], shape='circle'))
        lastlabel = trie[index+1][0]

    graph.add_node(pydot.Node(truecnt, label = trie[index][0], shape='circle'))
    graph.add_edge(pydot.Edge(truecnt, truecnt+1,label = trie[index][1], color='blue'))
    index = index + 1
    truecnt = truecnt + 1
    if (truecnt > 12): break

a.close()

graph.write_png('output.png')

# # Add nodes
# my_node = pydot.Node('a',label="ssss")
# graph.add_node(my_node)
# # Or, without using an intermediate variable:
# graph.add_node(pydot.Node('a', label = "sss", shape='circle'))


# # Add edges
# my_edge = pydot.Edge('a', 'b', label='Foo', color='blue')
# graph.add_edge(my_edge)
# # Or, without using an intermediate variable:
# graph.add_edge(pydot.Edge('b', 'c', color='blue'))

# 


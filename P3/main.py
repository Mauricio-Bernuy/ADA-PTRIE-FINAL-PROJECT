
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
    

print(trie)

#def printer(trie_, i, next):

index = 0
while(1):
    node() edge()

a.close()

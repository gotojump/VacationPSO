	main = Main
	lib = TS
	file = grafo.in
	flags = -Wall -g

all: comp exec

comp:	$(main).cpp $(lib).cpp $(lib).hpp
	g++ $(flags) $(main).cpp $(lib).cpp -o $(main)

exec:
	./$(main)	-g -c 10 -l 100 -f grafo.in
	./$(main) -f grafo.in -ca 20

clean:
	rm -rf $(main)

CXX		?= g++
LFLAGS 	?= -lcurl
DFLAGS	?= -pedantic -Wall -W -Wextra -Werror
OFLAGS 	?= -O2 -pipe -march=native
OBJECTS	?= bin/functions.o bin/main.o

#change to OFLAGS to compile optimized binaries. DFLAGS stands for debugging
FLAGS	?= $(DFLAGS) $(LFLAGS)

target:	$(OBJECTS)
	$(CXX) -o APICaller $(OBJECTS) $(FLAGS)

bin/%.o: src/%.cpp
	$(CXX) -c -o $@ $< $(FLAGS)

clean:
	rm bin/* APICaller

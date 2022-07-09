CXX		?= g++
LFLAGS 	?= -lcurl
DFLAGS	?= -pedantic -Wall -W -Wextra -Werror
OFLAGS 	?= -O2 -pipe -march=native
CFLAGS	?= -std=c++17
OBJECTS	?= bin/functions.o bin/main.o

target:	$(OBJECTS)
	$(CXX) -o APICaller $(OBJECTS) $(DFLAGS) $(LFLAGS) $(CFLAGS)

bin/%.o: src/%.cpp | bin
	$(CXX) -c -o $@ $< $(FLAGS)

bin:
	mkdir -p $@

clean:
	rm -rf bin APICaller

debug:	$(OBJECTS)
	$(CXX) -o APICaller $(OBJECTS) $(DFLAGS) $(LFLAGS) $(CFLAGS)

release:	$(OBJECTS)
	$(CXX) -o APICaller $(OBJECTS) $(OFLAGS) $(LFLAGS) $(CFLAGS)

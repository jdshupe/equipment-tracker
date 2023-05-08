CC = g++
src = $(wildcard src/*.cpp) \
	  $(wildcard src/divs/*.cpp) \
	  $(wildcard src/elements/*.cpp)
obj = $(src:.cpp=.o)

LDFLAGS = -lpqxx -lncurses 

equipmentTracker: $(obj)
	$(CC) -std=c++2a -ggdb -Wl,-rpath,lib -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(obj) myprog

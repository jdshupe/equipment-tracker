CC = g++
src = $(wildcard src/*.cpp) \
	  $(wildcard src/divs/*.cpp)
obj = $(src:.cpp=.o)

LDFLAGS = -lpqxx -lncurses 

equipmentTracker: $(obj)
	$(CC) -ggdb -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(obj) myprog

CC = g++
src = $(wildcard src/*.cpp)
obj = $(src:.cpp=.o)

LDFLAGS = -lncurses -lpqxx

equipmentTracker: $(obj)
	$(CC) -g -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(obj) myprog

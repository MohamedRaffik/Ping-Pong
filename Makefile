CXX := /usr/bin/g++
CXXFLAGS = -Wall 
SDL = -lSDL2 -lSDL2_ttf -lSDL2_image -no-pie
SRCS = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp,%.o,$(SRCS))
PROG = Pong

all: $(PROG)

.PHONY: clean cleanall
clean:
	rm -f $(OBJS)

cleanall:
	rm -f $(OBJS) $(PROG)

$(PROG): $(OBJS)
	$(CXX) -o $(PROG) $(OBJS) $(SDL) 

.cpp:
	$(CXX) -c $@.cpp $(CXXFLAGS)

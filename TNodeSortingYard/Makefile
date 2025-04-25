CXX = g++
CXXFLAGS = -I/usr/local/include -std=c++17
LDFLAGS = -L/usr/local/lib -lsfml-graphics -lsfml-window -lsfml-system

SOURCES = src/main.cpp src/sorting_yard.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = TNodeSortingYard

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

.PHONY: all clean
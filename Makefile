CPP_SOURCES = DebayerFilter.cpp main.cpp
CPP_HEADERS = DebayerFilter.hpp
CPP_OBJECTS = $(patsubst %.cpp,%.o,$(CPP_SOURCES))

all: out

$(CPP_OBJECTS): %.o: %.cpp $(CPP_HEADERS)
	g++ -o $@ -c $<

out: $(CPP_OBJECTS)
	g++ -o $@ $^

.PHONY: clean
clean:
	rm out
	rm *.o
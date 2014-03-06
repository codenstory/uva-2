
sources = $(wildcard *.cpp)
bins = $(sources:.cpp=.exe)
tests = $(sources:.cpp=.test)

all: $(bins) $(tests)

%.exe: %.cpp
	g++ -o $@ -std=c++11 -g -DONLINE_JUDGE $^

%.test: %.cpp
	g++ -o $@ -std=c++11 -g $^ -lgtest -lgtest_main

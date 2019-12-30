build:
	g++ -std=c++11 $(shell find . -name "*.cpp") -lgtest -lgtest_main -o zeroevenodd

run:
	./zeroevenodd
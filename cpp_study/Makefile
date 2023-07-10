# demo1:demo1.cc
# 	g++ -o $@ $^ -std=c++11
# .PHONY:clean
# clean:
# 	rm -f demo1

all: demo1 smart_point
demo1: demo1.cc
	g++ -o $@ $^ -std=c++11
smart_point: smart_point.cc
	g++ -o $@ $^ -std=c++11
.PHONY: clean
clean:
	rm -f demo1 smart_point
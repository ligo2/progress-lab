EXEC = vector
SRC = vector.cpp
DEBUG = debug

$(EXEC): $(SRC)
	g++ -o $@ $^ -std=c++11

debug:
$(DEBUG): $(SRC)
	g++ -o  $@ $^ -std=c++11 -g

.PHONY: clean
clean:
	rm -f $(EXEC) $(DEBUG)
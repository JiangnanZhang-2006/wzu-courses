# 本地编译：make 或 make 3821
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2

3821: 3821.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

.PHONY: clean
clean:
	rm -f 3821

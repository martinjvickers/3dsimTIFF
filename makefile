CC = g++ -std=c++14
LIB = -lm -ltiff

all : 3dsimTIFF

3dsimTIFF : main.cpp
	$(CC) -g -O2 $^ $(LIB) -o $@

clean:
	rm 3dsimTIFF

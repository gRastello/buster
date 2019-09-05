default: stacky

stacky: runtest build/main.o build/stacky.o build/cpu.o build/bus.o
	g++ -o build/stacky build/main.o build/stacky.o build/cpu.o build/bus.o
	
build/main.o: src/main.cpp src/stacky.hpp
	mkdir -p build
	g++ -o build/main.o -c src/main.cpp

build/stacky.o: src/stacky.cpp src/stacky.hpp src/bus.hpp
	mkdir -p build
	g++ -o build/stacky.o -c src/stacky.cpp

build/cpu.o: src/cpu.cpp src/cpu.hpp src/bus.hpp
	mkdir -p build
	g++ -o build/cpu.o -c src/cpu.cpp

build/bus.o: src/bus.cpp src/bus.hpp src/cpu.hpp
	mkdir -p build
	g++ -o build/bus.o -c src/bus.cpp

run: build/stacky
	./build/stacky

build/test: src/test.cpp src/stacky.hpp src/bus.hpp src/cpu.hpp
	mkdir -p build
	g++ -o build/test src/test.cpp

runtest: build/test
	./build/test

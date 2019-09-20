# buster targets

default: buster

buster: runtest build/main.o build/buster.o build/cpu.o build/bus.o
	g++ -o build/buster build/main.o build/buster.o build/cpu.o build/bus.o
	
build/main.o: src/main.cpp src/buster.hpp
	mkdir -p build
	g++ -o build/main.o -c src/main.cpp

build/buster.o: src/buster.cpp src/buster.hpp src/bus.hpp
	mkdir -p build
	g++ -o build/buster.o -c src/buster.cpp

build/cpu.o: src/cpu.cpp src/cpu.hpp src/bus.hpp
	mkdir -p build
	g++ -o build/cpu.o -c src/cpu.cpp

build/bus.o: src/bus.cpp src/bus.hpp src/cpu.hpp
	mkdir -p build
	g++ -o build/bus.o -c src/bus.cpp

run: build/buster
	./build/buster

build/test: src/test.cpp src/buster.cpp src/bus.cpp src/cpu.cpp\
			src/buster.hpp src/bus.hpp src/cpu.hpp
	mkdir -p build
	g++ -o build/test src/test.cpp

runtest: build/test
	./build/test

# nono targets

build/nono/token.o: src/nono/token.cpp src/nono/token.hpp
	mkdir -p build/nono
	g++ -o build/nono/token.o -c src/nono/token.cpp

build/nono/lexer.o: src/nono/lexer.cpp src/nono/lexer.hpp src/nono/token.hpp
	mkdir -p build/nono
	g++ -o build/nono/lexer.o -c src/nono/lexer.cpp

build/nono/statement.o: src/nono/statement.cpp src/nono/statement.hpp\
                        src/nono/token.hpp
	mkdir -p build/nono
	g++ -o build/nono/statement.o -c src/nono/statement.cpp

build/nono/parser.o: src/nono/parser.cpp src/nono/parser.hpp src/nono/token.hpp\
                     src/nono/statement.hpp
	mkdir -p build/nono
	g++ -o build/nono/parser.o -c src/nono/parser.cpp

build/nono/analyzer.o: src/nono/analyzer.cpp src/nono/analyzer.hpp\
                       src/nono/statement.hpp
	mkdir -p build/nono
	g++ -o build/nono/analyzer.o -c src/nono/analyzer.cpp

build/nono/generator.o: src/nono/generator.cpp src/nono/generator.hpp\
                        src/nono/statement.hpp
	mkdir -p build/nono
	g++ -o build/nono/generator.o -c src/nono/generator.cpp

build/nono/test: src/nono/test.cpp src/nono/token.cpp src/nono/lexer.cpp\
				 src/nono/token.hpp src/nono/lexer.hpp src/nono/parser.hpp\
				 src/nono/parser.cpp src/nono/statement.hpp src/nono/statement.cpp\
				 src/nono/analyzer.cpp src/nono/generator.cpp
	mkdir -p build/nono
	g++ -o build/nono/test src/nono/test.cpp

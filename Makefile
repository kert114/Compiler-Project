CPPFLAGS += -std=c++17 -W -Wall -g -Wno-unused-parameter
CPPFLAGS += -I include

all: bin/compiler bin/c_compiler

bin/c_compiler : bin/compiler src/wrapper.sh
	cp src/wrapper.sh bin/c_compiler
	dos2unix bin/c_compiler
	chmod u+x bin/c_compiler

src/parser.tab.cpp src/parser.tab.hpp : src/parser.y
	bison -v -d src/parser.y -o src/parser.tab.cpp

src/lexer.yy.cpp : src/lexer.flex src/parser.tab.hpp
	flex -o src/lexer.yy.cpp  src/lexer.flex

bin/compiler : src/compiler.o src/parser.tab.o src/lexer.yy.o src/parser.tab.o
	mkdir -p bin
	g++ $(CPPFLAGS) -o bin/compiler $^

clean :
	rm src/*.o
	rm bin/*
	rm src/*.tab.cpp
	rm src/*.tab.hpp
	rm src/*.yy.cpp
	rm output/*
	rm src/*.output
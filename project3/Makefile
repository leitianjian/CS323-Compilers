CC=g++
FLEX=flex
BISON=bison

.lex: scanner.l
	$(FLEX) -o scanner.cpp scanner.l
.syntax: parser.y
	$(BISON) -o parser.cpp -d -v parser.y
splc: .lex .syntax
	# touch bin/splc
	# @chmod +x bin/splc
	$(CC) --std=c++17 -g main.cpp scanner.cpp parser.cpp ICG.cpp interpreter.cpp ASTNode.cpp SematicAnalyzer.cpp NodeVisitor.cpp SymTab.cpp instruction.cpp CodeOptimizer.cpp -o bin/splc
clean:
	rm -rf scanner.cpp
	rm -rf parser.cpp parser.hpp location.hh position.hh stack.hh
	rm -rf a.out
	rm -rf bin/* *.output
	# @rm -f lex.yy.c syntax.tab.* *.out bin/* *.output
clean_out:
	rm -f ./my_test/*.out*

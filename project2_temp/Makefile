CC=gcc
FLEX=flex
BISON=bison

.lex: lex.l
	$(FLEX) -o lex.cpp lex.l
.syntax: parser.y
	$(BISON) -o parser.cpp -t -d -v parser.y
splc: .lex .syntax
	# @mkdir bin
	# touch bin/splc
	# @chmod +x bin/splc
	$(CC) parser.cpp lex.cpp -lfl -ly -o bin/splc
clean:
	@rm -rf bin/
.PHONY: splc

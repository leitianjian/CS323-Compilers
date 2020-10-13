CC=gcc
FLEX=flex
BISON=bison

.lex: lex.l
	$(FLEX) lex.l
.syntax: syntax.y
	$(BISON) -t -d -v syntax.y
p: .lex .syntax
	$(CC) syntax.tab.c -lfl -ly -o p.out
clean:
	@rm -f lex.yy.c syntax.tab.* *.out
# splc:
# 	@mkdir bin
# 	touch bin/splc
# 	@chmod +x bin/splc
# clean:
# 	@rm -rf bin/
# .PHONY: splc
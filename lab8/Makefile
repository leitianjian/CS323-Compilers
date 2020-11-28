CC=gcc
FLEX=flex
BISON=bison


.lex: lex.l
	$(FLEX) lex.l
.syntax: syntax.y
	$(BISON) -t -d syntax.y
jc: .lex .syntax
	$(CC) -g syntax.tab.c SymTab.c -lfl -ly -o jc.out
clean:
	@rm -f lex.yy.c syntax.tab.* *.out

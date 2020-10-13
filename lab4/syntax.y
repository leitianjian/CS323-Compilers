%{
    #include"lex.yy.c"
    void yyerror(const char*);
%}

%token LC RC LB RB COLON COMMA
%token STRING NUMBER
%token TRUE FALSE VNULL
%%

Json:
      Value
    | Value RB error { puts("extra close, recovered"); }
    | Value COMMA error { puts("comma after the close, recovered"); }
    ;
Value:
      Object
    | Array
    | STRING
    | NUMBER
    | TRUE
    | FALSE
    | VNULL
    | Object STRING error { puts("misplaced quoted value, recovered"); }  // 为什么和31行有冲突？不是很理解
    /* | Value RB error { puts("extra close"); } */
    ;
Object:
      LC RC
    | LC Members RC
    | LC Values RC error { puts("comma instead of colon, recovered"); }
    | LC Members Value RC error { puts("multiple value is not allowed, recovered"); }
    ;
Members:
      Member
    | Member COMMA Members
    | Member COMMA error { puts("extra comma, recovered"); }
    /* | Member Value error { puts("multiple value is not allowed, recovered"); } */
    ;
Member:
      STRING COLON Value
    | STRING COLON COLON Value error { puts("double colon, recovered"); }
    | STRING Value error { puts("missing colon, recovered"); }
    ;
Array:
      LB RB
    | LB Values RB
    | LB Values RC error { puts("unmatched right bracket, recovered"); }
    | LB Members RB error { puts("colon instead of comma, recovered"); }
    | LB Values error { puts("unclosed array, recovered"); }
    ;
Values:
      Value
    | Value COMMA Values
    | Value COMMA error { puts("extra comma, recovered"); }
    | Value COMMA COMMA error { puts("double extra comma, recovered"); }
    | COMMA Value error { puts("missing value, recovered"); }
    ;
%%

void yyerror(const char *s){
    /* printf("syntax error: must be recovered "); */
    printf("syntax error: ");
}

int main(int argc, char **argv){
    if(argc != 2) {
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        exit(-1);
    }
    else if(!(yyin = fopen(argv[1], "r"))) {
        perror(argv[1]);
        exit(-1);
    }
    yyparse();
    return 0;
}

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
    ;
Value:
      Object
    | Array
    | STRING
    | NUMBER
    | TRUE
    | FALSE
    | VNULL
    ;
Object:
      LC RC
    | LC Members RC
    /* | LC Members COMMA RC error { puts("extra comma1, recovered"); } */
    /* | LC Members COMMA error { puts("comma instead if closing brace, recovered"); } */
    ;
Members:
      Member
    | Member COMMA Members
    ;
Member:
      STRING COLON Value
    | STRING COLON COLON Value error { puts("double colon, recovered"); }
    | STRING Value error { puts("missing colon, recovered"); }
    | STRING COMMA Value error { puts("comma instead of colon, recovered"); }
    ;
Array:
      LB RB
    | LB Values RB
    | LB Values RC error { puts("unmatched right bracket, recovered"); }
    /* | LB Values COMMA RB error { puts("extra comma2, recovered"); } */
    ;
Values:
      Value
    | Value COMMA Values
    ;
%%

void yyerror(const char *s){
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

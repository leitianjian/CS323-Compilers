%{
    #include <stdbool.h>
    #include"lex.yy.c"
    void yyerror(const char*);

%}
%union{
    char *string;
}

%token LC RC LB RB COLON COMMA
%token <string> STRING 
%token TRUE FALSE VNULL NUMBER
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
      LC RC { pop(head); }
    | LC Members RC { pop(head); }
    ;
Members:
      Member
    | Member COMMA Members
    ;
Member:
      STRING COLON Value { int result = insert_symbol(head, $1); if (!result) is_valid = 0; }
    ;
Array:
      LB RB
    | LB Values RB
    ;
Values:
      Value
    | Value COMMA Values
    ;
%%

int main(int argc, char **argv){
    if(argc != 2) {
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        exit(-1);
    }
    else if(!(yyin = fopen(argv[1], "r"))) {
        perror(argv[1]);
        exit(-1);
    }
    head = symTab_init();
    yyparse();
    if(is_valid) {
        printf("%d\n", is_valid);
    }
    return 0;
}

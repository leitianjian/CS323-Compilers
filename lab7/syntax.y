%{
    #include"lex.yy.c"
    void yyerror(const char*);
%}
%union {
    struct Json *json;
    struct Object *object;
    struct Array *array;
    char *string;
    double number;
    int b;
}

%token LC RC LB RB COLON COMMA
%token<string> STRING 
%token<number> NUMBER
%token<b> TRUE FALSE 
%token<json> VNULL

%type<json> Json Value
%type<array> Array Values
%type<object> Object Member Members
%%

Json:
      Value { $$ = $1; }
    | Value RB error { puts("extra close, recovered"); }
    | Value COMMA error { puts("comma after the close, recovered"); }
    ;
Value:
      Object { $$ = init_json(CA_OBJECT); $$->val.object = $1; }
    | Array { $$ = init_json(CA_ARRAY); $$->val.array = $1; }
    | STRING { $$ = init_json(CA_STRING); $$->val.string = $1; }
    | NUMBER { $$ = init_json(CA_NUMBER); $$->val.number = $1; }
    | TRUE { $$ = init_json(CA_BOOLEAN); $$->val.b = $1; }
    | FALSE { $$ = init_json(CA_BOOLEAN); $$->val.b = $1; }
    | VNULL { $$ = $1; }
    | Object STRING error { puts("misplaced quoted value, recovered"); }  // 为什么和31行有冲突？不是很理解
    /* | Value RB error { puts("extra close"); } */
    ;
Object:
      LC RC { $$ = init_object(); }
    | LC Members RC { $$ = $2; }
    | LC Values RC error { puts("comma instead of colon, recovered"); }
    | LC Members Value RC error { puts("multiple value is not allowed, recovered"); }
    ;
Members:
      Member { $$ = $1; }
    | Member COMMA Members { $$ = $1; $$->next_object = $3; }
    | Member COMMA error { puts("extra comma, recovered"); }
    /* | Member Value error { puts("multiple value is not allowed, recovered"); } */
    ;
Member:
      STRING COLON Value { $$ = init_object(); $$->key = $1; $$->value = $3; }
    | STRING COLON COLON Value error { puts("double colon, recovered"); }
    | STRING Value error { puts("missing colon, recovered"); }
    ;
Array:
      LB RB { $$ = init_array(); $$->value = NULL; }
    | LB Values RB { $$ = $2; }
    | LB Values RC error { puts("unmatched right bracket, recovered"); }
    | LB Members RB error { puts("colon instead of comma, recovered"); }
    | LB Values error { puts("unclosed array, recovered"); }
    ;
Values:
      Value { $$ = init_array(); $$->value = $1; }
    | Value COMMA Values { $$ = init_array(); $$->value = $1; $$->next_value = $3;}
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

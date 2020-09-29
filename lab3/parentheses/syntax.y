%{
    #include"lex.yy.c"
    void yyerror(const char *s){}
    int result = 0;
%}
%token LP RP LB RB LC RC
%%
validString: String { result = 1; }

String: %empty {}
    | LP String RP String
    | LB String RB String
    | LC String RC String
%%

int validParentheses(char *expr){
    yy_scan_string(expr);
    yyparse();
    return result;
}

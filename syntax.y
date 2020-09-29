%{
    #include"lex.yy.c"
    void yyerror(const char *s){
        fprintf(stderr, "Syntax error: %s\n", s);
    }
    int result = 0;
%}
%token LP RP LB RB LC RC
%%
Single: LP { result = 1; } Single RP 
    | LB { result = 1; } Single RB
    | LC { result = 1; } Single RC 
    | %empty {}
    ;
%%

#ifndef CALC_MAIN
int validParentheses(char *expr){
    yy_scan_string(expr);
    yyparse();
    return result;
}
#else
int main(){
    yyparse();
    printf(" = %d\n", result);
}
#endif

%{
    #include"syntax.tab.h"
    extern "C" int yylex();
%}
%option noyywrap
%%
"(" { return LP; }
")" { return RP; }
"[" { return LB; }
"]" { return RB; }
"{" { return LC; }
"}" { return RC; }

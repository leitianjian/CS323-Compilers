%{
    #include"lex.yy.c"
    struct ASTNode *root = NULL;
    void SYNError(const char *, int);
    void yyerror(const char*);
    void initiate();
%}
%locations
%union{
    struct ASTNode *node_v;
}

%token <node_v> LP RP LC RC LB RB COMMA DOT SEMI 
%token <node_v> LT LE GT GE NE EQ PLUS MINUS MUL DIV AND OR NOT ASSIGN
%token <node_v> STRUCT 
%token <node_v> ID 
%token <node_v> CHAR
%token <node_v> INT 
%token <node_v> FLOAT
%token <node_v> WHILE TYPE
%token <node_v> IF ELSE RETURN UNKNOW

%type  <node_v> Program ExtDefList ExtDef ExtDecList
%type  <node_v> Specifier StructSpecifier 
%type  <node_v> VarDec FunDec VarList ParamDec
%type  <node_v> CompSt StmtList Stmt DefList Def DecList Dec
%type  <node_v> Exp Args 

%nonassoc LOWER_ELSE
%nonassoc ELSE
%right ASSIGN
%left OR
%left AND
%left LT LE GT GE EQ NE
%left PLUS MINUS
%left MUL DIV
%right UMINUS NOT
%left LP RP LB RB DOT
%left UNKNOW


%%

Program: 
      ExtDefList {
          $$ = newNode("Program", @$.first_line);
          root = $$;
          addChild($$, 1, $1);
      }
    ;
ExtDefList:
      ExtDef ExtDefList {
          $$ = newNode("ExtDefList", @$.first_line);
          addChild($$, 2, $1, $2);
      }
    | {
          $$ = newNode("NONE", @$.first_line); 
      }
    ;
ExtDef:
      Specifier ExtDecList SEMI {
          $$ = newNode("ExtDef", @$.first_line);
          addChild($$, 3, $1, $2, $3);
      }
    | Specifier SEMI {
          $$ = newNode("ExtDef", @$.first_line);
          addChild($$, 2, $1, $2);
      }
    | Specifier FunDec CompSt {
          $$ = newNode("ExtDef", @$.first_line);
          addChild($$, 3, $1, $2, $3);
      }
    | Specifier ExtDecList error {
          error = 1;
          SYNError("Missing semicolon ';'", @$.first_line);
      }
    | ExtDecList error {
        error = 1;
        SYNError("Missing specifier", @$.first_line);
    }
    ;
ExtDecList:
      VarDec {
          $$ = newNode("VarDec", @$.first_line);
          addChild($$, 1, $1);
      }
    | VarDec COMMA ExtDecList {
          $$ = newNode("ExtDecList", @$.first_line);
          addChild($$, 3, $1, $2, $3);
      }
    ;
Specifier:
      TYPE {
          $$ = newNode("Specifier", @$.first_line);
          addChild($$, 1, $1);
      }
    | StructSpecifier {
          $$ = newNode("Specifier", @$.first_line);
          addChild($$, 1, $1);
      }
    ;
StructSpecifier:
      STRUCT ID LC DefList RC {
          $$ = newNode("StructSpecifier", @$.first_line);
          addChild($$, 5, $1, $2, $3, $4, $5);
      }
    | STRUCT ID {
          $$ = newNode("StructSpecifier", @$.first_line);
          addChild($$, 2, $1, $2);
      }
    ;
VarDec:
      ID {
          $$ = newNode("VarDec", @$.first_line);
          addChild($$, 1, $1);
      }
    | VarDec LB INT RB {
          $$ = newNode("VarDec", @$.first_line);
          addChild($$, 4, $1, $2, $3, $4);
      }
    | UNKNOW {

      }
    ;
FunDec:
      ID LP VarList RP {
          $$ = newNode("FunDec", @$.first_line);
          addChild($$, 4, $1, $2, $3, $4);
      }
    | ID LP RP {
          $$ = newNode("FunDec", @$.first_line);
          addChild($$, 3, $1, $2, $3);
      }
    | ID LP error {
        error = 1;
        SYNError("Missing closing parenthesis ')'", @$.first_line);
      }
    | ID LP VarList error {
        error = 1;
        SYNError("Missing closing parenthesis ')'", @$.first_line);
      }
    ;
VarList:
      ParamDec COMMA VarList {
          $$ = newNode("VarList", @$.first_line);
          addChild($$, 3, $1, $2, $3);
      }
    | ParamDec {
          $$ = newNode("VarList", @$.first_line);
          addChild($$, 1, $1);
      }
    ;
ParamDec:
      Specifier VarDec {
          $$ = newNode("ParamDec", @$.first_line);
          addChild($$, 2, $1, $2);
      }
    ;
CompSt:
      LC DefList StmtList RC {
          $$ = newNode("CompSt", @$.first_line);
          addChild($$, 4, $1, $2, $3, $4);
      }
    ;
StmtList:
      Stmt StmtList {
          $$ = newNode("StmtList", @$.first_line);
          addChild($$, 2, $1, $2);
      }
    | {
          $$ = newNode("NONE", @$.first_line); 
      }
    ;
Stmt:
      Exp SEMI {
          $$ = newNode("Stmt", @$.first_line);
          addChild($$, 2, $1, $2);
      }
    | CompSt {
          $$ = newNode("Stmt", @$.first_line);
          addChild($$, 1, $1);
      }
    | RETURN Exp SEMI {
          $$ = newNode("Stmt", @$.first_line);
          addChild($$, 3, $1, $2, $3);
      }
    | IF LP Exp RP Stmt %prec LOWER_ELSE {
          $$ = newNode("Stmt", @$.first_line);
          addChild($$, 5, $1, $2, $3, $4, $5);
      }
    | IF LP Exp RP Stmt ELSE Stmt {
          $$ = newNode("Stmt", @$.first_line);
          addChild($$, 7, $1, $2, $3, $4, $5, $6, $7);
      }
    | WHILE LP Exp RP Stmt {
          $$ = newNode("Stmt", @$.first_line);
          addChild($$, 5, $1, $2, $3, $4, $5);
      }
    | Exp error {
        error = 1;
        SYNError("Missing semicolon ';'", @$.first_line);
      }
    | RETURN Exp error {
        error = 1;
        SYNError("Missing semicolon ';'", @$.first_line);
      }
    ;
DefList:
      Def DefList {
          $$ = newNode("DefList", @$.first_line);
          addChild($$, 2, $1, $2);
      }
    | {
          $$ = newNode("NONE", @$.first_line); 
      }
    ;
Def:
      Specifier DecList SEMI {
          $$ = newNode("Def", @$.first_line);
          addChild($$, 3, $1, $2, $3);
      }
    | Specifier DecList error {
          error = 1;
          SYNError("Missing semicolon ';'", @$.first_line);
      }
    ;
DecList:
      Dec {
          $$ = newNode("DecList", @$.first_line);
          addChild($$, 1, $1);
      }
    | Dec COMMA DecList {
          $$ = newNode("DecList", @$.first_line);
          addChild($$, 3, $1, $2, $3);
      }
    ;
Dec: 
      VarDec {
          $$ = newNode("Dec", @$.first_line);
          addChild($$, 1, $1);
      }
    | VarDec ASSIGN Exp {
          $$ = newNode("Dec", @$.first_line);
          addChild($$, 3, $1, $2, $3);
      }
    ;
Exp:
      Exp ASSIGN Exp {
          $$ = newNode("Exp", @$.first_line);
          addChild($$, 3, $1, $2, $3);
      }
    | Exp AND Exp {
          $$ = newNode("Exp", @$.first_line);
          addChild($$, 3, $1, $2, $3);
      }
    | Exp OR Exp {
          $$ = newNode("Exp", @$.first_line);
          addChild($$, 3, $1, $2, $3);
      }
    | Exp LT Exp {
          $$ = newNode("Exp", @$.first_line);
          addChild($$, 3, $1, $2, $3);
      }
    | Exp LE Exp {
          $$ = newNode("Exp", @$.first_line);
          addChild($$, 3, $1, $2, $3);
      }
    | Exp GT Exp {
          $$ = newNode("Exp", @$.first_line);
          addChild($$, 3, $1, $2, $3);
      }
    | Exp GE Exp {
          $$ = newNode("Exp", @$.first_line);
          addChild($$, 3, $1, $2, $3);
      }
    | Exp NE Exp {
          $$ = newNode("Exp", @$.first_line);
          addChild($$, 3, $1, $2, $3);
      }
    | Exp EQ Exp {
          $$ = newNode("Exp", @$.first_line);
          addChild($$, 3, $1, $2, $3);
      }
    | Exp PLUS Exp {
          $$ = newNode("Exp", @$.first_line);
          addChild($$, 3, $1, $2, $3);
      }
    | Exp MINUS Exp {
          $$ = newNode("Exp", @$.first_line);
          addChild($$, 3, $1, $2, $3);
      }
    | Exp MUL Exp {
          $$ = newNode("Exp", @$.first_line);
          addChild($$, 3, $1, $2, $3);
      }
    | Exp DIV Exp {
          $$ = newNode("Exp", @$.first_line);
          addChild($$, 3, $1, $2, $3);
      }
    | Exp UNKNOW Exp {

      }
    | LP Exp RP {
          $$ = newNode("Exp", @$.first_line);
          addChild($$, 3, $1, $2, $3);
      }
    | MINUS Exp %prec UMINUS {
          $$ = newNode("Exp", @$.first_line);
          addChild($$, 2, $1, $2);
      }
    | NOT Exp {
          $$ = newNode("Exp", @$.first_line);
          addChild($$, 2, $1, $2);
      }
    | ID LP Args RP {
          $$ = newNode("Exp", @$.first_line);
          addChild($$, 4, $1, $2, $3, $4);
      }
    | ID LP RP {
          $$ = newNode("Exp", @$.first_line);
          addChild($$, 3, $1, $2, $3);
      }
    | Exp LB Exp RB {
          $$ = newNode("Exp", @$.first_line);
          addChild($$, 4, $1, $2, $3, $4);
      }
    | Exp DOT ID {
          $$ = newNode("Exp", @$.first_line);
          addChild($$, 3, $1, $2, $3);
      }
    | ID {
          $$ = newNode("Exp", @$.first_line);
          addChild($$, 1, $1);
      }
    | INT {
          $$ = newNode("Exp", @$.first_line);
          addChild($$, 1, $1);
      }
    | FLOAT {
          $$ = newNode("Exp", @$.first_line);
          addChild($$, 1, $1);
      }
    | CHAR {
          $$ = newNode("Exp", @$.first_line);
          addChild($$, 1, $1);
      }
    | ID LP Args error {
          error = 1;
          SYNError("Missing closing parenthesis ')'", @$.first_line);
      }
    | ID LP error {
          error = 1;
          SYNError("Missing closing parenthesis ')'", @$.first_line);
      }
    | UNKNOW {

      }
    ;
Args:
      Exp COMMA Args {
          $$ = newNode("Args", @$.first_line);
          addChild($$, 3, $1, $2, $3);
      }
    | Exp {
          $$ = newNode("Args", @$.first_line);
          addChild($$, 1, $1);
      }
    ;

%%
void SYNError(const char *s, int line)
{
    fprintf(out, "Error type B at Line %d: %s\n", line, s);
}

void yyerror(const char *s){
    /* fprintf(out, "syntax error: must be recovered \n"); */
    /* fprintf(out, "Error type B at Line %d: %s\n", yylloc.first_line, s); */
    /* yyerrok; */
}

void initiate() {
    yycolno = 1;
    yylineno = 1;
    yytext = "";
    yyleng = 0;
    error = 0;
    root = NULL;
}

int main(int argc, char **argv){
    if(argc == 1) {
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        exit(-1);
    } else {
        for (int i = 1; i < argc; ++ i) {
            initiate();
            int name_len = strlen(argv[i]);
            char *out_name = (char *)malloc(name_len + 1);
            strcpy(out_name, argv[i]);
            out_name[name_len - 3] = 'o';
            out_name[name_len - 2] = 'u';
            out_name[name_len - 1] = 't';
            out_name[name_len] = '\0';
            char buf[1024];
            int len;
            FILE *fp;
            if(!(fp = fopen(argv[i],"r")))
            {
                perror("fail to read");
                exit (1) ;
            }
            out = fopen(out_name, "w");
            yyrestart(fp);
            yydebug=1;
            yyparse();
            if(!error)
                dfsPrint(root, 0);
            fclose(fp);
            fclose(out);
        }
    }
    return 0;
}
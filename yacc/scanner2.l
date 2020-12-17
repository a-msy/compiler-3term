%{
#include "tree.h"
#include "y.tab.h"
char *copy_lexeme();
%}
%%
[\t ]+         {}
"+"            { return PLUS; }
"*"            { return TIMES; }
"("            { return LPAR; }
")"            { return RPAR; }
[a-z][a-z0-9]* { yylval.name = copy_lexeme(); return IDENTIFIER; }
0|[1-9][0-9]*  { yylval.name = copy_lexeme(); return NUMBER; }
\n             { return 0; }
.              { printf("lexical error: '%c'\n", yytext[0]); }
%%
char StringTable[1000];
char *STp = StringTable;
char *copy_lexeme() {
    char *p = STp;
    strcpy(STp, yytext);
    STp += strlen(yytext) + 1;
    return p;
}


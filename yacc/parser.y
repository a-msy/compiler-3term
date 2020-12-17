%{
#include <stdio.h>
long make_tuple(char *op, long arg1, long arg2); /* プロトタイプ宣言 */
%}
%token PLUS TIMES LPAR RPAR IDENTIFIER NUMBER
%%
E: E PLUS T { $$ = make_tuple("+", $1, $3); }
 | T        { $$ = $1; }
T: T TIMES F { $$ = make_tuple("*", $1, $3); }
 | F        { $$ = $1; }
F: LPAR E RPAR { $$ = $2; }
 | IDENTIFIER  { $$ = $1; }
 | NUMBER  { $$ = $1; }
%%
long prev_tuple = 0;
long make_tuple(char *op, long arg1, long arg2) {
    printf("T%d: (%s, ", ++prev_tuple, op);
    if (arg1 > 0) 
        printf("%s, ", arg1);
    else
        printf("T%d, ", -arg1);
    if (arg2 > 0) 
        printf("%s", arg2);
    else
        printf("T%d", -arg2);
    printf(")\n");
    return -prev_tuple;
}

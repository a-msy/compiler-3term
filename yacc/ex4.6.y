%{
#include <stdio.h>
%}
%token NUMBER
%%
S: E ';'     { printf("%d.\n", $1); }
 ;

E: E '+' T   { $$ = $1 + $3; }
 | T         { $$ = $1; }
 ;

T: T '*' F   { $$ = $1 * $3; }
 | F         { $$ = $1; }
 ;

F: '(' E ')' { $$ = $2; }
 | NUMBER    { $$ = $1; }
 ;
%%

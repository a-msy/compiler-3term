%{
#include <stdlib.h>
#include "tree.h"
%}
%union {
    char   *name;
    tree_t *tree;
}
%token PLUS TIMES LPAR RPAR 
%token <name> IDENTIFIER
%token <name> NUMBER
%type <tree> E T F
%%
Expr: E        { print_tree($1); }
E: E PLUS T    { $$ = make_binary(Add_Expr, $1, $3); }
 | T           { $$ = $1; }
T: T TIMES F   { $$ = make_binary(Mul_Expr, $1, $3); }
 | F           { $$ = $1; }
F: LPAR E RPAR { $$ = $2; }
 | IDENTIFIER  { $$ = make_var($1); }
 | NUMBER      { $$ = make_iconst(atoi($1)); }
%%

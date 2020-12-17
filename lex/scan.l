%%
[\t ]+ {}
(a|b)*ab { printf("%s: OK.\n", yytext); }
. { printf("%s: wrong.\n", yytext); }
%%

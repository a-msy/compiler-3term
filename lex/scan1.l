%%
[\t ]+ {}
"+"|"-"|"*"|"/"|"=" { printf("%s (operator) ", yytext); }
";"                 { printf("%s (separator) ", yytext); }
[a-z][a-z0-9]*      { printf("%s (identifier) ", yytext); }
[0-9\.]             { printf("%s (number) ", yytext); }
.                   { printf("%s (don't know) ", yytext); }
%%

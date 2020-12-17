%%
[\t ]+         {}
"int"          { printf("KEYWORD(%s) ",yytext); }
"main"          { printf("KEYWORD(%s) ",yytext); }
"void"          { printf("KEYWORD(%s) ",yytext); }
"double"          { printf("KEYWORD(%s) ",yytext); }
"if"          { printf("KEYWORD(%s) ",yytext); }
"else"          { printf("KEYWORD(%s) ",yytext); }
"for"          { printf("KEYWORD(%s) ",yytext); }
"while"          { printf("KEYWORD(%s) ",yytext); }
"do"          { printf("KEYWORD(%s) ",yytext); }
"char"          { printf("KEYWORD(%s) ",yytext); }
"return"          { printf("KEYWORD(%s) ",yytext); }
"float"          { printf("KEYWORD(%s) ",yytext); }
"+"            { printf("PLUS "); }
"-"            { printf("MINUS ");}
"/"            { printf("DIVIDE ");}
"="            { printf("ASSIGN ");}
"=="            { printf("EQUAL ");}
"!="            { printf("NOTEQUAL ");}
"%"            { printf("SURPLUS ");}
"<"            { printf("LESSTHAN ");}
">"            { printf("GREATERTHAN ");}
"<="            { printf("ORLESS ");}
">="            { printf("ORMORE ");}
"*"            { printf("TIMES "); }
"("            { printf("LPAR "); }
")"            { printf("RPAR "); }
"{"            { printf("LBRA "); }
"}"            { printf("RBRA "); }
[a-z][a-z0-9]* { printf("IDENTIFIER(%s) ", yytext); }
[+-]?[0-9]+ { printf("NUMBER(%s) ", yytext); }
[+-]?[0-9]*[.][0-9]+ { printf("NUMBER(%s) ", yytext); }
";"            { printf("SEPARATOR(%s) ", yytext); }
"\n"           { printf("NEWLINE\n"); }
.              { printf("lexical error: '%c'\n", yytext[0]);
                return 0; // stop lexical analysis
              }

%{
#include "y.tab.h"
#include <stdlib.h>
%}

%%
[0-9]+       { yylval = atoi(yytext); return NUMBER; }
[a-zA-Z]+    { return ID; }
[ \t\r]+     ;
\n           { return 0; }
.            { return yytext[0]; }
%%

int yywrap(void)
{
    return 1;
}

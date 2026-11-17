%{
#include<stdio.h>
#include<stdlib.h>
#include "y.tab.h"
%}

%%
[0-9]+   {yyval=atoi(yytext); return NUMBER; }
[ \t\r]+   ;
\n   {return 0; }
.   {return yytext[0]; }
%%

int yywrap(void)
{
    return 1;
}
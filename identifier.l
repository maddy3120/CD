%{
#include "y.tab.h"   
%}

%%
[a-zA-Z]   {return LETTER; }
[0-9]   {return NUMBER; }
\n   {return 0; }
[\t]+   {return yytext[0]; }
.   {return yytext[0]; }
%%

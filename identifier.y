%{
#include<stdio.h>
#include<stdlib.h>

int yylex(void);
int yyerror(char *s);
%}

%token LETTER NUMBER

%%
validid: iden
    {
        printf("\nValid identifier.\n");
    }
    ;

iden: LETTER
    | iden LETTER
    | iden NUMBER
    ;
%%

int main(void)
{
    printf("Enter string: ");
    yyparse();
    return 0;
}
int yyerror(char *s)
{
    printf("\nInvalid identifier.\n");
    return 0;
}
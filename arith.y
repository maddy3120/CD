%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
int yyerror(char *s);
%}

%token NUMBER ID
%left '+' '-'
%left '*' '/'

%%
expr : expr '+' expr
     | expr '-' expr
     | expr '*' expr
     | expr '/' expr
     | '-' NUMBER
     | '-' ID
     | '(' expr ')'
     | NUMBER
     | ID
     ;
%%

int main(void)
{
    printf("Enter the expression\n");
    yyparse();
    printf("\nExpression is valid\n");
    return 0;
}

int yyerror(char *s)
{
    printf("\nExpression is invalid\n");
    exit(0);
}
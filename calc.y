%{
#include<stdio.h>
#include<stdlib.h>
int yylex(void);
int yyerror(char *s);
int flag=0;
%}

%token NUMBER

%left '+' '-'
%left '*' '/' '%'

%start ArithmeticExpression

%%
ArithmeticExpression: E
    {
        printf("\nresult: %d\n", $1);
    }
    ;
E: E '+' E {$$ = $1 + $3; }
    | E '-' E {$$ = $1 - $3; }
    | E '*' E {$$ = $1 * $3; }
    | E '/' E
        {
        if ($3==0){
            yyerror("division by zero.\n");
            YYABORT;
        }
        $$ = $1 / $3;
        }
    | E '%' E
        {
        if($3==0){
            yyerror("modulus by zero.\n");
            YYABORT;
        }
        $$ = $1 % $3;
        }
    | '(' E ')' {$$ = $2; }
    | NUMBER {$$ = $1; }
    ;
%%
int main(void)
{
    printf("Enter arithmetic expression: ");
    if(yyparse()==0 && flag==0){
        printf("Expression valid.");
    }
    return 0;
}
int yyerror(char *s){
    printf("expression invalid.\n");
    flag=1;
    return 0;
}
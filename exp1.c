#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isKeyword(char *word)
{
    char *keys[] = {
        "auto", "break", "case", "char", "const", "continue", "default",
        "do", "double", "else", "enum", "extern", "float", "for", "goto",
        "if", "int", "long", "register", "return", "short", "signed",
        "sizeof", "static", "struct", "switch", "typedef", "union",
        "unsigned", "void", "volatile", "while",
        NULL
    };

    int i = 0;

    while(keys[i] != NULL)
    {
        if(strcmp(word, keys[i]) == 0)
            return 1;
        i++;
    }

    return 0;
}

int isLibraryFunction(char *word)
{
    char *funcs[] = {
        "printf", "scanf", "fprintf", "fscanf", "sprintf", "sscanf",
        "getc", "putc", "getchar", "putchar",
        "fopen", "fclose", "fgetc", "fputc", "fgets", "fputs",
        "fread", "fwrite", "feof", "rewind",
        "malloc", "calloc", "realloc", "free",
        "strlen", "strcpy", "strncpy", "strcat", "strcmp", "strchr",
        "atoi", "atof", "exit", "main",
        NULL
    };

    int i = 0;

    while(funcs[i] != NULL)
    {
        if(strcmp(word, funcs[i]) == 0)
            return 1;
        i++;
    }

    return 0;
}

int main()
{
    FILE *fp;
    char filename[100];
    char token[100];
    char preprocessor[200];
    int ch;
    int i = 0, j;

    printf("Enter source file: ");
    scanf("%99s", filename);

    fp = fopen(filename, "r");

    if(fp == NULL)
    {
        printf("Cannot open %s\n", filename);
        return 0;
    }

    printf("\nLexical Analysis\n\n");

    while((ch = fgetc(fp)) != EOF)
    {
        /* Preprocessor Directive */
        if(ch == '#')
        {
            j = 0;
            preprocessor[j++] = ch;

            while((ch = fgetc(fp)) != '\n' && ch != EOF)
            {
                if(j < 198)
                    preprocessor[j++] = ch;
            }

            preprocessor[j] = '\0';

            printf("%-35s Preprocessor Directive\n", preprocessor);
            continue;
        }

        /* Form Tokens */
        if(isalnum((unsigned char)ch) || ch == '_' || ch == '.')
        {
            if(i < 99)
                token[i++] = ch;
        }
        else
        {
            if(i > 0)
            {
                token[i] = '\0';

                if(strstr(token, ".h") != NULL)
                    printf("%-25s Header File\n", token);

                else if(isKeyword(token))
                    printf("%-25s Keyword\n", token);

                else if(isdigit((unsigned char)token[0]))
                    printf("%-25s Number\n", token);

                else if(isLibraryFunction(token))
                    printf("%-25s Library Function\n", token);

                else
                    printf("%-25s Identifier\n", token);

                i = 0;
            }

            /* String Literal */
            if(ch == '"')
            {
                printf("\"");

                while((ch = fgetc(fp)) != '"' && ch != EOF)
                    putchar(ch);

                printf("\"%-16s\n", "String Literal");
            }

            /* Operators */
            else if(ch=='+' || ch=='-' || ch=='*' || ch=='/' ||
                    ch=='=' || ch=='<' || ch=='>' || ch=='%' ||
                    ch=='!' || ch=='&' || ch=='|')
            {
                printf("%-25c Operator\n", ch);
            }

            /* Special Symbols */
            else if(ch=='(' || ch==')' || ch=='{' || ch=='}' ||
                    ch=='[' || ch==']' || ch==';' || ch==',')
            {
                printf("%-25c Special Symbol\n", ch);
            }
        }
    }

    /* Process last token if file ends without separator */
    if(i > 0)
    {
        token[i] = '\0';

        if(strstr(token, ".h") != NULL)
            printf("%-25s Header File\n", token);

        else if(isKeyword(token))
            printf("%-25s Keyword\n", token);

        else if(isdigit((unsigned char)token[0]))
            printf("%-25s Number\n", token);

        else if(isLibraryFunction(token))
            printf("%-25s Library Function\n", token);

        else
            printf("%-25s Identifier\n", token);
    }

    fclose(fp);
    return 0;
}
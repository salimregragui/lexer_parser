/*********************************************************


    Parser and Lexer By Salim Regragui
    Code free to use in free and commercial use :)

*********************************************************/

#include "lexer.c"
#include "parser.c"

int main()
{
    char phrase[300];
    tokens* first_token;
    int keep_parsing = 0;

	do {
        system("cls");
        printf("What do you want to do ? ");
        gets(phrase);
        first_token = lexer(phrase);
        printf("\nRESPONSE OF THE PARSER : \n\n");
        parser(first_token);

        printf("\nWant to parse another phrase (type 1 if yes) ? ");
        scanf("%d",&keep_parsing);
        fflush(stdin);

	}while(keep_parsing == 1);

    return 0;
}

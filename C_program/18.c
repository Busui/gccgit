#include <stdio.h>

void getin(void);

static char ch = 'b';

int main(void)
{
    int i = 0;
    while(ch != 'q'){
        printf("%d ->", i);
        getin();
        printf(" %c\n",ch);
        ++i;
    }

    return 0;
}

void getin(void)
{
    //fflush(stdin);
    //setbuf(stdin, NULL);
    scanf("%c",&ch);
    getchar();
}

        /*************************************************************
         * fflush and setbuf function are useless for cleaning stream*
         * in linux.So I use "getchar()" behind scanf() to eat '\n'. *
         *However,The more interesting thing is when you put the 'ge-*
         *tchar() ahead of the scanf(),then,you cann't end of the pr-*
         *ogram.                                                     *
         *************************************************************/


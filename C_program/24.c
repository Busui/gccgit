#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    srand(time(NULL));
    int number = 3;

    for(int i = 0 ; i < 20 ; ++i){
        int funsel = ((int)(((double)(rand())*(number))/RAND_MAX)); //(RAND_MAX + 4.0)));
        printf("%3d ",funsel);
    }
    printf("%llu",RAND_MAX);
    return 0;
}

#include <stdio.h>
#include <stdbool.h>

bool get(void);

int main(void)
{
    int i = 0;
    while(get())
      printf("%d ", ++i);
    return 0;
}

bool get()
{
    char m = '\0';
    scanf(" %c",&m);
    if(m == 'y')
        return true;
    else
        return false;
}
/***************************************************************************
 * 第一次执行时，到while语句会调用get函数，这时候会直接到达get函数里面执行 *
 * 如果get函数返回一个true值，在main函数会调用printf函数输出1              *
 * 然后又执行while函数里面的判断条件（即get函数），调用get函数返回true时， *
 *main 又会再次输出一个i++，即2                                            *
 * 以此类推                                                                *
 * *************************************************************************/

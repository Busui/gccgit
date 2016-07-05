#include <stdio.h>
#include <stdlib.h>

#define LENGTH 30

int main(void)
{
    FILE *pfile = NULL;
    char *filename = "seek.bin";
    char array[LENGTH];
    long i = 4;
    long fpos;

    if(!(pfile = fopen(filename, "wb"))){
        printf("Error opening %s for writing.Program terminated.\n");
        exit(1);
    }
    setvbuf(pfile, NULL, _IOFBF, BUFSIZ);

    fgets(array, LENGTH, stdin);

    size_t num = sizeof(array)/sizeof(array[0]);
    fwrite(array, LENGTH, num, pfile);

    fclose(pfile);
    pfile = NULL;

    if(!(pfile = fopen(filename, "rb"))){
        printf("Error opening %s for reading.Program terminated.\n",filename);
        exit(1);
    }
    setvbuf(pfile, NULL, _IOFBF, BUFSIZ);

    fpos = ftell(pfile);
    printf("%d",fpos);
    fseek(pfile, i*sizeof(char), SEEK_SET);

    fread(array, sizeof(array), 1, pfile );
    /*********************************************
     * 作孽阿，开始的时候用                      *
     * fread(array, sizeof(array), num -i, pfile)*
     * 发现什么问题没有？sizeof(array),与 num - i*
     * 结合在一起出大问题阿，严重超出array数组的 *
     * 大小范围。导致内存溢出。。。。            *
     * *******************************************/
   // fgets(array, num - (size_t)i, pfile);

    fclose(pfile);
    pfile = NULL;
    printf("%s",array);

    return 0;
}

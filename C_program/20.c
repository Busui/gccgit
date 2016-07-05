#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXLEN 50

void listfile(const char *filename);

int main(void)
{
    const char *filename = "mypeople.bin";
    char name[MAXLEN];
    size_t length = 0;
    int age = 0;
    char answer = 'y';
    FILE *pfile = NULL;

    if(!(pfile = fopen(filename, "wb+"))){
        printf("Failed to create file %s.\n",filename);
        exit(1);
    }
    
    do{
        printf("Enter a name less than %d characters: ", MAXLEN);
        fgets(name, sizeof(name), stdin);
        size_t p = strlen(name);
        name[p - 1] = '\0';

        printf("Enter the age of %s.\n",filename);
        scanf(" %d", &age);
        getchar();

        length = strlen(name);
        fwrite(&length, sizeof(length), 1, pfile);
        fwrite(name, sizeof(char), length, pfile);
        fwrite(&age, sizeof(age), 1, pfile);

        printf("Do you want to enter another(y or n)? ");
        scanf("\n%c", &answer);
        getchar();
    }while(tolower(answer) == 'y');

    fclose(pfile);
    pfile = NULL;
    listfile(filename);

    return 0;
}

void listfile(const char *filename)
{
    size_t length = 0;
    char name[MAXLEN];
    int age = 0;
    char format[20];
    FILE *pfile = NULL;

    sprintf(format, "%%-%ds Age:%%4d\n", MAXLEN);

    if(!(pfile = fopen(filename, "rb"))){
        printf("Failed to open file %s to read it.\n",filename);
        exit(1);
    }
    printf("The folks recorded in the %s file are:\n",filename);

    while(fread(&length, sizeof(length), 1, pfile) == 1){
        if(length + 1 > MAXLEN){
            printf("Name too long.\n");
            exit(1);
        }
        fread(name, sizeof(char), length, pfile);
        name[length] = '\0';
        fread(&age, sizeof(age), 1, pfile);
        printf(format, name, age);
    }

    fclose(pfile);
    pfile = NULL;
}

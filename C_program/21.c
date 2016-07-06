#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#define MAXLEN 50

const char *filename = "my-people.bin";

typedef struct Record
{
    char name[MAXLEN];
    int age;
} Record;

void list_file(void);
void update_file(void);
Record *get_person(Record *precord);
void get_name(char *pname, size_t size);
void write_file(const char* mode);
void write_record(const Record *precord, FILE *pfile);
Record *read_record(Record *precord, FILE *pfile);
int find_record(Record *precord, FILE *pfile);
void duplicate_file(const Record *pnewrecord, int index, FILE *pfile);


int main(void)
{
    char answer = 'q';

    while(true){
        printf("Choose from the following options:\n"
                "  To list the file contents enter  L\n"
                "  To create a new file enter       C\n"
                "  To add new records enter         A\n"
                "  To update existing records emter U\n"
                "  To delete the file enter         D\n"
                "  To end the program enter         Q\n: ");
        scanf("\n%c", &answer);
        getchar();
        switch(toupper(answer))
        {
            case 'L':
                list_file();
                break;
            case 'C':
                write_file("wb+");
                printf("\nFile create complete.\n");
                break;
            case 'A':
                write_file("ab+");
                printf("\nfile append complete.\n");
                break;
            case 'U':
                update_file();
                break;
            case 'D':
                printf("Are you sure you want to delete %s (y or n)? ", filename);
                scanf("\n%c",&answer);
                getchar();
                if(tolower(answer) == 'y')
                    remove(filename);
                break;
            case 'Q':
                printf("Ending the program.\n");
                exit(0);
            default:
                printf("Invalid selection. Try again.\n");
                break;
        }
    }

    return 0;
}


Record *get_person(Record *precord)
{
    printf("Enter a name less than %d characters: ", MAXLEN);
    get_name(precord -> name, MAXLEN);
    printf("Enter the age of %s: ", precord -> name);
    scanf(" %d", &precord -> age);
    return precord;
}

void get_name(char *pname, size_t size)
{
    fgets(pname, size, stdin);
    size_t len = strlen(pname);
    if(pname[len - 1] == '\n')
        pname[len - 1] = '\0';
}

void write_record(const Record *precord, FILE *pfile)
{
    size_t length = strlen(precord -> name);
    fwrite(&length, sizeof(length), 1, pfile);
    fwrite(precord -> name, sizeof(char), length, pfile);
    fwrite(&precord -> age, sizeof(precord -> age), 1, pfile);
}

Record *read_record(Record *precord, FILE *pfile)
{
    size_t length = 0;
    fread(&length ,sizeof(length), 1, pfile);
    if(feof(pfile))
        return NULL;

    fread(precord -> name, sizeof(char), length, pfile);
    //一样可以用sizeof(precord -> name),1
    //但这样会造成内存浪费
    precord -> name[length] = '\0';
    // did not write '\0' at the end of "name" array when use 
    // the fwrite function.so add to here.
    fread(&precord -> age, sizeof(precord -> age), 1, pfile);

    return precord;
}

void write_file(const char *mode)
{
    char answer = 'y';

    FILE *pfile = NULL;
    if(!(pfile = fopen(filename, mode))){
        fprintf(stderr, "File open failed.\n");
        exit(1);
    }

    do{
        Record record;
        write_record(get_person(&record),pfile);

        printf("Do you want to enter another(y or n)? ");
        scanf(" %c", &answer);
        getchar();
    }while(tolower(answer) == 'y');
    fclose(pfile);
    pfile = NULL;
}

void list_file(void)
{
    char format[18];
    sprintf(format, "%%-%ds Age:%%4d\n", MAXLEN);

    FILE *pfile = NULL;
    if(!(pfile = fopen(filename, "rb"))){
        fprintf(stderr, "Unable to open %s. Verify it exists.\n",filename);
        return;
    }

    Record record;
    printf("The folks recorded in the %s file are:\n", filename);

    while(read_record(&record, pfile))
        printf(format, record.name, record.age);
    //record -> name equal to the adress of record.name

    printf("\n");
    fclose(pfile);
    pfile = NULL;
}

void duplicate_file(const Record *pnewrecord, int index, FILE *pfile)
{
    char tempname[L_tmpnam];
    if(mkstemp(tempname)){
        fprintf(stderr, "Terporary file name creation failed.\n");
        exit(1);
    }
    FILE *ptempfile = NULL;
    if(!(ptempfile = fopen(tempname, "wb+"))){
        fprintf(stderr, "Terporary file name creation failed.\n");
        exit(1);
    }

    rewind(pfile);
    Record record;
    for(int i = 0; i < index; ++i)
        write_record(read_record(&record, pfile), ptempfile);

    write_record(pnewrecord, ptempfile);
    read_record(&record, pfile);//将被更新的record以只读
    //不写的方式去掉。

    while(read_record(&record, pfile))
        write_record(&record, ptempfile);

    fclose(pfile);
    pfile = NULL;

    if(remove(filename)){
        printf("Faile to remove the old file.\n");
        exit(1);
    }

    if(rename(tempname, filename)){
        printf("Renaming the file copy failed.\n");
        exit(1);
    }

}

void update_file(void)
{
    FILE *pfile = NULL;
    if(!(pfile = fopen(filename, "rb+"))){
        printf("File open for updating records failed."
                "Maybe file does not exist.\n");
        exit(1);
    }

    Record record;
    int index = find_record(&record, pfile);
    if(index < 0){
        printf("Record not found\n");
        fclose(pfile);
        pfile = NULL;
        return;
    }

    printf("%s is aged %d.\n", record.name, record.age);
    Record newrecord;
    printf("You can now enter the new name and age for %s.\n", 
            record.name);
    get_person(&newrecord);

    if(strlen(record.name) == strlen(newrecord.name)){
        //name lengths are the same so we can update in place
        fseek(pfile, -(long)(sizeof(size_t) + 
                    strlen(record.name) + sizeof(record.age)),
                                                SEEK_CUR);
        write_record(&newrecord, pfile);
        fflush(pfile);
        fclose(pfile);
        pfile = NULL;
    }
    else
        duplicate_file(&newrecord, index, pfile);
    printf("File update complete.\n");
}

int find_record(Record* precord, FILE *pfile)
{
  char name[MAXLEN];
  printf("Enter the name for the record you wish to find: ");
  get_name(name, MAXLEN);

  rewind(pfile);
  int index = 0;

  while(true){
    if(!read_record(precord, pfile))
        return -1;

    if(!strcmp(name, precord -> name))
        break;
    ++index;
  }

  return index;
}


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define NAME_MAX 21

struct 
{
    char *filename;
    FILE *pfile;
} global =  {
                .filename = "myfile1.bin",
                .pfile = NULL
            };

typedef struct Date
{
    int day;
    int month;
    int year;
} Date;

typedef struct Family
{
    Date dob;
    char name[NAME_MAX];
    char pa_name[NAME_MAX];
    char ma_name[NAME_MAX];
} Family;

bool get_person(Family *pfamily);
void getname(char *name, size_t size);
void show_person_date(void);
void get_parent_dob(Family *pfamily);
void open_file(char *mode);
void close_file(void);

int main(void)
{
    Family member;
    open_file("ab");
    while(get_person(&member))
        fwrite(&member, sizeof(member), 1, global.pfile);
    printf("1\n");
    fclose(global.pfile);
    printf("2\n");

    show_person_date();

    if(remove(global.filename))
        printf("Unable to delete %s.\n",global.pfile);
    else
        printf("Delete %s ok.\n",global.pfile);

    return 0;
}

bool get_person(Family *temp)
{
    static char more = '\0';

    printf("\nDo you want to enter details of %s person(y or n)?",
                                more != '\0' ? "another" : "a");

    scanf(" %c",&more);

    if(tolower(more) == 'n')
            return false;

    printf("Enter the name of the person: ");
    getname(temp -> name, sizeof(temp -> name));
    printf("Enter %s's date of birth (day month year): ",
                                        temp -> name);
    scanf(" %d %d %d", &temp -> dob.day, &temp -> dob.month,
                                         &temp -> dob.year);

    printf("Who is %s's father? ", temp -> name);
    getname(temp -> pa_name, sizeof(temp -> pa_name));

    printf("Who is %s's mother? ");
    getname(temp -> ma_name, sizeof(temp -> ma_name));

    return true;
}

void getname(char *name, size_t size)
{
    //fflush(stdin);
    setbuf(stdin, NULL);
   // char buf[50];
    //fgets(buf, 50, stdin);
    fgets(name, size, stdin);
    int len = strlen(name);
    if(name[len - 1] == '\n')
        name[len - 1] = '\0';
}

void show_person_date(void)
{   
    printf("4\n");///////////////////////////////////////////////////////
    Family member;
    printf("6\n");
    open_file("rb");
    printf("5\n");

    while(fread(&member, sizeof(member), 1, global.pfile)){
        printf("%s's father is %s, and mother is %s.\n",
            member.name, member.pa_name, member.ma_name);
        printf("6\n");
        get_parent_dob(&member);
    }
    close_file();
    printf("3\n");//////////////////////////////////////////////////////////
}

void get_parent_dob(Family *pmember)
{
    Family relative;
    int num_found = 0;
    fpos_t current;
    fgetpos(global.pfile, &current);
    rewind(global.pfile);

    while(fread(&relative, sizeof(Family), 1, global.pfile)){
        if(strcmp(pmember -> pa_name, relative.name) == 0){
            printf(" Pa was born on %d/%d/%d.", relative.dob.day,
                                                relative.dob.month,
                                                relative.dob.year);
            ++num_found;
        }
        else if(strcmp(pmember -> ma_name, relative.name) == 0){
            printf(" Ma was born on %d/%d/%d.", relative.dob.day,
                                                relative.dob.month,
                                                relative.dob.year);
            ++num_found;
        }
        if(num_found == 2)
            break;
    }
    if(!num_found)
        printf(" No info on parent available.");

    printf("\n");
    /**
     * if(fsetpos(global.pfile, &current)){
        printf("Failed to set file position.\n");
        perror(global.filename);
        exit(1);
    }
    **/
    fsetpos(global.pfile, &current);
}

void open_file(char *mode)
{
    printf("8\n");/////////////////////////
    if(global.pfile){
        printf("9\n");////////////////////////////
        fclose(global.pfile);
        printf("0\n");
        global.pfile = NULL;//close_file();
    }

    printf("7\n");//////////////////////////
    if(!(global.pfile = fopen(global.filename, mode))){
        printf("Unable to open %s with mode %s.\n",global.filename,
                                                            mode);
        exit(1);
    }
    setvbuf(global.pfile, NULL, _IOFBF, BUFSIZ);
}

void close_file(void)
{
    printf("10\n");
    fclose(global.pfile);
    printf("11\n");////////////////
    global.pfile = NULL;
    printf("12\n");//////////////
}



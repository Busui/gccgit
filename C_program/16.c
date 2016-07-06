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


  //  fclose(global.pfile);
  //  源程序这里是有这一个语句的，但它导致了整个程序map memmery。
  //  经过实验验证，导致错误的原因是由于取消global.pfile文件指针与文件的并联时，没有
  //  将指针指向NULL，这是指针就处于一个非NULL的未知值。而恰恰，在程序的open_file语句
  //  中，有一个
  //    if(global.pfile)
  //        close_file();
  // 这会导致什么呢？
  // 没错，if条件为true，重新执行关闭已经文件的close_file()函数。然而，指针已经取消与
  // 文件的并联关系，所以呢，导致内存紊乱。也就是大名鼎鼎的map memery.
  // 解决方法时什么？
  //    这里已经很明确了。只要你在关闭文件时，将指针指向NULL，从而if条件文false，就不会
  //    发生这样的事情啦。

                                /************************************************************************
                                 * 那么问题又来了，对一个已经指向NULL的指针在一次执行fclose会如何？
                                 *没有mapmemery，但是又有一个：
                                 *                              Segmentation fault (核心已转储)
                                 *         不知是什么鬼。只知道也是内存方面的错误。以后知识够了再解答。
                                 ************************************************************************/

   /**********************     
    fclose(global.pfile);
    global.pfile = NULL;
    fclose(global.pfile);
    global.pfile = NULL;
    *********************/

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
    getchar();//eat '\n'

    if(tolower(more) == 'n')
            return false;

    printf("Enter the name of the person: ");
    getname(temp -> name, sizeof(temp -> name));
    printf("Enter %s's date of birth (day month year): ",
                                        temp -> name);
    scanf(" %d %d %d", &temp -> dob.day, &temp -> dob.month,
                                         &temp -> dob.year);

    getchar();//eat '\n' form scanf()

    printf("Who is %s's father? ", temp -> name);
    getname(temp -> pa_name, sizeof(temp -> pa_name));

    printf("Who is %s's mother? ");
    getname(temp -> ma_name, sizeof(temp -> ma_name));

    return true;
}

void getname(char *name, size_t size)
{
    //fflush(stdin);没用，在linux上不能清除缓冲区。
    //setbuf(stdin, NULL);
   // char buf[50];
    //fgets(buf, 50, stdin);
    fgets(name, size, stdin);
    int len = strlen(name);
    if(name[len - 1] == '\n')
        name[len - 1] = '\0';
}

void show_person_date(void)
{   
    Family member;
    open_file("rb");

    while(fread(&member, sizeof(member), 1, global.pfile)){
        printf("%s's father is %s, and mother is %s.\n",
            member.name, member.pa_name, member.ma_name);
        get_parent_dob(&member);
    }
    close_file();
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
    if(global.pfile)
        close_file();

    if(!(global.pfile = fopen(global.filename, mode))){
        printf("Unable to open %s with mode %s.\n",global.filename,
                                                            mode);
        exit(1);
    }
    setvbuf(global.pfile, NULL, _IOFBF, BUFSIZ);
}

void close_file(void)
{
    fclose(global.pfile);
    global.pfile = NULL;
}



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 81

int main(void)
{
  FILE *pfile = NULL;
  char mystr[LENGTH];
  int mychar = 0;
  char *filename = "myfile1.txt";

  printf("Enter an interesting string of up to %d characters:\n",LENGTH - 1);
  if(!fgets(mystr, LENGTH, stdin))
  {
    printf("Input from keyboard failed.\n");
    exit(1);
  }

  if(!(pfile = fopen(filename, "w")))
  {
    printf("Error opening %s for writing.Program terminated.\n",filename);
    exit(1);
  }
  setvbuf(pfile, NULL, _IOFBF, BUFSIZ);

  for(int i = strlen(mystr) - 1 ; i >= 0 ; --i)
      fputc(mystr[i], pfile);
  fclose(pfile);
  pfile = NULL;

  if(!(pfile = fopen(filename, "r")))
  {
    printf("Error opening %s for reading.Program terminated.\n",filename);
    exit(1);
  }
  setvbuf(pfile, NULL, _IOFBF, BUFSIZ);
  while((mychar = fgetc(pfile)) != EOF)
    putchar(mychar);
    //printf("%d",mychar);
  fclose(pfile);
  pfile = NULL;

  return 0;
}

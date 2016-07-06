#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define LENGTH 81

int main(void)
{
  char *proverb[] = {
                "Many a mickle makes a muckle.\n",
                "Too many cooks spoil the broth.\n",
                "He who laugts last didn't get the joke in the first place.\n"
                    };
  char more[LENGTH];
  FILE *pfile = NULL;
  char *filename = "mylove.txt";

  if(!(pfile = fopen(filename, "w")))
  {
    printf("Error opening %s for writing.Program terminated.\n");
    exit(1);
  }
  setvbuf(pfile, NULL, _IOFBF, BUFSIZ);
  for(size_t i = 0 ; i < sizeof(proverb)/sizeof(proverb[0]) ; ++i)
  {
    if(EOF == fputs(proverb[i], pfile))
    {
      printf("Error writing file.\n");
      exit(1);
    }
  }
  fclose(pfile);
  pfile = NULL;

  if(!(pfile = fopen(filename, "a")))
  {
    printf("Error opening for writing.Program terminated.\n");
    exit(1);
  }
  setvbuf(pfile, NULL, _IOFBF, BUFSIZ);
  while(true)
  {
    fgets(more, LENGTH, stdin);
    if(more[0] == '\n')
        break;
    if(EOF == fputs(more, pfile))
    {
      printf("Error writing file.\n");
      exit(1);
    }
  }
  fclose(pfile);
  pfile = NULL;

  if(!(pfile = fopen(filename, "r")))
  {
    printf("Error opening %s for reading.Program terminated.\n");
    exit(1);
  }
  setvbuf(pfile, NULL, _IOFBF, BUFSIZ);
  while(fgets(more, LENGTH, pfile))
      printf("%s",more);
  fclose(pfile);
  pfile = NULL;

  return 0;
}

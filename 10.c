#include <stdio.h>
#include <stdlib.h>

int main(void)
{ 
  char b[] = "abc\n";
  char a[10];
  FILE *pfile = NULL;
  char *filename = "mylove.txt";
  if(!(pfile = fopen("mylove.txt", "w")))
  {
    printf("Error for open mylove.txt for writing.exit.\n");
    exit(1);
  }
  setbuf(pfile, NULL);
  
  printf("first");
  fprintf(stderr, "1");

  fprintf(pfile, "two\na");
  fclose(pfile);
  pfile = NULL;

  fprintf(stderr, "2");
  if(!(pfile = fopen(filename, "r")))
  {
    printf("Error opening mylove for reading.exit.\n");
    exit(1);
  }
  setbuf(pfile, NULL);

  fgets(a,10, pfile);
  fclose(pfile);
  pfile = NULL;

  printf("%s",a);
  printf("%s\n",b);
  printf("efg\n");
  printf("one");
  printf("one1\n");

  return 0;
}


/********************************
 printf("one");
 fprintf(stderr,"two");
 会先输出two再输出one，原因是stdout遇到换行符（或者main函数结束之后，作为程序交回控制给操作系统之前C运行时库所必须进行的清理工作的一部分。）才将stdout刷新输出stdout中的内容。而stderr不会缓存直接输出。
 证明：main函数结束后会刷新stdout
   
int main(void)
{
  printf("one");
  printf("two");
  fprintf(stderr, "three");
  printf("four");
  return 0;
}
输出：threeonetwofour
解释：因为输入到stderr的信息不会被缓存而直接输出，所以会先输出three，然后，printf语句会分别将onetwofour输入到stdout在内存中的缓冲区中，因为他们当中都没有换行符，所以stdout不会将缓冲区信息输出而是先憋住。最后到main函数结束，刷新并且输出了stdout缓冲区里的东西。

注：在默认情况下，stdout是行缓冲的，他的输出会放在一个buffer里面，只有到换行的时候，才会输出到屏幕。

或许还会有点疑问，那么看下面：
int main(void)
{
  printf("one");
  printf("two\n");
  fprintf(stderr, "three");
  printf("four");
  return 0;
}
结果输出：onetwo
          threefour
解释：这个看起来就明显多了。printf函数将onetwo存到缓冲区时，遇到了two后面的\n,由于stdout时行缓冲，会将缓冲区的onetwo一起输出。one后面没有\n呀，为什么还会被输出？哈哈，仔细看看很容易知道printf将one输出到缓冲区没有输出屏幕的戍守，下一句printf又马上将two接在one后，即onetwo。可以这样理解，one是搭了two后面的换行符的顺风车。
*******************************************************************/

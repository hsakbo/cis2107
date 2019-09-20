#include <stdio.h>
#define MAX 5
#define ever (;;);

//compile with gcc -E ex.c. produces stdout of the preprocessor output


int main()
{
  int hidden();
  int nMax = MAX;
  
  //for ever

  printf("%d\n", hidden());
  int a[] = {12, 41};
  return 0;
}

int hidden()
{
  return 1;
}

int *somefunction(int &a, int *b);

//note: x == 7 and 7==x are both valid
//      if(x=4) is executed since x != 0

//sizeof() when local it finds the whole contiguous block but called under a
//different function it will simply find the size of the type

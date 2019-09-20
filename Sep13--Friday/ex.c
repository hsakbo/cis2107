#include <stdio.h>

int G_var; //naming convention for global variables

static int fac(int n)
{
  if(n==0)
    return 1;
  static int x = 5;
  x = n;
  return x * fac(x-1);
}

union abc
{
  //a member that share the same storage space.
  //used in sparce memory because some variables are reset
  int x;
  int y;
  double z;

  //this will have a memory of z -- 8
  //use when you are unsure of what to use but 1 of them

};

void doSomething(int a, char **s)
{
  printf("Number of args = %d\n", a);
  for(int i = 0; i < a; i++)
    printf("arg[%d] = %s\n", i, s[i]);
}

int main(int argc, char **argv)
{
  int x = 5;
  //auto a;
  { //block scope
    x = 3;
    int x = 10;
    //printf("%d\n", x);//visibility inside inner scope
  }

  static int r = 4;
  int g = fac(r);
  printf("%d\n", g);

  //doSomething(argc, argv);

  //blockscope is governed by the principle of the least privilege
  //static wil mean initialize once. it will not reassign to the same val again
  //dont forget %s for printf

enum seasons
{
 FALL = 4,
 SUMMER,    //will automatically be incremented by 1
 SPRING,
 WINTER,
};


//if(5 == SUMMER)
// printf("%d\n", 4);

  return 0;
}
